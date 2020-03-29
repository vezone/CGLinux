#pragma once

#include "Types.h"

void vstring_set(char* string, char c, i32 length);
i32 vstring_length(const char* str);
/*
compare logic:
*  0 - means left != rigth
*  1 - means left == rigth
*/
i32 vstring_compare(const char* left_string, const char* right_string);
char vstring_to_upperc(char character);
char vstring_to_lowerc(char character);
char* vstring_to_upper(const char* input);
char* vstring_to_lower(const char* input);
i32 vstring_index_of(const char* input, char character);
i32 vstring_index_of_string(const char* input, const char* string);
i32 vstring_last_index_of(const char* input, char character);
const char* vstring_substring(const char* input, i32 start_index);
const char* vstring_substring_range(const char* input, i32 start_index, i32 end_index);
