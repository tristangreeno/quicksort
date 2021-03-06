#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <memory>

// borrowed heavily from: https://gist.github.com/lawliet89/4106929


int generate_random_pivot(int start, int end);

template <typename Iterator>
void quick_sort(Iterator start_iterator, Iterator end_iterator);

int main()
{
	auto input = list_of_numbers;

	quick_sort(input.begin(), input.end());

	return 0;
}

template <typename Iterator>
void quick_sort(Iterator start_iterator, Iterator end_iterator)
{
	const auto size = end_iterator - start_iterator;

	if (size <= 0)
		return; // Base case

	// Partition - in place partitioning that involves only swapping
	// https://class.coursera.org/algo/lecture/preview/22 - O(n) time with no extra memory++
	/*
	Assume pivot is first element of array
	Otherwise swap pivot with first element

	Idea: Array A is in this form
	pivot | < p | > p | unpartitioned/unseen

	Let i = index of the first item > p
	Let j = index of the first item unpartitioned

	Let i = 1
	Let j = 1
	Let p = pivot value

	for j < size
	if A[i] < p
	swap A[j] with A[i]
	i++
	swap A[0] with A[i-1]
	*/
	const auto random_pivot_index = generate_random_pivot(0, size);

	auto pivot = *(start_iterator + random_pivot_index);

	if (random_pivot_index != 0)
		std::swap(*(start_iterator + random_pivot_index), *start_iterator);

	auto i = 1;

	for (auto j = 1; j < size; j++)
	{
		if (*(start_iterator + j) < pivot)
		{
			std::swap(*(start_iterator + j), *(start_iterator + i));
			i++;
		}
	}

	std::swap(*start_iterator, *(start_iterator + i - 1));

	quick_sort(start_iterator, start_iterator + i - 1);
	quick_sort(start_iterator + i, end_iterator);
}

// Generate a number between start and end
int_fast16_t generate_random_pivot(const int start, const int end)
{
	// Seed the randomiser
	srand(time(nullptr));

	return rand() % end + start;
}
