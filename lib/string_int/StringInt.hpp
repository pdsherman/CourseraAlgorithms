#include <string>

class StringInt 
{
public:
	StringInt(void);
	StringInt(const int num);
	StringInt(const std::string &num_str);

	~StringInt(void) = default;
	
	std::string get_num(void) const;

	StringInt operator+(const StringInt &rhs);
	StringInt operator-(const StringInt &rhs);
	StringInt operator*(const StringInt &rhs);

	bool operator==(const StringInt &rhs) const;
	bool operator!=(const StringInt &rhs) const;
	bool operator<(const StringInt &rhs) const;
	bool operator>(const StringInt &rhs) const;
	bool operator<=(const StringInt &rhs) const;
	bool operator>=(const StringInt &rhs) const;

private:
	std::string karatsuba(const std::string &x, const std::string &y);
	static void half(const std::string &base, std::string &first, std::string &second);
	static void format_numbers(std::string &first, std::string &second);
	static std::string multiply_strings(const std::string &x, const std::string &y);
	void remove_leading_zeros(void);

	std::string _num;

	bool _negative;
};
