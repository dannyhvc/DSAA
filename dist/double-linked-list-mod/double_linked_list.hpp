#pragma once
//#include <functional>
#include "../node-mod/node.hpp"
#include <algorithm>

/**
 * \brief 
 */
namespace linears_dh
{
	template <typename _Ty>	class
	Double_linked_list : protected dbl_node<_Ty>
	{
		using __pointer_t = dbl_node<_Ty>*;
		using __const_pointer_t = const dbl_node<_Ty>*;

	public:
		using pointer_type = std::shared_ptr<Double_linked_list<_Ty>>;
		using const_pointer_type = const std::shared_ptr<Double_linked_list<_Ty>>;

		// ============== ITERATOR SPECIFIERS ============== //
#if 1
		class iterator
		{
			using __pointer_t = dbl_node<_Ty>*;
			using __const_pointer_t = const dbl_node<_Ty>*;
			__pointer_t _pointer_node{ nullptr };
		public:
			explicit iterator(const iterator& it)
				: _pointer_node(it._pointer_node) { }
			explicit iterator() = default;
			explicit iterator(const __pointer_t& cpn)
				: _pointer_node(cpn) { }
			~iterator() = default;

			// operator overloading
			iterator& operator=(__const_pointer_t& pnode);
			//iterator& operator=(const iterator& pnode);

			iterator& operator++ (); //prefix
			iterator& operator++ (int); //postfix

			iterator& operator-- (); //postfix
			iterator& operator-- (int); //postfix

			iterator& operator+ (const size_t val) noexcept;
			iterator& operator- (const size_t val) noexcept;

			constexpr bool operator == (const iterator& rhs);
			constexpr bool operator != (const iterator& rhs);
		};
		friend class iterator;
		
		//iterating class super method
		// -> iterator to the top of the list
		iterator begin() const { return iterator(this->_head); }
		// leads to the end of the list
		iterator end() const { return iterator(nullptr); }
#endif
		
		// ============== DOUBLE LINKED LIST CLASS SPECIFIERS ============== //
		Double_linked_list() = default;
		explicit Double_linked_list(
			const iterator& beginning, 
			const iterator& ending
		);
		explicit Double_linked_list(const Double_linked_list& lst);
		~Double_linked_list();

		// stretcher methods
		constexpr size_t size() const { return {_size}; }
		constexpr bool is_empty() const { return {_size == 0}; }
		void push_back(_Ty val);
		

	private:
		// list node mutatbles
		__pointer_t _head { nullptr };
		__pointer_t _tail { nullptr };
		unsigned	_size { 0 };
	};
	
} 


namespace linears_dh
{
#if 1
	template <typename _Ty>
	constexpr bool Double_linked_list<_Ty>::iterator::operator==(const iterator& rhs) {
		return reinterpret_cast<const void*>(this) == reinterpret_cast<const void*>(rhs);
	}

	template <typename _Ty>
	constexpr bool Double_linked_list<_Ty>::iterator::operator!=(const Double_linked_list::iterator& rhs) {
		return reinterpret_cast<const void*>(this) != reinterpret_cast<const void*>(rhs);
	}

	template <typename _Ty>
	auto Double_linked_list<_Ty>::iterator::operator=(
		     __const_pointer_t& pnode) ->iterator& {
		return &iterator{ pnode };
	}

	template <typename _Ty>
	typename Double_linked_list<_Ty>::iterator& Double_linked_list<_Ty>::iterator::operator++()
	{
		if (this->_pointer_node)
			_pointer_node = _pointer_node->next;
		return *this;
	}

	template <typename _Ty>
	typename Double_linked_list<_Ty>::iterator& 
		Double_linked_list<_Ty>::iterator::operator++(int)
	{
		iterator temp = *this;
		++* this;
		return &iterator{ temp };
	}

	template <typename _Ty>
	typename Double_linked_list<_Ty>::iterator& 
		Double_linked_list<_Ty>::iterator::operator--()
	{
		if (this->_pointer_node)
			_pointer_node = _pointer_node->prev;
		return *this;
	}

	template <typename _Ty>
	typename Double_linked_list<_Ty>::iterator& 
		Double_linked_list<_Ty>::iterator::operator--(int)
	{
		iterator temp = *this;
		++* this;
		return &iterator{ temp };
	}

	template <typename _Ty>
	typename Double_linked_list<_Ty>::iterator& 
		Double_linked_list<_Ty>::iterator::operator+(const size_t val) noexcept {
		for (size_t i = 0; i < val; ++i)
			++this;
		return *this;
	}

	template <typename _Ty>
	typename Double_linked_list<_Ty>::iterator& 
		Double_linked_list<_Ty>::iterator::operator-(const size_t val) noexcept {
		for (size_t i = 0; i < val; ++i)
			--this;
		return *this;
	}

#endif
	
#if 1
	template <typename _Ty>
	Double_linked_list<_Ty>::Double_linked_list(
		const iterator& beginning, const iterator& ending)
	{
		std::for_each(beginning, ending, [this]()
		{
			
		});
	}

	template <typename _Ty>
	Double_linked_list<_Ty>::Double_linked_list(const Double_linked_list& lst)
	{
		__pointer_t current = lst._head;
		__pointer_t end = nullptr;
		std::for_each(lst.begin(), lst.end(), 
		[&lst, &current, &end, this]() mutable -> auto
		{
			__pointer_t n = new dbl_node<_Ty>;
			n->data = current->data;
			if (!_head) {
				_head = n;
				end = _head;
			}
			else {
				end->next = n;
				end = n;
			}
			current = current->next;
		});
	}// copy constructor 

	template <typename _Ty>
	Double_linked_list<_Ty>::~Double_linked_list()
	{
		while (_head != _tail)
		{
			const __pointer_t temp = _head;
			_head = _head->next;
			delete temp;
		}
	}//end destructor
	template <typename _Ty>
	void Double_linked_list<_Ty>::push_back(_Ty val)
	{
		//TODO
		__pointer_t node = new dbl_node<_Ty>(val);
		node->next = nullptr;
		node->prev = _tail;
		if (is_empty())
			_head = node;
		else
			_tail->next = node;
		_tail = node;
		++_size; // new node = +1 to size
	}
#endif

	// global functions
	namespace static_dlist_dh
	{
		template <class _Ty>
		_NODISCARD auto begin(const Double_linked_list<_Ty>& dll) noexcept {
			return dll.begin();
		}

		template <class _Ty>
		_NODISCARD auto end(const Double_linked_list<_Ty>& dll) noexcept {
			return dll.end();
		}

		template <class _Ty>
		_NODISCARD auto begin(const Double_linked_list<_Ty>*& dll) noexcept {
			return dll->begin();
		}

		template <class _Ty>
		_NODISCARD auto end(const Double_linked_list<_Ty>*& dll) noexcept {
			return dll->end();
		}
	}
}