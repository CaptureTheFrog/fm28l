//
// Created by eddie on 14/02/24.
//

#ifndef FM28L_STRING_OPERATIONS_H
#define FM28L_STRING_OPERATIONS_H

#include <stddef.h>

void awsS3_utils_lowercase(char* string, size_t n);
char* awsS3_utils_hex(const unsigned char* input, size_t count);
char* awsS3_utils_sha256hash(const unsigned char* input, size_t count);
char* awsS3_utils_hmac_sha256(const unsigned char* input, size_t input_count, const unsigned char* key, size_t key_count);

#endif //FM28L_STRING_OPERATIONS_H
