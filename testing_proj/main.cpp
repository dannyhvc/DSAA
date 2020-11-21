/*
Name: Daniel Herrera
Date: / /
Desc:
*/
//standard libs
#include <iostream>
#include <algorithm>
#include <string>
#include <list>

using std::cout;
using std::for_each;
using std::string;
using std::list;
using std::shared_ptr;
using std::to_string;
using std::endl;

// my libraries
#include <dist/double-linked-list-mod/double_linked_list.hpp>
#include <dist/node-mod/node.hpp>
#include <dist/util-mod/util.hpp>
#include <dist/meta-prog-mod/meta_temp.hpp>


//==================== DEBUG ADAPTER MODE ===================//
#if _DEBUG
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE myTests
#define PRINT std::cout <<
#include <boost/test/unit_test.hpp>

auto r = util::RunTimer();

BOOST_AUTO_TEST_CASE(case1_dbl_ll)
{
	r.start("[starting case 1...]");
	linears_dh::Node<int>* node = new linears_dh::dbl_node<int>(10);
	r.add_pivot_time("case 1: node init");
	delete node;
	r.finish("[finished case 1...]");
	cout << __TIMESTAMP__ << " <==> D.HERRERA.V 0881570\n" << endl;
}//end case1
						  
BOOST_AUTO_TEST_CASE(case2_dbl_ll)
{
	// test push-back
	// confirm test destructor
	r.start("[starting case 2...]");
	auto* lst1 (new linears_dh::Double_linked_list<int>);	
	lst1->push_back(51);
	lst1->push_back(42);
	lst1->push_back(33);
	lst1->push_back(24);
	lst1->push_back(15);
	
	delete lst1;
	r.finish("[finished case 2...]");
}

BOOST_AUTO_TEST_CASE(case3_util)
{
	list<string> a;
	size_t i = 0; 
	const string test_to[9] = {"the", "quick", "brown","fox","jumped","over","the","lazy","dog"};
	r.start("[starting case 3...]");
	util::split("the,quick,brown,fox,jumped,over,the,lazy,dog", a, ',');
	for_each(a.begin(), a.end(), [&test_to, &i](auto x) {
		BOOST_CHECK_EQUAL(x, test_to[i]); ++i;
	});
	r.finish("[finished case 3...]");
}

//TODO: not reading file correctly
BOOST_AUTO_TEST_CASE(case4_util)
{
	r.start("[starting case 4...]");
	shared_ptr<util::csv> my_csv{ new util::csv("util_csv_test1.csv") };
	//my_csv->read_csv(); //todo
	cout << my_csv->str();
	r.finish("[finished case 4...]");
}

BOOST_AUTO_TEST_CASE(case5_dbl_ll)
{
	// pop_back test
	r.start("[starting case 5]");
	auto* str_lst1(new linears_dh::Double_linked_list<string>);
	r.add_pivot_time("case 5: init new double linked list...");
	for (size_t i = 0; i < 10; ++i) 
		str_lst1->push_back("pos" + to_string(i));	
	str_lst1->pop_back();
	r.add_pivot_time("case 5: ll push and pop");
	delete str_lst1;
	r.finish("[finished case 5]");
}

BOOST_AUTO_TEST_CASE(case6_dbl_ll)
{
	r.start("[starting case 6...]");
	auto* lst_dbl (new linears_dh::Double_linked_list<double>);
	for (unsigned i = 0; i < 10; ++i)
		lst_dbl->push_front(static_cast<double>(i));
	delete lst_dbl;
	r.finish("[finished case 6...]");
}

BOOST_AUTO_TEST_CASE(case7_dll_iter)
{
	//double linked list iterator test
	r.start("[starting case 7...]");
	auto* linked_list(new linears_dh::Double_linked_list<string>);
	string a[] = { "D","A","N","I","E","L" }; 
	unsigned oioioi = 0;
	linked_list->push_back("D");
	linked_list->push_back("A");
	linked_list->push_back("N");
	linked_list->push_back("I");
	linked_list->push_back("E");
	linked_list->push_back("L");
	r.add_pivot_time("case 7: pre iter check");
	
	for (auto i = linked_list->begin(); i.operator!=(linked_list->end()); ++i)
	{
		BOOST_CHECK_EQUAL(*i, a[oioioi]);
		++oioioi;
	}
	r.add_pivot_time("case 7: post iter init and destruct");
	delete linked_list;
	r.finish("[finished case 7...]");
}

BOOST_AUTO_TEST_CASE(case8_dbl_ll)
{
	cout << endl;
	r.start("[starting case 8...]");
	auto* pop_front_list_ut (new linears_dh::Double_linked_list<string>);
	for (auto i = 64; i < 97; ++i)
		pop_front_list_ut->push_back(to_string(i));

	r.add_pivot_time("| case 8: <linears_dh::pop_front-test>");
	delete pop_front_list_ut;
	r.finish("[finished case 8...]");
}

BOOST_AUTO_TEST_CASE(case9_runtimer_pivot)
{
	r.start("[starting case 9...]");
	for (auto i = 0; i < 100000; ++i);
	r.add_pivot_time("case 9: 100K dead loop");
	for (auto i = 0; i < 10000; ++i);
	r.add_pivot_time("case 9: 10K dead loop");
	for (auto i = 0; i < 1000000; ++i);
	r.add_pivot_time("case 9: 1M dead loop");
	for (auto i = 0; i < 10000; ++i);
	r.finish("[finished case 9...]");
}


// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //


BOOST_AUTO_TEST_CASE(logging_out)
{
	cout << tplate_metaprog::meta_fact<13>::RET << endl;
}

#endif // DEBUG

//================ RELEASE MODE OPTIMIZATION =================//
#ifndef _DEBUG
int main(int argv, char** argc)
{
	return EXIT_SUCCESS;
}//end testing
#endif // !_DEBUG
