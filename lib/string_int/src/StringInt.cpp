
#include <lib/string_int/StringInt.hpp>

#include <iostream>
#include <stdlib.h> // abs

StringInt::StringInt(void) : 
	_num("0"), 
	_negative(false)
{
}

StringInt::StringInt(const int num) : 
	_num(std::to_string(abs(num))),
	_negative(num < 0 ? true : false)
{
}

StringInt::StringInt(const std::string &num_str) : _num(num_str)
{
	//TODO: verify num_str is a valid integer.
	
	if(num_str.empty()) {
		_num = "0";
		_negative = false;
		return;
	}

	_negative = _num[0] == '-';
	if(_negative)
		_num.erase(0, 1);
}

std::string StringInt::get_num(void) const
{
	std::string num = _num;
	if(_negative)
		num.insert(0, 1, '-');

	return num;
}

StringInt StringInt::operator+(const StringInt &rhs)
{
	StringInt val;

	if(_negative != rhs._negative) {
		StringInt tmp_lhs(_num);
		StringInt tmp_rhs(rhs._num);

		if(_negative) {
			val = tmp_rhs - tmp_lhs;	
		} else {
			val = tmp_lhs - tmp_rhs;
		}

	} else {		
			
		std::string sum = "";

		int c = 0;
		size_t n = std::max(_num.size(), rhs._num.size());

		for(size_t ii = 0; ii < n; ++ii) {
			int a = 0;
			if(ii < _num.size())
				a = *(_num.rbegin() + ii) - '0';

			int b = 0;
			if(ii < rhs._num.size())
				b = *(rhs._num.rbegin() + ii) - '0';

			int d = b + a + c;
			if(d >= 10) {
				c = 1;
				d -= 10;
			} else {
				c = 0;
			}
			
			sum.insert(0, std::to_string(d));
		}

		if(c == 1)
			sum.insert(0, std::to_string(1));

		val._num = std::move(sum);
		if(_negative && rhs._negative)
			val._negative = true;	
	}

	val.remove_leading_zeros();
	return val;
}

StringInt StringInt::operator-(const StringInt &rhs)
{
	StringInt val;

	// If rhs is negative. Switch to addition	
	if(rhs._negative)
		return operator+(StringInt(rhs._num));

	// If lhs negative, rhs positive. Add and answer is negative
	if(_negative && !rhs._negative) {
		val = StringInt(_num) + rhs;
		val._negative = true;
	} else {
		std::string x = _num;
		std::string y = rhs._num;

		bool lhs_smaller = StringInt(x) < StringInt(y);
		if(lhs_smaller)
			std::swap(x, y);

		std::string diff = "";
		int c = 0;
		size_t n = x.size();
		
		for(size_t ii = 0; ii < n; ++ii)
		{
			int a = 0;
			if(ii < x.size())
				a = *(x.rbegin() + ii) - '0';
			
			int b = 0;
			if(ii < y.size())
				b = *(y.rbegin() + ii) - '0';

			int d = a - b - c;
			if(d < 0) {
				c = 1;
				d += 10;
			} else {
				c = 0;
			}

			diff.insert(0, std::to_string(d));
		}

		val._num = std::move(diff);
		if(lhs_smaller)
			val._negative = true;	
	}

	val.remove_leading_zeros();
	return val;
}

StringInt StringInt::operator*(const StringInt &rhs)
{
	std::string x = _num;
	std::string y = rhs._num;

	format_numbers(x, y);
	std::string product = karatsuba(x, y);	

	return StringInt(product);
}

bool StringInt::operator==(const StringInt &rhs) const
{
	if(_num.size() != rhs._num.size())
		return false;

	if(_negative != rhs._negative)
		return false;

	for(size_t ii = 0; ii < _num.size(); ++ii)
	{
		if(_num[ii] != rhs._num[ii])
			return false;
	}

	return true;
}

bool StringInt::operator!=(const StringInt &rhs) const
{
	return !operator==(rhs);
}

bool StringInt::operator<(const StringInt &rhs) const
{
	// Can't be equal
	if(operator==(rhs))
		return false;

	// If one number negative and other isn't
	if(_negative && !rhs._negative)
		return true;
	if(!_negative && rhs._negative)
		return false;

	bool lhs_bigger = false;
	if(_num.size() != rhs._num.size()) {
		if(_num.size() > rhs._num.size())
			lhs_bigger = true;
		else
			lhs_bigger = false;
	} else {
		for(size_t ii = 0; ii < _num.size(); ++ii){
			if(_num[ii] != rhs._num[ii]){
				if(_num[ii] > rhs._num[ii])
					lhs_bigger = true;
				else
					lhs_bigger = false;
				break;
			}	
		}		
	}
	
	if(lhs_bigger)
		return _negative;	
	return !_negative;
}

bool StringInt::operator>(const StringInt &rhs) const
{
	return !operator<(rhs) && !operator==(rhs);
}

bool StringInt::operator<=(const StringInt &rhs) const
{
	return operator==(rhs) || operator<(rhs);
}

bool StringInt::operator>=(const StringInt &rhs)  const
{
	return operator==(rhs) || operator>(rhs);
}

std::string StringInt::karatsuba(const std::string &x, const std::string &y)
{
	std::string product = "";
	int n = x.size();

	if(x.size() == 1 || y.size() == 1)
		return multiply_strings(x, y);

	std::string a, b, c, d;
	half(x, a, b);
	half(y, c, d);

	// 1. Compute ac
	std::string ac = karatsuba(a, c);

	// 2. Compute bd
	std::string bd = karatsuba(b, d);

	// 3. Compute (a+b)(c+d)
	StringInt a_s(a);
	StringInt b_s(b);
	StringInt c_s(c);
	StringInt d_s(d);

	StringInt ab_s = a_s + b_s;
	StringInt cd_s = c_s + d_s;
	
	std::string ab_cd = karatsuba(ab_s.get_num(), cd_s.get_num());
	ab_cd.insert(ab_cd.end(), n/2, '0');

	StringInt ab_cd_s(ab_cd);

	// Then 3 - 2 - 1 => ad+bc
	StringInt ad_bc_s = ab_cd_s - StringInt(ac) - StringInt(bd);

	// x*y = 10^n * ac + 10^n/2 * (ad+bc) + bd
	ac.insert(ac.end(), n, '0');
	ad_bc_s._num.insert(ad_bc_s._num.end(), n/2, '0');

	StringInt prod = StringInt(ac) + ad_bc_s + StringInt(bd);
	
	return prod.get_num();
}

void StringInt::half(const std::string &base, std::string &first, std::string &second)
{
	int pos = base.size() / 2;
	first = base.substr(0, pos);
	second = base.substr(pos, base.size());
}

void StringInt::format_numbers(std::string &first, std::string &second)
{
	int size_diff = first.size() - second.size();
	
	if(size_diff > 0)
		second.insert(second.begin(), size_diff, '0');

	if(size_diff < 0)
		first.insert(first.begin(), size_diff-1, '0');
}

std::string StringInt::multiply_strings(const std::string &x, const std::string &y)
{
	if(x.empty() || y.empty())
		return std::to_string(0);

	int a = std::stoi(x);
	int b = std::stoi(y);
	return std::to_string(a*b);
}

void StringInt::remove_leading_zeros(void)
{
	while(_num.front() == '0' && _num.size() > 1)
		_num.erase(0, 1);
}
