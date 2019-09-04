
#include <lib/file_ops/FileOperations.hpp>

#include <unistd.h>
#include <fstream>
#include <iostream>

std::vector<std::string> get_lines_from_file(const std::string &filename)
{
	std::vector<std::string> lines;
	std::ifstream infile(filename);
	if(!infile) {
		std::cout << "Error opening/reading input file: " << filename << std::endl;
	} else {
		std::string l;
		while(std::getline(infile, l))
			lines.push_back(l);
	}

	return lines;
}

bool get_integers_from_file(const std::string &filename, std::vector<int> &nums)
{
	std::vector<std::string> lines = get_lines_from_file(filename);

	if(lines.empty()) {
		std::cout << "File retured zero lines during read." << std::endl;
		return false;
	}

	nums.clear();
	for(auto &line : lines)
		nums.push_back(std::stoi(line));

	return true;
}

bool get_integers_from_line(std::string line, std::vector<int>& output) 
{
	output.clear();

	std::size_t found_ws  = line.find_first_not_of("0123456789");
	std::size_t found_num = line.find_first_of("0123456789");

	while(found_num != std::string::npos) {
		if(found_num < found_ws) {
			std::string num_str;

			if(found_ws == std::string::npos) { 
				num_str = line;
				line.clear();
			} else {
				num_str = line.substr(found_num, found_num + found_ws);
				line.erase(0, found_num + found_ws + 1);	
			}

			output.push_back(std::stoi(num_str));
			
		} else if(found_ws < found_num) {
			line.erase(0, found_ws+1);
		} else {

		}

		found_ws  = line.find_first_not_of("0123456789");
		found_num = line.find_first_of("0123456789");
	}

	return true;
}

