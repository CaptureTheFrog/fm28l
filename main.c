#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <pthread.h>
#include <linux/fb.h>
#include <string.h>
#include <linux/kd.h>
#include <ncurses.h>
#include <signal.h>
#include <time.h>
#include <termios.h>

#include "font.h"
#include "draw.h"
#include "led_image.h"
#include "screen.h"

#define SCROLL_PIXELS_PER_SECOND    63

unsigned char buffer[2][LED_ROWS * LED_COLS / 8];
unsigned char front_buffer_index = 0;

#define FRONT_BUFFER    ((unsigned char *)buffer[front_buffer_index])
#define BACK_BUFFER     ((unsigned char *)buffer[1-front_buffer_index])

struct font header;
struct font regular;
struct font icons;
struct font notice;
struct font notice_bold;
struct font regular_wider;

struct time {
    unsigned char hour;
    unsigned char minute;
};

struct arrival {
    struct time time;
    char station[28];
    unsigned char platform;
    unsigned char delay;
};

unsigned char draw_mode = 1;
unsigned char screen_mode = 0;

int framebuffer;
int stop_refresh = 0;
struct arrival arrivals[10];
struct timespec last_time;
double delta_time;

void init_arrivals() {
    arrivals[0].time.hour = 11;
    arrivals[0].time.minute = 40;
    strncpy(arrivals[0].station, "London Kings X", sizeof(arrivals[0].station));
    arrivals[0].platform = 2;
    arrivals[0].delay = 0;

    arrivals[1].time.hour = 11;
    arrivals[1].time.minute = 45;
    strncpy(arrivals[1].station, "Reading", sizeof(arrivals[1].station));
    arrivals[1].platform = 11;
    arrivals[1].delay = 1;

    arrivals[2].time.hour = 11;
    arrivals[2].time.minute = 50;
    strncpy(arrivals[2].station, "London Kings X", sizeof(arrivals[2].station));
    arrivals[2].platform = 2;
    arrivals[2].delay = 4;

    arrivals[3].time.hour = 11;
    arrivals[3].time.minute = 54;
    strncpy(arrivals[3].station, "Middlesbrough", sizeof(arrivals[3].station));
    arrivals[3].platform = 6;
    arrivals[3].delay = 0;

    arrivals[4].time.hour = 11;
    arrivals[4].time.minute = 55;
    strncpy(arrivals[4].station, "Carlisle", sizeof(arrivals[4].station));
    arrivals[4].platform = 3;
    arrivals[4].delay = 9;

    arrivals[5].time.hour = 11;
    arrivals[5].time.minute = 56;
    strncpy(arrivals[5].station, "Aberdeen", sizeof(arrivals[5].station));
    arrivals[5].platform = 4;
    arrivals[5].delay = 0;

    arrivals[6].time.hour = 12;
    arrivals[6].time.minute = 16;
    strncpy(arrivals[6].station, "Morpeth", sizeof(arrivals[6].station));
    arrivals[6].platform = 8;
    arrivals[6].delay = 0;

    arrivals[7].time.hour = 12;
    arrivals[7].time.minute = 19;
    strncpy(arrivals[7].station, "Liverpool Lime St", sizeof(arrivals[7].station));
    arrivals[7].platform = 5;
    arrivals[7].delay = 16;

    arrivals[8].time.hour = 12;
    arrivals[8].time.minute = 22;
    strncpy(arrivals[8].station, "Carlisle", sizeof(arrivals[8].station));
    arrivals[8].platform = 10;
    arrivals[8].delay = 0;

    arrivals[9].time.hour = 12;
    arrivals[9].time.minute = 24;
    strncpy(arrivals[9].station, "Edinburgh", sizeof(arrivals[9].station));
    arrivals[9].platform = 4;
    arrivals[9].delay = 0;
}

