#ifndef MULTI_SEARCH_MULTI_SEARCH_H
#define MULTI_SEARCH_MULTI_SEARCH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#ifdef IS_MACOS
#include <unistd.h>
#elif IS_LINUX
#include <sys/sysinfo.h>
#endif

typedef struct
{
	int str_size;
	int right_index;
	int left_index;
} max_str_;

typedef struct
{
	int start_index;
	int stop_index;
	int * index_array;
	max_str_ max_str_info;
} thr_data;

int mod_m(int num);
int get_threads_count();
int print_array(int * array, int array_size);
int print_str(char * str, int str_size);
int * multi_init_index_array(const char * str, int str_size, int * array_size);
void * multi_find_biggest_str(void * t_data);
max_str_ find_biggest_str_at_limits(const int * index_array, int threads_count, int array_for_thread_size);
char * multi_get_result_str(const char * str, max_str_ result_str_struct);
char * multi_find_str(const char * str, int str_size);

#endif //MULTI_SEARCH_MULTI_SEARCH_H
