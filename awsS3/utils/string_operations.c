//
// Created by eddie on 14/02/24.
//
#include "string_operations.h"
#include <malloc.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <ctype.h>
#include <string.h>

void awsS3_utils_lowercase(char* string, size_t n){
    for(size_t i = 0; i < n; i++)
        if(string[i] >= 'A' && string[i] <= 'Z')
            string[i] += ('a' - 'A');
}

char* awsS3_utils_hex(const unsigned char* input, size_t count){
    char* output = malloc((count*2)+1);
    if(output != NULL) {
        for (size_t i = 0; i < count; i++)
            snprintf(output + (i * 2), 3, "%02x", input[i]);
        output[count*2] = '\0';
    }
    return output;
}

char* awsS3_utils_sha256hash(const unsigned char* input, size_t count){
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(input, count, hash);
    return awsS3_utils_hex(hash, SHA256_DIGEST_LENGTH);
}

char* awsS3_utils_hmac_sha256(const unsigned char* input, size_t input_count, const unsigned char* key, size_t key_count){
    unsigned char hmac[SHA256_DIGEST_LENGTH];
    HMAC(EVP_sha256(), key, key_count, input, input_count, hmac, NULL);
    return awsS3_utils_hex(hmac, SHA256_DIGEST_LENGTH);
};

int awsS3_utils_trim(char* string, size_t n, size_t* new_n){
    char* first_non_space;
    for(first_non_space = string; first_non_space < string + n; first_non_space++){
        if(isspace(*first_non_space) == 0)
            break;
    }

    char* last_non_space;
    for(last_non_space = string + n - 1; last_non_space >= string; last_non_space--){
        if(isspace(*last_non_space) == 0)
            break;
    }

    if(last_non_space < first_non_space){
        memset(string, 0, n);
        return 0;
    }

    char* temp = malloc(last_non_space - first_non_space + 2);
    if(temp == NULL)
        return 1;

    strncpy(temp, first_non_space,last_non_space - first_non_space + 1);
    temp[last_non_space - first_non_space + 1] = '\0';

    memset(string, 0, n);
    strncpy(string, temp, last_non_space - first_non_space + 1);
    free(temp);

    if(new_n != NULL)
        *new_n = last_non_space - first_non_space + 1;

    return 0;
}