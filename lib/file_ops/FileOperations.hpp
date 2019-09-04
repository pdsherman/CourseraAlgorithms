
#include<string>
#include<vector>

std::vector<std::string> get_lines_from_file(const std::string &filename);

bool get_integers_from_file(const std::string &filename, std::vector<int> &nums);

bool get_integers_from_line(std::string line, std::vector<int>& output);
