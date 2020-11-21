#pragma once
#include <boost/multiprecision/cpp_int.hpp>

namespace tplate_metaprog
{
	typedef boost::multiprecision::cpp_int Int;
	// compile time factorial
	template<unsigned long long N>
	struct meta_fact {
		enum { RET = N * meta_fact<N - 1>::RET};
	};
	template<> //breaks the recursize compile loop
	struct meta_fact<0> { enum { RET = 1 }; };
}
