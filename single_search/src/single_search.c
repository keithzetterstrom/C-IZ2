#include "../include/single_search.h"

int mod(int num)
{
	if (num >= 0)
		return num;
	if (num < 0)
		return num * (-1);
	return -1;
}


int print_array(int * array, int array_size)
{
	if(array == NULL)
		return -1;

	for (int i = 0; i < array_size; ++i)
	{
		printf("%i, ", array[i]);
	}
	printf("\n");
	return 0;
}


int print_str(char * str, int str_size)
{
	if(str == NULL)
		return -1;

	for (int i = 0; i < str_size; ++i)
	{
		printf("%c", str[i]);
	}
	printf("\n");
	return 0;
}


int * init_index_array(const char * str, int str_size, int * array_size)
{
	if(str == NULL)
		return NULL;

	int * index_array = (int * )malloc(sizeof(int) * str_size);
	if(index_array == NULL)
	{
		free(index_array);
		return NULL;
	}

	int index_array_size = 0;

	for (int i = 0; i < str_size; ++i)
	{
		if(str[i] == '\"')
		{
			if(str[i+1] >= 65 && str[i+1] <= 90)
			{
				index_array[index_array_size] = (i + 1) * (-1);
				index_array_size++;
				continue;
			}
			index_array[index_array_size] = i + 1;
			index_array_size++;
		}
	}
	int * new_array = (int *)(realloc(index_array, index_array_size * sizeof(int)));
	if (new_array == NULL)
		return NULL;
	else
		index_array = new_array;

	*array_size = index_array_size;
	return index_array;
}


struct max_str find_biggest_str(const int * index_array, int index_array_size)
{
	struct max_str result_struct = {0, 0, 0};
	int tmp = 0;
	for (int i = 0; i < index_array_size - 1; ++i)
	{
		if(index_array[i] < 0)
		{
			tmp = mod(index_array[i+1]) - mod(index_array[i]) + 1;
			if(result_struct.str_size < tmp)
			{
				result_struct.str_size = tmp;
				result_struct.left_index = mod(index_array[i]) - 1;
				result_struct.right_index = mod(index_array[i + 1]) - 1;
			}
		}
	}

	return result_struct;
}


char * get_result_str(const char * str, struct max_str result_str_struct)
{
	char * result_str = (char * )malloc(sizeof(int) * result_str_struct.str_size);
	if(result_str == NULL)
		return NULL;
	for (int i = 0, j = result_str_struct.left_index; i < result_str_struct.str_size; ++i, ++j)
	{
		result_str[i] = str[j];
	}
	return result_str;
}


char * find_str(const char * str, int str_size)
{
	int index_array_size = 0;

	int * index_array = init_index_array(str, str_size, &index_array_size);
	if(index_array == NULL)
		return NULL;

	struct max_str result_str_struct = find_biggest_str(index_array, index_array_size);

	char * result_str = get_result_str(str, result_str_struct);
	if(result_str == NULL)
	{
		free(index_array);
		return NULL;
	}

	if(print_str(result_str, result_str_struct.str_size))
	{
		free(index_array);
		return NULL;
	}

	free(index_array);
	return result_str;
}