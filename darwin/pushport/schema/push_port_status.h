//
// Created by eddie on 12/02/24.
//

#ifndef FM28L_PUSH_PORT_STATUS_H
#define FM28L_PUSH_PORT_STATUS_H

#include "common_types.h"

#define DARWIN_ERRORCODETYPE_MIN_STRING_LENGTH   1
#define DARWIN_ERRORCODETYPE_MAX_STRING_LENGTH   32
#define DARWIN_ERRORCODETYPE_MAX_BYTES_LENGTH   (DARWIN_ERRORCODETYPE_MAX_STRING_LENGTH + 1)
/**
 * \struct ErrorCodeType
 * \brief Error Code Type
 */
typedef struct {
    char string[DARWIN_ERRORCODETYPE_MAX_BYTES_LENGTH];
} ErrorCodeType;

#define DARWIN_ERRORMSGTYPE_MAX_STRING_LENGTH   128
#define DARWIN_ERRORMSGTYPE_MAX_BYTES_LENGTH   (DARWIN_ERRORMSGTYPE_MAX_STRING_LENGTH + 1)
/**
 * \struct ErrorMsgType
 * \brief Error Message Type
 */
typedef struct {
    char string[DARWIN_ERRORMSGTYPE_MAX_BYTES_LENGTH];
} ErrorMsgType;


/**
 * \struct StatusType
 * \brief Status Code Type
 */
typedef struct {
    ErrorMsgType message;
    ErrorCodeType code;
    // todo: add support for anyAttribute here?
} StatusType;

#endif //FM28L_PUSH_PORT_STATUS_H
