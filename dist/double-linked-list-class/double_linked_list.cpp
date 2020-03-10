#include "double_linked_list.hpp"
using namespace std;

template <class Ty>
Double_linked_list<Ty>::Double_linked_list(const_pointer& nod, function<void(const_pointer val)> func)
{
	func(nod);
}

template <class Ty>
Double_linked_list<Ty>::Double_linked_list(const_pointer& h, const_pointer& t,
	function<void(const_pointer val)> func1,
	function<void(const_pointer val)> func2)
{
	func1(h), func2(t);
}

template <class Ty>
Double_linked_list<Ty>::~Double_linked_list()
{
	pointer walk = this->begin();
	while (this->walk->next != nullptr)
	{
			walk = walk->next;
			delete walk->prev;
	}
}
