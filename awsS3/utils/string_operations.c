//
// Created by eddie on 14/02/24.
//
#include "string_operations.h"

void awsS3_utils_lowercase(char* string, size_t n){
    for(size_t i = 0; i < n - 1; i++)
        if(string[i] >= 'A' && string[i] <= 'Z')
            string[i] += ('a' - 'A');
};