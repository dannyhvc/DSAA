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
using namespace std;

// my libraries
#include <dist/double-linked-list-mod/double_linked_list.hpp>
#include <dist/node-mod/node.hpp>
#include <dist/util-mod/util.hpp>


//==================== DEBUG ADAPTER MODE ===================//
#if _DEBUG
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE myTests
#define PRINT std::cout <<
#include <boost/test/unit_test.hpp>

auto r = util::RunTimer();

BOOST_AUTO_TEST_CASE(case1_dbl_ll)
{
	r.start();
	linears_dh::Node<int>* node = new linears_dh::dbl_node<int>(10);
	delete node;
	r.finish();
	cout << __TIMESTAMP__ << " <==> D.HERRERA.V 0881570\n" << endl;
	//
	//
	PRINT r.logging("| case 1: <linears_dh::dbl_node=init-test>") << endl;
}//end case1
						  
BOOST_AUTO_TEST_CASE(case2_dbl_ll)
{
	// test push-back
	// confirm test destructor
	r.start();
	auto* lst1 (new linears_dh::Double_linked_list<int>);	
	lst1->push_back(51);
	lst1->push_back(42);
	lst1->push_back(33);
	lst1->push_back(24);
	lst1->push_back(15);
	
	delete lst1;
	r.finish();
	//
	//
	PRINT r.logging("| case 2: <linears_dh::push_back=D_l_l-test>") << endl;
}

BOOST_AUTO_TEST_CASE(case3_util)
{
	list<string> a;
	size_t i = 0; 
	const string test_to[9] = {"the", "quick", "brown","fox","jumped","over","the","lazy","dog"};
	r.start();
	util::split("the,quick,brown,fox,jumped,over,the,lazy,dog", a, ',');
	for_each(a.begin(), a.end(), [&test_to, &i](auto x) {
		BOOST_CHECK_EQUAL(x, test_to[i]); ++i;
	});
	r.finish();
	//
	//
	PRINT r.logging("| case 3: <util::split-test>") << endl;
}

//TODO: not reading file correctly
BOOST_AUTO_TEST_CASE(case4_util)
{
	r.start();
	shared_ptr<util::csv> my_csv{ new util::csv("util_csv_test1.csv") };
	my_csv->read_csv();
	cout << my_csv->str();
	r.finish();
	//
	//
	PRINT r.logging("| case 4: <util::csv=init+methods-test>") << endl;
}

BOOST_AUTO_TEST_CASE(case5_dbl_ll)
{
	// pop_back test
	r.start();
	auto* str_lst1(new linears_dh::Double_linked_list<string>);
	for (size_t i = 0; i < 10; ++i) 
		str_lst1->push_back("pos" + to_string(i));
	
	str_lst1->pop_back();
	delete str_lst1;
	r.finish();
	//
	//
	PRINT r.logging("| case 5: <linears_dh::pop_back=D_l_l-test>") << endl;
}

BOOST_AUTO_TEST_CASE(case6_dbl_ll)
{
	r.start();
	auto* lst_dbl (new linears_dh::Double_linked_list<double>);
	for (unsigned i = 0; i < 10; ++i)
		lst_dbl->push_front(static_cast<double>(i));
	delete lst_dbl;
	r.finish();
	//
	//
	PRINT r.logging("| case 6: <linears_dh::push_front=D_l_l-test>") << endl;
}

BOOST_AUTO_TEST_CASE(case7_dbl_ll__iter)
{
	//double linked list iterator test
	r.start();
	auto* linked_list(new linears_dh::Double_linked_list<string>);
	string a[] = { "D","A","N","I","E","L" }; unsigned oioioi = 0;
	linked_list->push_back("D");
	linked_list->push_back("A");
	linked_list->push_back("N");
	linked_list->push_back("I");
	linked_list->push_back("E");
	linked_list->push_back("L");
	
	for (auto i = linked_list->begin(); 
		i.operator!=(linked_list->end()); 
		++i) {
		BOOST_CHECK_EQUAL(*i, a[oioioi]); ++oioioi;
	}
	delete linked_list;
	r.finish();
	//
	//
	PRINT r.logging("| case 7: <linears_dh::iter=D_l_l-test>") << endl;
}

BOOST_AUTO_TEST_CASE(case7_dbl_ll)
{
	cout << endl;
	r.start();
	auto* pop_front_list_ut (new linears_dh::Double_linked_list<string>);
	for (auto i = 64; i < 97; ++i)
		pop_front_list_ut->push_back(to_string(i));
	r.restart();
	PRINT r.logging("| case 8: <linears_dh::pop_front-test>") << endl;
	delete pop_front_list_ut;
	r.finish();
	//
	//
	PRINT r.logging("| case 8: <linears_dh::pop_front-test>");
}


#endif // DEBUG

//================ RELEASE MODE OPTIMIZATION =================//
#ifndef _DEBUG
int main(int argv, char** argc)
{
	return EXIT_SUCCESS;
}//end testing
#endif // !_DEBUG
