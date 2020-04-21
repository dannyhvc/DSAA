/*
Name: Daniel Herrera
Date: / /
Desc:
*/
//standard libs
#include <iostream>
#include <algorithm>
#include <chrono>
#include <string>
#include <list>
using namespace std;

// my libraries
#include <dist/double-linked-list-mod/double_linked_list.hpp>
#include <dist/node-mod/node.hpp>
#include <dist/util-mod/util.hpp>


//==================== DEBUG ADAPTER MODE ===================//
#if _DEBUG
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE myTests
#include <boost/test/unit_test.hpp>
#pragma warning(push)
#pragma warning(disable : 26812)
#pragma warning(disable : 26495)
auto r = util::RunTimer();

BOOST_AUTO_TEST_CASE(case1dbl_ll)
{
	linears_dh::Node<int>* node = new linears_dh::dbl_node<int>(10);
	delete node;
	cout << __TIMESTAMP__ << " <==> D.HERRERA.V 0881570\n" << endl;
}//end case1

//BOOST_AUTO_TEST_CASE(case2dbl_ll)
//{
//	// test push-back
//	// confirm test destructor
//	linears_dh::Double_linked_list<int>::pointer_type lst(
//		new linears_dh::Double_linked_list<int>);
//	lst->push_back(51);
//	lst->push_back(42);
//	lst->push_back(33);
//	lst->push_back(24);
//	lst->push_back(15);
//}

BOOST_AUTO_TEST_CASE(case3)
{
	list<string> a;
	size_t i = 0;
	const string TEST_TO[9] = {"the", "quick", "brown","fox","jumped","over","the","lazy","dog"};
	r.start();
	util::split("the,quick,brown,fox,jumped,over,the,lazy,dog", a, ',');
	for_each(a.begin(), a.end(), [&TEST_TO, &i](auto x) {
		BOOST_CHECK_EQUAL(x, TEST_TO[i]); ++i;
	});
	r.finish();
	cout << "case 3 took -> " << r.elapsed() << " seconds" << endl;
	
}

BOOST_AUTO_TEST_CASE(case4)
{
	r.start();
	shared_ptr<util::csv> my_csv{ new util::csv("util_csv_test1.csv") };
	my_csv->read_csv();
	cout << my_csv->str();
	r.finish();
	cout << "case 4 took -> " << r.elapsed() << " seconds" << endl;
}
#endif // DEBUG

//================ RELEASE MODE OPTIMIZATION =================//
#ifndef _DEBUG
int main(int argv, char** argc)
{
	return EXIT_SUCCESS;
}//end testing
#endif // !_DEBUG
