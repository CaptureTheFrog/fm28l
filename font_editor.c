#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include "glyph_names.h"
#include <string.h>
#include <adwaita.h>
#include "font.h"

struct font font;
struct glyph *active_glyph = NULL;
AdwWindowTitle *titleWidget = NULL;
GtkDrawingArea *drawingArea = NULL;
GtkButton *btnSave = NULL;
GtkSpinButton *numWidth = NULL;
GtkSpinButton *numHeight = NULL;
GtkSpinButton *numDescend = NULL;
GtkButton *btnCrop = NULL;

char *font_filename = NULL;
cairo_matrix_t cr_matrix;

unsigned char unsaved = 0;
static gboolean ui_initialised = 0;

void reset_unsaved() {
    unsaved = 0;
    if (titleWidget && font.name[0])
        adw_window_title_set_subtitle(titleWidget, font.name);
    if (btnSave)
        gtk_widget_set_sensitive((GtkWidget *) btnSave, false);
}

void set_unsaved() {
    if (unsaved)
        return;
    unsaved = 1;
    char subtitle[sizeof(font.name) + 1];
    strncpy(subtitle, font.name, sizeof(font.name) - 1);
    subtitle[strnlen(font.name, sizeof(font.name) - 1)] = '*';
    subtitle[strnlen(font.name, sizeof(font.name) - 1) + 1] = '\0';
    adw_window_title_set_subtitle(titleWidget, subtitle);
    if (btnSave)
        gtk_widget_set_sensitive((GtkWidget *) btnSave, true);
}

void set_active_glyph(struct glyph *glyph) {
    active_glyph = glyph;

    gtk_spin_button_set_value(numWidth, active_glyph->width);
    gtk_spin_button_set_value(numHeight, active_glyph->height);
    gtk_spin_button_set_value(numDescend, active_glyph->descender_offset);

    gtk_drawing_area_set_content_width(drawingArea, active_glyph->width);
    gtk_drawing_area_set_content_height(drawingArea, active_glyph->height);

    gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
}

void on_glyph_changed(GtkComboBox *self, gpointer user_data) {
    unsigned int glyph_id = 0;
    if (sscanf(gtk_combo_box_get_active_id(self), "glyph%3u", &glyph_id) != 1) {
        perror("Glyph ID cannot be parsed.");
        return;
    }
    if (glyph_id > (sizeof(font.glyphs) / sizeof(font.glyphs[0]))) {
        perror("Glyph ID is exceeded upper bound.");
        return;
    }

    set_active_glyph(&font.glyphs[glyph_id]);
}

void do_file_open(char **file) {
    if (read_font(*file, &font) != 0) {
        g_free(*file);
        *file = NULL;
        return;
    }
    adw_window_title_set_subtitle(titleWidget, font.name);
    if (active_glyph != NULL) {
        set_active_glyph(active_glyph); // reload active glyph
    }
    reset_unsaved();
}

void do_gfile_open(GFile *file) {
    if (font_filename)
        g_free(font_filename);
    font_filename = g_file_get_path(file);
    do_file_open(&font_filename);
}

static void on_open_response(GtkDialog *dialog, int response) {
    if (response == GTK_RESPONSE_ACCEPT) {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        g_autoptr(GFile) file = gtk_file_chooser_get_file(chooser);
        do_gfile_open(file);
    }
    gtk_window_destroy(GTK_WINDOW (dialog));
}

GtkWindow *window;

static void open_button(AdwSplitButton *self, gpointer user_data) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    dialog = gtk_file_chooser_dialog_new("Open File", window, action, "Cancel", GTK_RESPONSE_CANCEL, "Open",
                                         GTK_RESPONSE_ACCEPT, NULL);
    gtk_window_present(GTK_WINDOW (dialog));
    g_signal_connect (dialog, "response", G_CALLBACK(on_open_response), NULL);
}

static void save_button(GtkButton *self, gpointer user_data) {
    if (write_font(font_filename, &font) == 0)
        reset_unsaved();
}