void *refresh_screen(void *arg) {
    // Set up a structure to hold information about the framebuffer
    struct fb_var_screeninfo vinfo;
    ioctl(framebuffer, FBIOGET_VSCREENINFO, &vinfo);

    // Calculate the size of the framebuffer in bytes
    size_t screensize = vinfo.yres_virtual * vinfo.xres_virtual * vinfo.bits_per_pixel / 8;

    // Map the framebuffer into memory
    unsigned char *framebuffer_ptr = (unsigned char *) mmap(NULL, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
                                                            framebuffer, 0);
    while (!stop_refresh) {
        switch (draw_mode) {
            case 0:
                // Draw the LED matrix to the framebuffer
                for (int row = 0; row < LED_ROWS; ++row) {
                    for (int col_block = 0; col_block < LED_COLS / 8; col_block++) {
                        for (char block_index = 0; block_index < 8; block_index++) {
                            size_t position =
                                    ((vinfo.yoffset + row) * vinfo.xres_virtual + (col_block * 8) + block_index) *
                                    (vinfo.bits_per_pixel / 8);
                            *(unsigned int *) (framebuffer_ptr + position) = ((FRONT_BUFFER[(row * LED_COLS / 8) +
                                                                                            col_block] << block_index) &
                                                                              0x80) ? LED_ON_COLOR : LED_OFF_COLOR;
                        }
                    }
                }
                // Wait for a while before refreshing again
                usleep(10000);
                break;
            case 1:
                // Draw the LED matrix to the framebuffer
                for (int row = 0; row < LED_ROWS; ++row) {
                    for (int col_block = 0; col_block < LED_COLS / 8; col_block++) {
                        for (char block_index = 0; block_index < 8; block_index++) {
                            for (int y = 0; y < led_image_height; y++) {
                                for (int x = 0; x < led_image_width; x++) {
                                    size_t position =
                                            ((vinfo.yoffset + (row * led_image_height) + y) * vinfo.xres_virtual +
                                             (((col_block * 8) + block_index) * led_image_width) + x) *
                                            (vinfo.bits_per_pixel / 8);
                                    *(unsigned int *) (framebuffer_ptr + position) = ((FRONT_BUFFER[
                                            (row * LED_COLS / 8) + col_block] << block_index) & 0x80) ? led_image[
                                                                                             (y * led_image_width) + x]
                                                                                                      : 0x000000;
                                }
                            }
                        }
                    }
                }
                // Wait for a while before refreshing again
                usleep(10000);
                break;
        }
    }

    // Unmap the framebuffer
    munmap(framebuffer_ptr, screensize);

    return NULL;
}

void draw_header(const char *text) {
    draw_text_const(BACK_BUFFER, &header, text, 0, 0, left);
    draw_line_horizontal(BACK_BUFFER, 0, LED_COLS - 1, 11, 1);
}

void draw_header_2(const char *text) {
    draw_text_const(BACK_BUFFER, &notice_bold, text, LED_COLS / 2, 0, centre);
    draw_line_horizontal(BACK_BUFFER, 0, LED_COLS - 1, 11, 1);
}

void draw_time_row(unsigned char nti) {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char timeString[9];
    strftime(timeString, sizeof(timeString), "%H:%M:%S", timeinfo);
    draw_line_horizontal(BACK_BUFFER, 0, LED_COLS - 1, LED_ROWS - 11 - (nti & 1), 1);
    draw_text(BACK_BUFFER, &header, timeString, sizeof(timeString), LED_COLS - 2, LED_ROWS - 9, right);
}

void draw_arrivals() {
    draw_header("Arrivals");
    draw_printf(BACK_BUFFER, &regular_wider, LED_COLS - 1, 1, right, "Page %d of %d", 1, 2);
    for (int i = 0; i < (sizeof(arrivals) / sizeof(arrivals[0])); i++) {
        struct arrival *arrival = &arrivals[i];
        draw_printf(BACK_BUFFER, &regular, 1, 14 + (i * 12), left, "%02d:%02d", arrival->time.hour,
                    arrival->time.minute);
        draw_text(BACK_BUFFER, &regular, arrival->station, strnlen(arrival->station, sizeof(arrival->station)), 32,
                  14 + (i * 12), left);
        draw_printf(BACK_BUFFER, &regular, LED_COLS - 49, 14 + (i * 12), right, "%d", arrival->platform);
        if (arrival->delay == 0)
            draw_text_const(BACK_BUFFER, &regular, "On time", LED_COLS - 1, 14 + (i * 12), right);
        else {
            draw_printf(BACK_BUFFER, &regular, LED_COLS - 1, 14 + (i * 12), right, "%02d:%02d",
                        (arrival->time.hour + ((arrival->time.minute + arrival->delay) / 60)) % 24,
                        (arrival->time.minute + arrival->delay) % 60);
        }
    }
    draw_time_row(0);
}

void draw_debug() {
    draw_rectangle(BACK_BUFFER, 0, LED_COLS - 1, 0, 130, outline_only, 1, 0);
    draw_text_const(BACK_BUFFER, &regular, "Display", 4, 2, left);
    draw_text_const(BACK_BUFFER, &regular, "Model", 4, 12, left);
    draw_text_const(BACK_BUFFER, &regular, "Script", 4, 22, left);
    draw_text_const(BACK_BUFFER, &regular, "Version", 4, 32, left);
    draw_text_const(BACK_BUFFER, &regular, "Address", 4, 42, left);
    draw_text_const(BACK_BUFFER, &regular, "IP", 4, 52, left);
    draw_time_row(0);
}

