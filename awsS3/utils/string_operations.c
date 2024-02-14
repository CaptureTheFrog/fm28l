//
// Created by eddie on 14/02/24.
//
#include <malloc.h>
#include "string_operations.h"

void awsS3_utils_lowercase(char* string, size_t n){
    for(size_t i = 0; i < n - 1; i++)
        if(string[i] >= 'A' && string[i] <= 'Z')
            string[i] += ('a' - 'A');
};

char* awsS3_utils_hex(char* input, size_t n){
    char* output = malloc(((n-1)*2)+1);
    if(output != NULL) {
        for (size_t i = 0; i < n - 1; i++)
            snprintf(output + (i * 2), 3, "%02x", input[i]);
        output[((n-1)*2)+1] = '\0';
    }
    return output;
};