static void crop_button(GtkButton *self, gpointer user_data) {
    if (crop_glyph(active_glyph, gtk_spin_button_get_value_as_int(numWidth),
                   gtk_spin_button_get_value_as_int(numHeight)) != 0) {
        // error
        return;
    }
    active_glyph->descender_offset = gtk_spin_button_get_value_as_int(numDescend);
    gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
    set_unsaved();
}


static void draw_function(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer data) {
    if (active_glyph == NULL)
        return;

    cairo_set_matrix(cr, &cr_matrix);

    cairo_rectangle(cr, 0, 0, active_glyph->width, active_glyph->height);
    cairo_set_source_rgb(cr, 1, 1, 1);   /* set fill color */
    cairo_fill(cr);                            /* fill rectangle */

    for (unsigned char gy = 0; gy < active_glyph->height; gy++) {
        for (unsigned char gx = 0; gx < active_glyph->width; gx++) {
            if (active_glyph->bitmap[((gy * ((active_glyph->width + 7) & ~7)) / 8) + (gx / 8)] >> (7 - (gx % 8)) & 1)
                cairo_rectangle(cr, gx, gy, 1, 1);
        }
    }

    cairo_set_source_rgb(cr, 0, 0, 0);   /* set fill color */
    cairo_fill(cr);                            /* fill rectangle */

    cairo_matrix_t ident;
    cairo_matrix_init_identity(&ident);

    cairo_set_matrix(cr, &ident);

    if (cr_matrix.xx >= 6.5) {
        for (unsigned int row = 1; row < active_glyph->height; row++)
            cairo_rectangle(cr, 0, (row * cr_matrix.xx) - 0.5, active_glyph->width * cr_matrix.xx, 1);
        for (unsigned int col = 1; col < active_glyph->width; col++)
            cairo_rectangle(cr, (col * cr_matrix.xx) - 0.5, 0, 1, active_glyph->height * cr_matrix.xx);

        cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);   /* set fill color */
        cairo_fill(cr);

        cairo_rectangle(cr, 0, ((active_glyph->height - active_glyph->descender_offset) * cr_matrix.xx) - 1.5,
                        active_glyph->width * cr_matrix.xx, 3);
        cairo_set_source_rgb(cr, 0.8, 0, 0);   /* set fill color */
        cairo_fill(cr);
        cairo_rectangle(cr, 0,
                        ((active_glyph->height - font.cap_height - active_glyph->descender_offset) * cr_matrix.xx) -
                        1.5, active_glyph->width * cr_matrix.xx, 3);
        cairo_set_source_rgb(cr, 0, 0, 0.8);   /* set fill color */
        cairo_fill(cr);
    }
}


static gboolean on_scroll_event(GtkEventControllerScroll *self, gdouble dx, gdouble dy, gpointer user_data) {
    cairo_matrix_scale(&cr_matrix, 1 - (dy / 2), 1 - (dy / 2));

    gtk_widget_queue_draw(GTK_WIDGET(drawingArea));

    return TRUE;
}


static void on_click_event(GtkGestureClick *gesture, int n_press, double x, double y, gpointer user_data) {
    if (active_glyph) {
        cairo_matrix_t inverse_matrix = cr_matrix;
        if (cairo_matrix_invert(&inverse_matrix) != CAIRO_STATUS_SUCCESS) {
            // Handle the case where the matrix is not invertible
            return;
        }
        cairo_matrix_transform_point(&inverse_matrix, &x, &y);
        int x_int = (int) x;
        int y_int = (int) y;
        if ((0 <= x_int) && (x_int < active_glyph->width) && (0 <= y_int) && (y_int < active_glyph->height)) {
            active_glyph->bitmap[((y_int * ((active_glyph->width + 7) & ~7)) / 8) + (x_int / 8)] ^=
                    1 << (7 - (x_int % 8));
            gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
            set_unsaved();
            printf("X: %lf Y: %lf, %d %d %d %d\n", x, y, x_int, y_int, active_glyph->width, active_glyph->height);
        }
    }
}


