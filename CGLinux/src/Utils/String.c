#include "String.h"
#include <stdlib.h>

void
vstring_set(char* string, char c, int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        string[i] = c;
    }
}

int32 
vstring_length(const char* str)
{
	int32 index = 0;
	for (char* ptr = (char*)str; 
		 *ptr != '\0'; 
		 ptr++, index++);
	return index;
}

int32 
vstring_compare(const char* left_string, const char* right_string)
{
	int32 left_string_length = vstring_length(left_string);
	int32 right_string_length = vstring_length(right_string);
	
	if ((left_string_length == 0) 
		||
		(right_string_length == 0))
	{	
		return 0;	
	}
	else if ((left_string_length > right_string_length)
		||
		(left_string_length < right_string_length))
	{
		return 0;
	}
	else 
	{
		for (right_string_length = 0;
			 right_string_length < left_string_length;
			 right_string_length++)
		{
			if (left_string[right_string_length] != right_string[right_string_length])
			{
				return 0;
			}
		}
	}
	return 1;
}

char 
vstring_to_upperc(char character)
{
	if (character >= 'a' && character <= 'z')
		return (character - 'a' + 'A');
	else 
		return character;
}

char 
vstring_to_lowerc(char character)
{
	if (character >= 'A' && character <= 'Z')
		return (character - 'A' + 'a');
	else 
		return character;
}

char* 
vstring_to_upper(const char* input)
{
	int32 i;
	int32 input_length = vstring_length(input);
	char* result = malloc((input_length + 1) * sizeof(char));
	for (i = 0; i < input_length; i++)
	{
		char element = input[i];
		if (element >= 'a' && element <= 'z')
		{
			result[i] = element - 'a' + 'A';
		}
		else
		{
			result[i] = element;
		} 
	}
	result[input_length] = '\0';
	return result;
}

char* 
vstring_to_lower(const char* input)
{
	int32 i;
	int32 input_length = vstring_length(input);
	char* result = malloc((input_length + 1) * sizeof(char));
	for (i = 0; i < input_length; i++)
	{
		char element = input[i];
		if (element >= 'A' && element <= 'Z')
		{
			result[i] = element - 'A' + 'a';
		}
		else
		{
			result[i] = element;
		}
	}
	result[input_length] = '\0';
	return result;
}

int32 
vstring_index_of(const char* input, char character)
{
	int32 i;
	int32 input_length = vstring_length(input);
	for (i = 0; i < input_length; i++)
	{
		if (input[i] == character)
		{
			return i;
		}
	}
	return -1;
}

int32 
vstring_index_of_string(const char* input, const char* string)
{
	int32 input_length = vstring_length(input);
	int32 string_length = vstring_length(string);
	if (input_length > 0)
	{
		int32 i;
		int32 j;
		int8 flag = -1;
		for (i = 0; i < input_length; i++)
		{
			for (j = 0; j < string_length; j++)
			{
				if (input[i + j] == string[j])
				{
					flag = 1;
				}
				else
				{
					flag = -1;
					j = string_length;
				}
			}
			if (flag == 1)
			{
				return i;
			}
		}
		return flag;
	}
	return -1;
}

int32 
vstring_last_index_of(const char* input, char character)
{
	int32 i;
	int32 input_length = vstring_length(input) - 1;
	for (i = input_length; i >= 0; i--)
	{
		if (input[i] == character)
		{
			return i;
		}
	}
	return -1;
}

char* 
vstring_substring(const char* input, int32 start_index)
{
	int32 input_length = vstring_length(input);
	if ((start_index < input_length) && (start_index >= 0))
	{
		int32 i;
		int32 new_length = input_length - start_index + 1;
		char* result = malloc(new_length * sizeof(char));
		for (i = start_index; i <= input_length; i++)
		{
			result[i - start_index] = input[i];
		}
		result[new_length] = '\0';
		return result;
	}
	return "vstring_substring: ERROR";
}

char* 
vstring_substring_range(const char* input, int32 start_index, int32 end_index)
{
	int32 input_length = vstring_length(input);
	if ((start_index < input_length) && 
		(start_index >= 0) && 
		(end_index < input_length) &&
		(end_index > start_index))
	{
		int32 i;
		int32 new_length = end_index - start_index;
		char* result = malloc(new_length * sizeof(char));
		for (i = start_index; i <= end_index; i++)
		{
			result[i - start_index] = input[i];
		}
		result[new_length-1] = '\0';
		return result;
	}
	return "vstring_substring: ERROR";
}