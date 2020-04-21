#pragma once
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <memory>
#include <chrono>
#include <iostream>

namespace util
{
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
		
		std::vector<std::vector<std::string>> read_csv();
		std::vector<std::vector<std::string>> parse(std::istream& bis);
		std::string str() const;
	};

	class RunTimer
	{
	private:
		using time_unit = std::chrono::steady_clock::time_point;
		time_unit start_time_point_;
		time_unit end_time_point_;
		const double CONVERT_2SECONDS = 1'000'000'000;
		
	public:
		explicit RunTimer() = default;
		~RunTimer() = default;

		/* init on time start using chrono::now */
		auto start() {
			this->start_time_point_ = std::chrono::high_resolution_clock::now();
			return start_time_point_;
		}

		/* init on time after start */
		auto finish() {
			this->end_time_point_ = std::chrono::high_resolution_clock::now();
			return end_time_point_;
		}

		/*
		 * return time elapsed in seconds
		 */
		constexpr auto elapsed() const {
			const auto t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(
				end_time_point_ - start_time_point_
			);
			return t1.count() / CONVERT_2SECONDS;
		}
	};

	
}
