#include "ContainerIO.hpp"
#define BOOST_TEST_MODULE CASE_CIO_SUITE_TEST
#include <boost/test/unit_test.hpp>
#include <iostream>
using namespace std;

#ifdef _DEBUG
BOOST_AUTO_TEST_CASE(TIME_STAMP_CASE)
{
	cout << __TIMESTAMP__ << endl;
}
#endif
