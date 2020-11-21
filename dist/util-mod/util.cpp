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
		_pivot_times.clear(); // get rid of useless recalculations
		this->start_time_point_ = high_resolution_clock::now(); // start time immidiately
		this->add_pivot_time("started"); // log pivot
		return start_time_point_; // ret start time_point
	}//end start

	RunTimer::time_unit RunTimer::start(std::string const& s)
	{
		_pivot_times.clear(); // get rid of useless recalculations
		this->start_time_point_ = high_resolution_clock::now(); // start time immidiately
		this->add_pivot_time(s); // log pivot
		return start_time_point_; // ret start time_point
	}//end start

	RunTimer::time_unit RunTimer::finish()
	{
		this->end_time_point_ = high_resolution_clock::now(); // end time = now time
		this->add_pivot_time("finished"); // log pivot
		if (_pivot_times.size() <= 1)
			return end_time_point_;
		
		// add time stamp diff
		for (size_t i = 0; i < _pivot_times.size() - 1; ++i)
		{
			_times_stamps.push_back(_pivot_times[i + 1] - _pivot_times[i]);
		}
		return end_time_point_; // ret current time_point
	}//end finish

	RunTimer::time_unit RunTimer::finish(std::string const& s)
	{
		this->end_time_point_ = high_resolution_clock::now(); // end time = now time
		this->add_pivot_time(s); // log pivot
		if (_pivot_times.size() <= 1)
			return end_time_point_;

		// add time stamp diff
		for (size_t i = 0; i < _pivot_times.size() - 1; ++i)
			_times_stamps.push_back(_pivot_times[i + 1] - _pivot_times[i]);
		
		return end_time_point_;
	}// end finish

	std::vector<long long> RunTimer::time_stamps() const { return this->_times_stamps; }

	long long RunTimer::add_pivot_time(std::string const& str)
	{
		const auto ms = time_point_cast<nanoseconds>(system_clock::now()).time_since_epoch().count();
		_verbose.push_back(str); // formatting
		_pivot_times.push_back(ms); // add to times for actual use
		return *(_pivot_times.end() - 1); // return last for updated time slot
	}//end addPivotTime

	std::string RunTimer::logging() const
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
		
		for (size_t i = 0; i < _verbose.size(); ++i) 
			///TODO logic error
			/// _verbose > _timestamps and iters don't line up
			oss << _verbose[i] << " " << _times_stamps[i] << " ns" << std::endl; 
		return oss.str();
	}
	
}
