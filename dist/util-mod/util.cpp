#include "util.hpp"
#include <fstream>
#include <iomanip>

/*
 * let a = function 1, b = function 2
 * a /\ b(x) = a|1 "functional output of the boolean function"
 * b /\ a(x) = b|1
 * if a|1 /\ !(b|1) = a|1 else b|1
 *
 *
#split function python pseudo code
def split(string, delimiters=' \t\n'):
	result = []
	word = ''
	for c in string:
		if c not in delimiters:
			word += c
		elif word:
			result.append(word)
			word = ''

	if word:
		result.append(word)

	return result
 */

namespace util
{
	/**
	 * method used to read and parse the csv file.
	 * \tparam void
	 * \treturn vector of vector, string
	 */
	std::vector<std::vector<std::string>> csv::read_csv()
	{
		std::ifstream ifs(this->fname_cs_, std::ios::binary);
		this->parse(ifs);
		ifs.close();
		return *solution_;
	} //end read_csv

	/**
	 * parse the csv file. each line from the csv corresponds
	 * to an index on the first vector, and each element in the csv
	 * corresponds to a element in the second vector.
	 * 
	 * \tparam void
	 * \treturn vector of vector, string
	 */
	std::vector<std::vector<std::string>> csv::parse(std::istream& bis)
	{
		auto tmp = std::string();
		const auto len = std::count(std::istream::_Iter(bis),
			std::istream::_Iter(), '\n');
		
		for (auto i = 0; i < len || std::getline(bis, tmp); ++i)
			split(tmp, solution_->operator[](i), ','); // pushing back values into solution
		return (*solution_);
	}//end parse

	/**
	 * to string method.
	 * \tparam void
	 * \treturn vector of vector, string
	 */
	std::string csv::str() const
	{
		unsigned counter = 0;
		std::ostringstream oss;
		for (const auto& line_vec : *solution_)	
		{
			for (const auto& basic_str : line_vec)
				oss << counter << std::setw(10) << basic_str << ' ';
			oss << std::endl;
			++counter;
		}
		return oss.str();	
	} //end to_string
}
