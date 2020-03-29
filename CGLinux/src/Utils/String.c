#include "String.h"
#include <stdlib.h>
#include "Logger.h"

void
vstring_set(char* string, char c, i32 length)
{
    i32 i = 0;
    for (; i < length; i++)
    {
        string[i] = c;
    }
}

int32 
vstring_length(const char* str)
{
	i32 index = 0;
	for (; str[index] != '\0'; index++);
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
	i32 i;
	i32 input_length;
	char  element;
	char* result;
	
	if (input == NULL)
	{
		return NULL;
	}
	
	input_length = vstring_length(input);
	result = malloc((input_length + 1) * sizeof(char));
	for (i = 0; i < input_length; i++)
	{
		element = input[i];
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

i32 
vstring_index_of(const char* input, char character)
{
	i32 i;
	i32 input_length;

	if (input == NULL)
	{
		return -1;
	}
	
	input_length = vstring_length(input);
	for (i = 0; i < input_length; i++)
	{
		if (input[i] == character)
		{
			return i;
		}
	}
	
	return -1;
}

i32 
vstring_index_of_string(const char* input, const char* string)
{
	i32 i;
	i32 j;
	i32 flag;
	i32 input_length;
	i32 string_length;
	
	if (input == NULL || string == NULL)
	{
		return -1;
	}
	
	input_length = vstring_length(input);
	string_length = vstring_length(string);

	if (input_length <= 0 ||
		string_length <= 0)
	{
		return -1;
	}
	
	flag = -1;
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

i32 
vstring_last_index_of(const char* input, char character)
{
	i32 i;
	i32 start_index;
	start_index = vstring_length(input) - 1;
    
	if (input == NULL)
	{
		return -1;
	}
	
	for (i = start_index; i >= 0; i--)
	{
		if (input[i] == character)
		{
			return i;
		}
	}
	
	return -1;
}

const char* 
vstring_substring(const char* input, i32 start_index)
{
	i32 i;
	i32 new_length;
	i32 input_length;
	char* result;

	if (input == NULL)
	{
		return NULL;
	}
	
	input_length = vstring_length(input);
	
    if (start_index >= input_length ||
		start_index < 0)
	{
		return NULL;
	}
	
	new_length = input_length - start_index + 1;
	result = malloc((new_length + 1) * sizeof(char));
	for (i = start_index; i < input_length; i++)
	{
		result[i - start_index] = input[i];
	}
	result[new_length] = '\0';

	return (const char*)result;
}

//HERE A BUG
const char* 
vstring_substring_range(const char* input, i32 start_index, i32 end_index)
{
	i32 i;
	i32 input_length;
	i32 new_length;
	char* result;
	
	if (input == NULL)
	{
		return NULL;
	}
	
	input_length = vstring_length(input);
	new_length = end_index - start_index + 1;
	result = malloc((new_length + 1) * sizeof(char));
	
	if (start_index >= input_length || 
		start_index < 0 ||
		end_index >= input_length ||
		end_index <= start_index)
	{
		return NULL;
	}
	
	for (i = start_index; i <= end_index; i++)
	{
		result[i - start_index] = input[i];
	}
	result[new_length] = '\0';
	
	return result;
}
