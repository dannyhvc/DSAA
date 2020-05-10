#pragma once
//#include <functional>
#include "../node-mod/node.hpp"
#include <algorithm>

/**
 * \brief
 * 
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
			iterator& operator=(__const_pointer_t& pnode) {
				return &iterator(pnode);
			}

			//prefix
			iterator& operator++ () {
				if (this->_pointer_node)
					_pointer_node = _pointer_node->next;
				return *this;
			}

			//postfix
			iterator& operator++ (int) {
				iterator temp = *this;
				++* this;
				return &iterator{ temp };
			}
			
			//prefix
			iterator& operator-- () {
				if (this->_pointer_node)
					_pointer_node = _pointer_node->prev;
				return *this;
			}
			
			//postfix
			iterator& operator-- (int) {
				iterator temp = *this;
				++*this;
				return &iterator{ temp };
			}

			iterator& operator+ (const size_t val) noexcept {
				for (size_t i = 0; i < val; ++i)
					++this;
				return *this;
			}

			iterator& operator- (const size_t val) noexcept {
				for (size_t i = 0; i < val; ++i)
					--this;
				return *this;
			}

			constexpr bool operator == (const iterator& rhs) {
				return reinterpret_cast<const void*>(this) == reinterpret_cast<const void*>(rhs);
			}
			constexpr bool operator != (const iterator& rhs) {
				return reinterpret_cast<const void*>(this) != reinterpret_cast<const void*>(rhs);
			}
		};
		friend class iterator;
		
		//iterating class super method
		// -> iterator to the top of the list
		iterator begin() const { return iterator(this->_head); }
		// leads to the end of the list
		iterator end() const { return iterator(nullptr); }
#endif
		
		// ============== DOUBLE LINKED LIST CLASS SPECIFIERS ============== //
		Double_linked_list() :
			_head(nullptr), _tail(nullptr)
		{
		}

		/**@author Daniel Herrera
		 * name: class
		 * @param1 beginning <dbl_ll::iterator>
		 * @param2 ending <dbl_ll::iterator>
		 * ==============Description==============
		 *		Constructor that takes beginning and ending iterators
		 *		used to copy another linked list on initialization.
		 */
		explicit Double_linked_list(const iterator& beginning, 	const iterator& ending)
		{
			std::for_each(beginning, ending, [this](_Ty val)	{
				this->push_back(val);
			});
		}

		/**@author Daniel Herrera
		 * 
		 */
		explicit Double_linked_list(const Double_linked_list& lst)
		{
			__pointer_t current = lst._head;
			__pointer_t end = nullptr;
			std::for_each(lst.begin(), lst.end(),
				[this](_Ty val) mutable -> auto	{
				this->push_back(val);
			});
		}//end cpy_init

		/**@author Daniel Herrera
		 * name: ~class
		 * ==============Description==============
		 *		Destructor function that loop through every node in
		 *		the linked list and reduces the size numerically as well as
		 *		unlinking the node and deleting them using the dbl_node destructor.
		 */
		~Double_linked_list()
		{
			while (!is_empty())	{
				const __pointer_t temp = _head;
				_head = _head->next;
				delete temp;
				--this->_size;
			}
		}//end destructor

		// stretcher methods
		_NODISCARD constexpr size_t size() const { return _size; }
		_NODISCARD constexpr bool is_empty() const { return _size == 0; }

		/**@author Daniel Herrera
		 * name: push_back
		 * @param val, const qualified template typed
		 * @returns void
		 * ==============Description==============
		 *		Object method that links a new node on to the back (i.e. tail)
		 *		of the double linked list.
		 */
		void push_back(const _Ty& val)
		{
			//TODO
			auto* node = new dbl_node<_Ty>(val);
			node->next = nullptr;
			node->prev = _tail;
			if (is_empty())
				_head = node;
			else
				_tail->next = node;
			_tail = node;
			++_size; // new node = +1 to size
		}

		/**@author Daniel Herrera
		 * name: pop_back
		 * @param: val, const qualified template typed
		 * @returns _Ty
		 * ==============Description==============
		 *		Object method unlinks and deletes the last node on
		 *		the chain and returns the data value of the unlinked node.
		 */
		_Ty pop_back()
		{
			if (is_empty())
				return _Ty();
			auto* temp(_tail);
			_Ty val(temp->data);
			this->_tail = _tail->prev;
			delete temp;
			--_size;
			return val;
		}

		/**@author Daniel Herrera
		 * name: push_front
		 * 
		 */
		void push_front(const _Ty& val)
		{
			auto* node = new dbl_node<_Ty>;
			node->data = val;
			node->next = _head;
			node->prev = nullptr;
			if (is_empty())
				_head = _tail = node;
			else {
				_head->prev = node;
				_head = node;
			}
			++_size;
		}
		
		_Ty pop_front();
		void insert(const unsigned pos, const _Ty& rval); //inserts and replaces at position
		void insert_before();
		void insert_after();
		

	private:
		// list node mutatbles
		__pointer_t _head { nullptr };
		__pointer_t _tail { nullptr };
		unsigned	_size { 0 };
	};
	
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
