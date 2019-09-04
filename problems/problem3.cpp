#include <lib/file_ops/FileOperations.hpp>

#include <algorithm> // iter_swap
#include <iostream>

//#define DEBUG

using iter = std::vector<int>::iterator;

static unsigned long comparisons = 0;

enum PIVOT_CHOICE{START, END, MEDIAN};
static PIVOT_CHOICE pivot_choice = PIVOT_CHOICE::MEDIAN;

iter GetPivot(std::vector<int> &array, iter start, iter end);
void Partition(std::vector<int> &array, iter start, iter end, iter &pivot);
void Quicksort(std::vector<int> &array, iter start, iter end);

int main(int argc, const char* argv[])
{
	if(argc < 2) {
		std::cout << "Invalid number of arguments" << std::endl;
		std::cout << "Please include filename." << std::endl;
		return -1;
	}

	std::string filename(argv[1]);
	std::vector<int> array2sort;
	if(!get_integers_from_file(filename, array2sort)) {
		return -1;	
	}		

	std::vector<int> vec_start = array2sort;
	std::vector<int> vec_end = array2sort;
	std::vector<int> vec_med = array2sort;

#ifdef DEBUG
	std::cout << "** QUICKSORT ON ARRAY **" << std::endl;
	for(iter ii = vec_start.begin(); ii < vec_start.end(); ++ii)
		std::cout << *ii << " ";
	std::cout << std::endl;
#endif

	comparisons = 0;
	pivot_choice = PIVOT_CHOICE::START;
	Quicksort(vec_start, vec_start.begin(), vec_start.end());
	std::cout << "Comparisons: " << comparisons << std::endl;

	comparisons = 0;
	pivot_choice = PIVOT_CHOICE::END;
	Quicksort(vec_end, vec_end.begin(), vec_end.end());
	std::cout << "Comparisons: " << comparisons << std::endl;

	comparisons = 0;
	pivot_choice = PIVOT_CHOICE::MEDIAN;
	Quicksort(vec_med, vec_med.begin(), vec_med.end());
	std::cout << "Comparisons: " << comparisons << std::endl;

#ifdef DEBUG
	std::cout << "** SORTED ARRAY **" << std::endl;
	for(iter ii = vec_start.begin(); ii < vec_start.end(); ++ii)
		std::cout << *ii << " ";
	std::cout << std::endl;
#endif


	return 0;
}

void Quicksort(std::vector<int> &array, iter start, iter end)
{
	if(start == end)
		return;

	// Get Pivot. TODO: Put Pivot at front of vector.
	iter pivot = GetPivot(array, start, end);
	std::iter_swap(pivot, start);
	pivot = start;

	// Partition Array
	Partition(array, start, end, pivot);
	comparisons += end - start - 1;

	// Recurse on each partitioned section
	Quicksort(array, start, pivot);
	Quicksort(array, pivot+1, end);
}

iter GetPivot(std::vector<int> &array, iter start, iter end)
{
	iter pivot, med;
	switch(pivot_choice) {
	case PIVOT_CHOICE::END:
		pivot = end - 1;
		break;
	case PIVOT_CHOICE::MEDIAN:
		med = start + (end - start - 1)/2;

		if((*start < *med && *start > *(end-1)) ||
				(*start < *(end-1) && *start > *med)){
			pivot = start;	
		} else if((*med < *start && *med > *(end-1)) ||
				(*med < *(end-1) && *med > *start)) {
			pivot = med;
		} else {
			pivot = end - 1;
		}
		break;
	case PIVOT_CHOICE::START:
	default:
		pivot = start;	
	}

	return pivot;
}

void Partition(std::vector<int> &array, iter start, iter end, iter &pivot)
{
	iter i = start + 1;	
	for(iter j = start + 1; j < end; ++j) {
		if(*j < *pivot)	{	
			std::iter_swap(i, j);
			++i;
		}
	}
	std::iter_swap(pivot, i-1);
	pivot = i-1;
}


