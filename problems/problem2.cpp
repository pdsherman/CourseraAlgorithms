#include <lib/file_ops/FileOperations.hpp>

#include <iostream>

template<typename T>
void print_vector(std::vector<T> &vec)
{
	for(auto &x : vec)
		std::cout << x << std::endl;
}

template<typename T>
void split_vector(const std::vector<T> &base, std::vector<T> &first, std::vector<T> &second)
{
	int n = base.size();	
	first.assign(base.begin(), base.begin() + n/2);
	second.assign(base.begin() + n/2, base.end());
}

unsigned long int split_inversions(std::vector<int> &base, std::vector<int> &left, std::vector<int> &right)
{
	using iter = std::vector<int>::iterator;

	size_t size_l = left.size();
	size_t size_r = right.size();

	size_t li = 0;
	size_t ri = 0;
	
	unsigned long int ins = 0;
	for(iter bi = base.begin(); bi != base.end(); ++bi) {
		if(li < size_l && ri < size_r) {
			if(left[li] <= right[ri]) {
				*bi = left[li];
				++li;	
			} else {
				*bi = right[ri];
				++ri;
				ins += size_l - li;
			}
		} else if(li == size_l) {
			*bi = right[ri];
			++ri;
		} else if (ri == size_r) {
			*bi = left[li];
			++li;
		}

	}

	return ins;;
}

unsigned long int inversions(std::vector<int> &array)
{
	if(array.size() == 1 || array.size() == 0)
		return 0;

	std::vector<int> left;
	std::vector<int> right;
	split_vector(array, left, right);

	unsigned long int linversions = inversions(left);  // Inversions in left side
	unsigned long int rinversions = inversions(right); // Inversions in right side
	unsigned long int sinversions = split_inversions(array, left, right); // Split Inversions

	return linversions + rinversions + sinversions;
}


int main(int argc, const char* argv[])
{

	if(argc < 2) {
		std::cout << "Invalid number of arguments" << std::endl;
		std::cout << "Please include filename." << std::endl;
		return -1;
	}

	std::vector<int> x;

	std::string filename(argv[1]);
	if(!get_integers_from_file(filename, x)) {
		return -1;	
	}		

	unsigned long int ins = inversions(x);

	std::cout << "****************************" << std::endl;
	std::cout << "Inversions: " << ins << std::endl;

	return 0;
}
