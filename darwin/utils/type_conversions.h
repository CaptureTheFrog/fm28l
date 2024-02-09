//
// Created by eddie on 08/02/24.
//

#ifndef FM28L_TYPE_CONVERSIONS_H
#define FM28L_TYPE_CONVERSIONS_H

#include <stdint.h>

#if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define CHAR_PAIR_TO_UINT16_T(c1, c2) ((uint16_t)(((uint8_t)(c1) << 8) | (uint8_t)(c2)))
#define CHAR_QUAD_TO_UINT32_T(c1, c2, c3, c4) ((uint16_t)(((uint8_t)(c1) << 24) | ((uint8_t)(c2) << 16) | ((uint8_t)(c3) << 8) | (uint8_t)(c4)))
#elif defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#define CHAR_PAIR_TO_UINT16_T(c1, c2) ((uint16_t)(((uint8_t)(c2) << 8) | (uint8_t)(c1)))
#define CHAR_QUAD_TO_UINT32_T(c1, c2, c3, c4) ((uint16_t)(((uint8_t)(c4) << 24) | ((uint8_t)(c3) << 16) | ((uint8_t)(c2) << 8) | (uint8_t)(c1)))
#else
#error "Unable to determine system endianness"
#endif

#endif //FM28L_TYPE_CONVERSIONS_H
