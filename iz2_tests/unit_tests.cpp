#include "gtest/gtest.h"
#include <iostream>
#include <fstream>

using namespace std;

extern "C"
{
	#include "single_search.h"
	#include "multi_search.h"
}

char *read_file(const string& path, int * str_size)
{
	char *buffer;

	ifstream is;
	is.open(path, ios::binary);

	is.seekg(0, ios::end);
	*str_size = is.tellg();
	is.seekg(0, ios::beg);

	buffer = new char[*str_size];

	is.read(buffer, *str_size);

	is.close();
	return buffer;
}

TEST(testMainFunc, test1)
{
	int str_size = 0;
	char * str = read_file("../../texts/test1.txt", &str_size);
	if(str == nullptr)
		return;

	char * real_str = (char*)"\"Agricultural Basin, which is one of the richest farming areas in the world.\"";

	std::clock_t start_time_single_thread = std::clock();
	char * result_str = find_str(str, str_size);
	std::clock_t end_time_single_thread = std::clock();

	float time_single_thread = ((float)((float)end_time_single_thread - (float)start_time_single_thread)
							   / CLOCKS_PER_SEC) * 1000;

	printf("\n Time (single thread): %f ms\n\n", time_single_thread);

	if(result_str == nullptr)
	{
		delete[] str;
		return;
	}

	for (int i = 0; i < strlen(real_str); ++i)
	{
		ASSERT_EQ(real_str[i], result_str[i]);
	}

	delete[] str;
	free(result_str);
}

TEST(testMainFunc, test2)
{
	int str_size = 0;
	char * str = read_file("../../texts/test1.txt", &str_size);
	if(str == nullptr)
		return;

	char * real_str = (char*)"\"Agricultural Basin, which is one of the richest farming areas in the world.\"";

	std::clock_t start_time_multi_thread = std::clock();
	char * result_str = multi_find_str(str, str_size);
	std::clock_t end_time_multi_thread = std::clock();

	float time_multi_thread = ((float)((float)end_time_multi_thread - (float)start_time_multi_thread)
			/ CLOCKS_PER_SEC) * 1000;

	printf("\n Time (multi thread): %f ms\n\n", time_multi_thread);


	if(result_str == nullptr)
	{
		delete[] str;
		return;
	}

	for (int i = 0; i < strlen(real_str); ++i)
	{
		ASSERT_EQ(real_str[i], result_str[i]);
	}

	delete[] str;
	free(result_str);
}

