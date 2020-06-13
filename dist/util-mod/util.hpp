#pragma once
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <memory>
#include <chrono>
#include <iomanip>

namespace util
{
	/**
	 * \params 
	 */
	template <typename Container>
	constexpr void split(const std::string& str, Container& container, const char delims)
	{
		std::stringstream ss;
		for (auto ch : str)
		{
			if (ch != delims)
				ss << ch;
			else {
				container.push_back(ss.str());
				ss.str(std::string());
			}//end if-else
		}//end for
		if (ss) container.push_back(ss.str());
	}//end split
	
	/**
	 *@author Daniel Herrera
	 *@description csv Class, standard layout class for reading and wriing to a csv.
	 */
	class csv
	{
		std::string fname_cs_ { 0 };
		std::shared_ptr<std::vector<std::vector<std::string>>> solution_{ 
			new std::vector<std::vector<std::string>>
		};
		
	public:
		explicit csv(std::string fn) :
			fname_cs_(std::move(fn)) {}
		~csv() = default;
		
		std::vector<std::vector<std::string>> read_csv() const;
		std::vector<std::vector<std::string>> parse(std::istream& bis) const;
		std::string str() const;
	};

	
	
	/**@author Daniel Herrera
	 * RunTimere Class
	 */
	class RunTimer
	{
	private:
		using time_unit = std::chrono::time_point<std::chrono::steady_clock>;
		
	public:
		// ---------------------------- Construction ---------------------------- */
		explicit RunTimer() = default;
		~RunTimer() = default;

		/* ============================ Inits methods ============================ */
		time_unit start(); /* init on time start using chrono::now */
		time_unit finish(); /* init on time after start */

		/* ---------------------------- Calculationals ---------------------------- */
		/** returns current high resulotion time_point<steady_clock> obj to define current pivot time */
		/* return time elapsed in seconds */
		constexpr auto elapsed() const;
		static constexpr double elapsed(time_unit const& fin, time_unit const& beg);
		static constexpr double elapsed(const long long fin, const long long beg);

		/* ============================ Intervals ============================ */
		long long addPivotTime();

		/* ---------------------------- Accessors ---------------------------- */
		auto getPivotTimes() const { return this->pivot_times_; }
		std::vector<long long> TimeStamps() const;

		
		/* ============================ Construction ============================ */
		/* logs the amount of time a specific task took to complete in milliseconds */
		std::string logging(const std::string& s = "") const;

	private:
		// **** CONSTANTS **** //
		const double TO_MSEC = 1'000'000;

		// **** MEMBERS **** //
		time_unit start_time_point_;
		time_unit end_time_point_;

		// **** Stamp Containers **** //
		std::vector<long long> pivot_times_;
		std::vector<long long> times_stamps_;
	};

	constexpr auto RunTimer::elapsed() const
	{
		const auto t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(
			end_time_point_ - start_time_point_
		);
		return t1.count() / TO_MSEC;
	}

	constexpr double RunTimer::elapsed(time_unit const& fin, time_unit const& beg)
	{
		const auto t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(fin - beg);
		return t1.count() / static_cast<double>(1'000'000); // ~= CONVERT_2_MSECONDS
	}

	constexpr double RunTimer::elapsed(const long long fin, const long long beg)
	{
		return (fin - beg) / static_cast<double>(1'000); // ~= CONVERT_2_MSECONDS
	}
}
