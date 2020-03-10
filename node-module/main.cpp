/*
Name: Daniel Herrera
Date: / /
Desc:
*/
#include <iostream>
#include <memory>
#include "../dist/node-mod/node.hpp"
using namespace std;

//==================== DEBUG ADAPTER MODE ===================//
#if _DEBUG
#define BOOST_TEST_MODULE myTests
#include <boost/test/unit_test.hpp>
#pragma warning(push)
#pragma warning(disable : 26812)
#pragma warning(disable : 26495)
BOOST_AUTO_TEST_CASE(case1)
{
	cout << __TIMESTAMP__ << " <==> D.HERRERA.V 0881570\n" << endl;
	Node<int>* node = new dbl_node<int>(1);

	
}//end case1
#endif // DEBUG

//================ RELEASE MODE OPTIMIZATION =================//
#ifndef _DEBUG
int main(int argv, char** argc)
{
	return EXIT_SUCCESS;
}//end doublelinkedlist
#endif // !_DEBUG