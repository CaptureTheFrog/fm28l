#ifndef FM28L_MIN_H
#define FM28L_MIN_H

#define MIN(x, y) ({                 \
        __typeof__(x) _x = (x);       \
        __typeof__(y) _y = (y);       \
        _x < _y ? _x : _y;            \
    })

#endif //FM28L_MIN_H