static void activate(GtkApplication *app, gpointer user_data) {
    printf("Using GTK v%d.%d.%d\n", GTK_MAJOR_VERSION, GTK_MINOR_VERSION, GTK_MICRO_VERSION);
    /* Construct a GtkBuilder instance and load our UI description */
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "font_editor.ui", NULL);

    /* Connect signal handlers to the constructed widgets. */
    window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));
    gtk_window_set_application(window, app);

    titleWidget = ADW_WINDOW_TITLE(gtk_builder_get_object(builder, "titleWidget"));
    drawingArea = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "drawingArea"));
    GtkEventController *event_controller = gtk_event_controller_scroll_new(GTK_EVENT_CONTROLLER_SCROLL_BOTH_AXES);
    g_signal_connect_object(event_controller, "scroll", G_CALLBACK (on_scroll_event), drawingArea, G_CONNECT_SWAPPED);
    GtkGestureClick *clickGesture = (GtkGestureClick *) gtk_gesture_click_new();
    g_signal_connect(clickGesture, "pressed", G_CALLBACK(on_click_event), NULL);
    gtk_widget_add_controller(GTK_WIDGET(drawingArea), GTK_EVENT_CONTROLLER(clickGesture));
    cairo_matrix_init_scale(&cr_matrix, 25, 25);
    gtk_drawing_area_set_draw_func(drawingArea, draw_function, NULL, NULL);

    GtkComboBoxText *cmbGlyph = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "cmbGlyph"));
    g_signal_connect(cmbGlyph, "changed", G_CALLBACK(on_glyph_changed), NULL);

    for (unsigned int i = 0; i < sizeof(glyph_names) / sizeof(glyph_names[0]); i++) {
        char item_id[6 + 3];
        snprintf(item_id, sizeof(item_id), "glyph%03d", i);
        gtk_combo_box_text_append(cmbGlyph, item_id, glyph_names[i]);
    }

    AdwSplitButton *btnOpen = ADW_SPLIT_BUTTON(gtk_builder_get_object(builder, "btnOpen"));
    g_signal_connect(btnOpen, "clicked", G_CALLBACK(open_button), NULL);

    btnSave = GTK_BUTTON(gtk_builder_get_object(builder, "btnSave"));
    g_signal_connect(btnSave, "clicked", G_CALLBACK(save_button), NULL);

    btnCrop = GTK_BUTTON(gtk_builder_get_object(builder, "btnCrop"));

    numWidth = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "numWidth"));
    numHeight = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "numHeight"));
    numDescend = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "numDescend"));

    g_signal_connect(btnCrop, "clicked", G_CALLBACK(crop_button), NULL);

    gtk_widget_add_controller(GTK_WIDGET (window), event_controller);
    gtk_widget_set_visible(GTK_WIDGET (window), TRUE);

    /* We do not need the builder anymore */
    g_object_unref(builder);
    if (font_filename != NULL)
        do_file_open(&font_filename);
    ui_initialised = TRUE;
}

static void font_editor_open(GApplication *app, GFile **files, int n_files, const char *hint) {
    if (n_files >= 1) {
        if (ui_initialised) {
            // The application is initialized; proceed with file loading
            do_gfile_open(files[0]);
        } else {
            // Defer file loading until after activation
            font_filename = g_file_get_path(files[0]);
        }
    }
    g_application_activate(app);
    for (int i = 1; i < n_files; i++) {
        // TODO: spawn new app process for this file (we can only open one font at once)
    }
}


int main(int argc, char *argv[]) {
#ifdef GTK_SRCDIR
    g_chdir (GTK_SRCDIR);
#endif

    AdwApplication *app = adw_application_new("dev.eddiehart.fm28l_fonteditor", G_APPLICATION_HANDLES_OPEN);
    g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
    g_signal_connect(app, "open", G_CALLBACK(font_editor_open), NULL);

    memset(&font, 0, sizeof(font));

    int status = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);

    return status;
}