void draw_notice() {
    draw_header_2("Information");
    draw_text_const(BACK_BUFFER, &notice, "Industrial action &", LED_COLS / 2, 20, centre);
    draw_text_const(BACK_BUFFER, &notice, "engineering work is", LED_COLS / 2, 20 + (16 * 1), centre);
    draw_text_const(BACK_BUFFER, &notice, "planned from", LED_COLS / 2, 20 + (16 * 2), centre);
    draw_text_const(BACK_BUFFER, &notice, "Saturday 2 to Saturday", LED_COLS / 2, 20 + (16 * 3), centre);
    draw_text_const(BACK_BUFFER, &notice, "9 December.", LED_COLS / 2, 20 + (16 * 4), centre);
    draw_text_const(BACK_BUFFER, &notice, "CHECK BEFORE YOU TRAVEL", LED_COLS / 2, 20 + (16 * 5), centre);
    draw_time_row(0);
}

double scroll_counter = 0.0;
double toggle_counter = 0.0;
#define TOGGLE_SECONDS  2.0
#define SCROLL_BLANK_SECONDS    0.93

void draw_nti() {
    draw_text_const(BACK_BUFFER, &header, "10:57", 0, 0, left);
    if ((int) (toggle_counter / TOGGLE_SECONDS) % 2)
        draw_text_const(BACK_BUFFER, &header, "Platform 7", LED_COLS - 1, 0, right);
    else
        draw_text_const(BACK_BUFFER, &header, "Expt 11:06", LED_COLS - 1, 0, right);
    draw_text_const(BACK_BUFFER, &header, "Hexham", 0, 14, left);
    draw_text_const(BACK_BUFFER, &regular, "Calling at:", 0, 30, left);
    draw_text_const(BACK_BUFFER, &regular, "Dunston (11:06), MetroCentre (11:09),", 5, 43, left);
    draw_text_const(BACK_BUFFER, &regular, "Blaydon (11:13), Wylam (11:19),", 5, 43 + (12 * 1), left);
    draw_text_const(BACK_BUFFER, &regular, "Prudhoe (11:23), Stocksfield (11:28),", 5, 43 + (12 * 2), left);
    draw_text_const(BACK_BUFFER, &regular, "Riding Mill (11:32), Corbridge (11:36),", 5, 43 + (12 * 3), left);
    draw_text_const(BACK_BUFFER, &regular, "& Hexham (11:41).", 5, 43 + (12 * 4), left);
    draw_text_const(BACK_BUFFER, &regular, "Northern", 0, 43 + (12 * 4) + 20, left);
    draw_text_const(BACK_BUFFER, &regular, "Penalty fares apply on this train, buy before you board.",
                    LED_COLS - scroll_counter, 43 + (12 * 4) + 20 + 12, left);
    draw_time_row(1);

    scroll_counter += delta_time * SCROLL_PIXELS_PER_SECOND;
    toggle_counter += delta_time;
    if ((scroll_counter - get_text_width_const(&regular, "Penalty fares apply on this train, buy before you board.") -
         LED_COLS) / SCROLL_PIXELS_PER_SECOND > SCROLL_BLANK_SECONDS) {
        scroll_counter = 0.0;
    }
}

//                                                                                                                           \/ missing space here is accurate, a real bug!
#define TERMINATED_SCROLL_TEXT "This train will terminate here. Please do not attempt to board this train.   This train is the10:09 TransPennine Express service from Liverpool Lime St status : On time"

void draw_terminate() {
    draw_text_const(BACK_BUFFER, &header, "Terminating train", 0, 14, left);

    draw_text_const(BACK_BUFFER, &regular_wider, "This train finishes", 12, 54, left);
    draw_text_const(BACK_BUFFER, &regular_wider, "its journey here.", 12, 54 + 11, left);

    draw_text_const(BACK_BUFFER, &regular, TERMINATED_SCROLL_TEXT, LED_COLS - scroll_counter, 43 + (12 * 4) + 20 + 12,
                    left);
    draw_time_row(1);

    scroll_counter += delta_time * SCROLL_PIXELS_PER_SECOND;
    toggle_counter += delta_time;
    if ((scroll_counter - get_text_width_const(&regular, TERMINATED_SCROLL_TEXT) - LED_COLS) /
        SCROLL_PIXELS_PER_SECOND > SCROLL_BLANK_SECONDS) {
        scroll_counter = 0.0;
    }
}

