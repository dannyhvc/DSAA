#include "util.hpp"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <numeric>


namespace util
{
	/**
	 * -------------------------- CLASS <RUNTIMER> --------------------------
	 */
	
	/**
	 * method used to read and parse the csv file.
	 * \tparam void
	 * \treturn vector of vector, string
	 */
	std::vector<std::vector<std::string>> csv::read_csv() const
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
	std::vector<std::vector<std::string>> csv::parse(std::istream& bis) const
	{
		auto tmp = std::string();
		const auto len = std::count(std::istream::_Iter(bis), std::istream::_Iter(), '\n');
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

	/**
	 * -------------------------- CLASS <RUNTIMER> --------------------------
	 */
	using namespace std::chrono;
	
	RunTimer::time_unit RunTimer::start()
	{
		pivot_times_.clear();
		this->start_time_point_ = high_resolution_clock::now();
		this->addPivotTime();
		return start_time_point_;
	}

	RunTimer::time_unit RunTimer::finish()
	{
		this->end_time_point_ = high_resolution_clock::now();
		this->addPivotTime();
		if (pivot_times_.size() > 1)
			this->times_stamps_ = std::vector<long long>(this->pivot_times_.size() - 1);
		for (auto i = 0; i < times_stamps_.size(); ++i)
			times_stamps_[i] = pivot_times_[i + 1] - pivot_times_[i];
		return end_time_point_;
	}

	std::vector<long long> RunTimer::TimeStamps() const
	{
		return this->times_stamps_;
	}

	/**
	 * ~addPivotTime~
	 * object method to describe the time elaspsed from previous exec to final exec
	 *
	 * @returns double
	 */
	long long RunTimer::addPivotTime()
	{
		/*double reduce = 0.0;
		std::for_each(pivot_times_.begin(), pivot_times_.end(), 
			[&reduce](auto elem) {
				reduce += elem;
			}
		);*/
		const auto ms = time_point_cast<nanoseconds>(system_clock::now()).time_since_epoch().count();
		pivot_times_.push_back(ms);
		return *(pivot_times_.end() - 1);
	}//end addPivotTime

	std::string RunTimer::logging(const std::string& s) const
	{
		/**
		 * logging conventions:
		 *		| "name": 
		 *		<namespace::("test conjugate"_1+"test conjugate"_2="class abreviation")-test>
		 *
		 *	if global method:
		 *		<namespace::"method(s) name"-test>
		 *	elif multi paradigm test:
		 *		<"test culture brief"::"pass/fail expected"-test>
		 */
		std::ostringstream oss;
		oss << std::setprecision(5) << std::fixed << elapsed() << "ms " << s;
		return oss.str();
	}
}
