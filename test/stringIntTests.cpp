
#include <lib/string_int/StringInt.hpp>

#include <array>
#include <vector>
#include <iostream>

bool StringIntTest(int x, int y, std::string &note);
bool StringIntOperations(int x, int y, std::string &note);
bool CompareNumbers(int x, const StringInt &xs);

struct Result {
	int x;
	int y;
	bool pass;
	std::string detail;
};

int main(int argc, const char* argv[])
{
	std::array<const int, 6> numbers{10, 2813, 3451, 74763, 0, 31};

	std::vector<Result> results;
	for(auto x : numbers) {
		for(auto y : numbers) {
			std::string note = "";
			bool pass = StringIntTest(x, y, note);	
			results.push_back(Result{x, y, pass, note});
		}
	}	
	
	int fails  = 0;
	int passes = 0;

	for(const auto &r : results) {
		if(r.pass)
			passes++;
		else {
			fails++; 
			std::cout << r.detail << std::endl;
		}
	}

	std::cout << "***********" << std::endl;
	std::cout << " Fails: " << fails << std::endl;
	std::cout << "Passes: " << passes << std::endl;
	std::cout << "************" << std::endl;

	return 0;
}

bool StringIntTest(int x , int y, std::string &note) 
{
	// +/+
	std::string note_pp = "";
	bool pp = StringIntOperations(x, y, note_pp);
	if(!pp)
		note += note_pp;

	// +/-
	std::string note_pn = "";
	bool pn = StringIntOperations(x, -y, note_pn);
	if(!pn)
		note += note_pn;
		
	// -/+
	std::string note_np = "";
	bool np = StringIntOperations(-x, y, note_np);
	if(!np)
		note += note_np;	

	// -/-
	std::string note_nn = "";
	bool nn = StringIntOperations(-x, -y, note_nn);
	if(!nn)
		note += note_nn;

	return pp && pn && np && nn;
}

bool StringIntOperations(int x, int y, std::string &note) 
{
	StringInt xs(x);
	StringInt ys(y);

	note += "\n(" + std::to_string(x) + ", " + std::to_string(y) + ")\n";
	note += "-----------\n";

	int z;
	StringInt zs;

	// add
	z = x + y;
	zs = xs + ys;
	bool add = CompareNumbers(z, zs);
	if(!add) {
		note += "Add Failed\n";
		note += " z = " + std::to_string(z) + '\n';
		note += "zs = " + zs.get_num() + '\n';
	}

	// subtract
	z  = x - y;
	zs = xs - ys;
	bool sub1 = CompareNumbers(z, zs);
	if(!sub1) {
		note += "Subtract 1 Failed\n";
		note += " z = " + std::to_string(z) + '\n';
		note += "zs = " + zs.get_num() + '\n';
	}

	z = y - x;
	zs = ys - xs;
	bool sub2 = CompareNumbers(z, zs);
	if(!sub2) { 
		note += "Subtract 2 Failed\n";
		note += " z = " + std::to_string(z) + '\n';
		note += "zs = " + zs.get_num() + '\n';
	}

	// less than
	bool zsc = xs <= ys;
	bool zc = x <= y;
	bool lt = zsc == zc;
	if(!lt)  
		note += "Less than Failed\n";
	

	// greather than	
	zsc = xs >= ys;
	zc  = x >= y;
	bool gt = zsc == zc;
	if(!gt)
		note += "Greater than Failed\n";

	// equal
	zsc = xs == ys;
	zc  = x == y;
	bool eq = zsc == zc;
	if(!eq)
		note += "Equal Failed\n";
	
	note += "-----------\n";

	return add && sub1 && sub2 && lt && gt && eq;
}

bool CompareNumbers(int x, const StringInt &xs)
{
	return xs.get_num().compare(std::to_string(x)) == 0;
}

