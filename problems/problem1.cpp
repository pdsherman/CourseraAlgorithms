
#include <lib/file_ops/FileOperations.hpp>
#include <lib/string_int/StringInt.hpp>

#include <iostream>

inline bool get_numbers(const std::string &filename, std::string &x, std::string &y)
{
	std::cout << "Reading File: " << filename << std::endl;
	std::vector<std::string> lines = get_lines_from_file(filename);

	if(lines.empty() || lines.size() != 2)
		return false;

	x = lines[0];
	y = lines[1];
	return true;
}

int main(int argc, const char* argv[])
{

	if(argc < 2) {
		std::cout << "Invalid number of arguments" << std::endl;
		return -1;
	}
	
	std::string filename(argv[1]);
	std::string x, y;
	if(!get_numbers(filename, x, y)) {
		return -1;	
	}		


	StringInt x_s(x);
	StringInt y_s(y);
	StringInt xy = x_s * y_s;	
	

	std::cout << "****************************" << std::endl;
	std::cout << " " << x << std::endl;
	std::cout << "x" << y << std::endl;
	std::cout << "------------------" << std::endl;

	std::cout << xy.get_num() << std::endl;
	std::cout << "****************************" << std::endl;

	return 0;
}