void key_press(int ch) {
    if (ch == KEY_F(1)) {
        screen_mode = 0;
    } else if (ch == KEY_F(2)) {
        screen_mode = 1;
    } else if (ch == KEY_F(3)) {
        screen_mode = 2;
    } else if (ch == KEY_F(4)) {
        screen_mode = 3;
    } else if (ch == KEY_F(5)) {
        screen_mode = 4;
    } else if (ch == KEY_F(6)) {
        screen_mode = 5;
        scroll_counter = 0.0;
        toggle_counter = 0.0;
    } else if (ch == KEY_F(7)) {
        screen_mode = 6;
        scroll_counter = 0.0;
        toggle_counter = 0.0;
    } else if (ch == KEY_DOWN) {
        draw_mode = 0;
    } else if (ch == KEY_UP) {
        draw_mode = 1;
    } else if (ch == KEY_END) {
        stop_refresh = 1;
    }
}

void handle_signal(int signo) {
    if (signo == SIGINT) {
        printf("SIGINT");
        stop_refresh = 1;
    }
}

int main() {
    signal(SIGINT, handle_signal);

    initscr(); // Initialize ncurses
    raw();     // Disable line buffering
    keypad(stdscr, TRUE); // Enable special keys (function keys, arrow keys, etc.)
    nodelay(stdscr, TRUE); // Enable non-blocking mode
    curs_set(0); // disable cursor blink

    init_arrivals();

    read_font("header", &header);
    read_font("regular", &regular);
    read_font("icons", &icons);
    read_font("notice", &notice);
    read_font("notice_bold", &notice_bold);
    read_font("regular_wider", &regular_wider);

    // disable tty echo
    struct termios new_termios, old_termios;
    uint8_t reset_tty = 0;
    if (tcgetattr(STDIN_FILENO, &old_termios) == 0) {
        reset_tty = 1;
        new_termios = old_termios;
        new_termios.c_lflag &= ~ECHO;
        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_termios) == -1) {
            perror("Error setting tty attributes");
            return 1;
        }
    }

    // set to graphics mode
    ioctl(STDIN_FILENO, KDSETMODE, KD_GRAPHICS);

    // Open the framebuffer device
    framebuffer = open("/dev/fb0", O_RDWR);
    if (framebuffer == -1) {
        perror("Error opening framebuffer device");
        return 1;
    }

    // Create a thread for refreshing the screen
    pthread_t refresh_thread;
    if (pthread_create(&refresh_thread, NULL, refresh_screen, NULL)) {
        perror("Error creating refresh thread");
        return 1;
    }

    clock_gettime(CLOCK_MONOTONIC, &last_time); // init deltatime counter
    // The main thread can perform other tasks or just wait for the refresh thread to finish
    while (!stop_refresh) {
        // i think it would be preferable to use clock() here, but it seemed to run too fast (?)
        struct timespec time_now;
        clock_gettime(CLOCK_MONOTONIC, &time_now);
        delta_time = ((double) (time_now.tv_sec - last_time.tv_sec)) +
                     ((double) (time_now.tv_nsec - last_time.tv_nsec) / 1e9);
        last_time = time_now;

        int ch = getch(); // Get a character from the user

        if (ch != ERR) {
            key_press(ch);
        }

        fill_screen(BACK_BUFFER, 0);

        switch (screen_mode) {
            case 0:
                draw_arrivals();
                break;
            case 1:
                draw_debug();
                break;
            case 2:
                draw_notice();
                break;
            case 3:
                fill_screen(BACK_BUFFER, 1);
                break;
            case 4:
                fill_screen(BACK_BUFFER, 0);
                for (int i = 0; i < LED_COLS; i += 10) {
                    draw_line_vertical(BACK_BUFFER, i, 0, LED_ROWS - 1, 1);
                }
                for (int i = 0; i < LED_ROWS; i += 10) {
                    draw_line_horizontal(BACK_BUFFER, 0, LED_COLS - 1, i, 1);
                }
                break;
            case 5:
                draw_nti();
                break;
            case 6:
                draw_terminate();
                break;
        }

        // swap buffers
        front_buffer_index = 1 - front_buffer_index;
    }

    // Wait for the refresh thread to finish
    pthread_join(refresh_thread, NULL);

    // Close the framebuffer device
    close(framebuffer);
    endwin();

    ioctl(STDIN_FILENO, KDSETMODE, KD_TEXT);
    if (reset_tty) {
        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_termios) == -1) {
            perror("Error resetting tty attributes");
            return 1;
        }
    }

    return 0;
}