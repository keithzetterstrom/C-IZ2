#ifndef SINGLE_SEARCH_SINGLE_SEARCH_H
#define SINGLE_SEARCH_SINGLE_SEARCH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct max_str
{
	int str_size;
	int right_index;
	int left_index;
};

int mod(int num);
int print_array(int * array, int array_size);
int print_str(char * str, int str_size);
int * init_index_array(const char * str, int str_size, int * array_size);
struct max_str find_biggest_str(const int * index_array, int index_array_size);
char * get_result_str(const char * str, struct max_str result_str_struct);
char * find_str(const char * str, int str_size);

#endif //SINGLE_SEARCH_SINGLE_SEARCH_H
