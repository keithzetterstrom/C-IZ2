#include "../include/multi_search.h"


int mod_m(int num)
{
	if (num >= 0)
		return num;
	if (num < 0)
		return num * (-1);
	return -1;
}


int get_threads_count()
{
	int count_threads = get_nprocs();
	return count_threads;
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


int * multi_init_index_array(const char * str, int str_size, int * array_size)
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


void * multi_find_biggest_str(void * t_data)
{
	thr_data * data = (thr_data*)t_data;
	max_str_ result_struct = { 0, 0, 0 };
	int tmp = 0;
	for (int i = data->start_index; i < data->stop_index; ++i)
	{
		if (data->index_array[i] < 0)
		{
			tmp = mod_m(data->index_array[i + 1]) - mod_m(data->index_array[i]) + 1;
			if (result_struct.str_size < tmp)
			{
				result_struct.str_size = tmp;
				result_struct.left_index = mod_m(data->index_array[i]) - 1;
				result_struct.right_index = mod_m(data->index_array[i + 1]) - 1;
			}
		}
	}
	data->max_str_info = result_struct;
	return NULL;
}


max_str_ find_biggest_str_at_limits(const int * index_array, int threads_count, int array_for_thread_size)
{
	int tmp = 0;
	max_str_ result_struct = { 0, 0, 0 };
	for (int i = array_for_thread_size; i < threads_count; i += array_for_thread_size)
	{
		if(index_array[i - 1] < 0)
		{
			tmp = mod_m(index_array[i]) - mod_m(index_array[i - 1]) + 1;
			if(result_struct.str_size < tmp)
			{
				result_struct.str_size = tmp;
				result_struct.left_index = mod_m(index_array[i - 1]) - 1;
				//result_struct.right_index = mod(index_array[i + 1]) - 1;
			}
		}
	}
	return result_struct;
}


char * multi_get_result_str(const char * str, max_str_ result_str_struct)
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


char * multi_find_str(const char * str, int str_size)
{
	int threads_count = get_threads_count();
	int array_size = 0;

	int * array = multi_init_index_array(str, str_size, &array_size);

	int array_for_thread_size = array_size / threads_count;

	pthread_t * threads = (pthread_t*) malloc(threads_count * sizeof(pthread_t));
	thr_data * thread_data = (thr_data*) malloc(threads_count * sizeof(thr_data));

	for(int i = 0; i < threads_count; i++)
	{
		thread_data[i].index_array = array;
		thread_data[i].start_index = i * array_for_thread_size;
		thread_data[i].stop_index = (i + 1) * array_for_thread_size;

		pthread_create(&(threads[i]), NULL, multi_find_biggest_str, &thread_data[i]);
	}

	for(int i = 0; i < threads_count; i++)
		pthread_join(threads[i], NULL);

	max_str_ max_str_struct = find_biggest_str_at_limits(array, threads_count, array_for_thread_size);

	for (int i = 0; i < threads_count; ++i)
	{
		if(thread_data[i].max_str_info.str_size > max_str_struct.str_size)
		{
			max_str_struct = thread_data[i].max_str_info;
		}
	}

	free(threads);
	free(thread_data);
	free(array);

	char * result_str = multi_get_result_str(str, max_str_struct);
	print_str(result_str, max_str_struct.str_size);
	return result_str;
}