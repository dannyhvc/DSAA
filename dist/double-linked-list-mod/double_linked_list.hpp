/**@author Daniel Herrera
 * Description:
 */

#pragma once
//#include <functional>
#include "../node-mod/node.hpp"
#include <algorithm>


namespace linears_dh
{
	template <typename _Ty>
	class
		Double_linked_list : protected dbl_node<_Ty>
	{
		using __pointer_t = dbl_node<_Ty>*;
		using __const_pointer_t = const dbl_node<_Ty>*;

	public:
		using pointer_type = std::shared_ptr<Double_linked_list<_Ty>>;
		using const_pointer_type = const std::shared_ptr<Double_linked_list<_Ty>>;

		// ============== ITERATOR SPECIFIERS ============== //
#if true
		class iterator
		{
			using __pointer_t = dbl_node<_Ty>*;
			using __const_pointer_t = dbl_node<_Ty>* const;
			__pointer_t _pointer_node;
		public:
			explicit iterator() = default;

			explicit iterator(iterator const& it)
				: _pointer_node(it._pointer_node)
			{
			}

			explicit iterator(iterator* const& it)
				: _pointer_node(it->_pointer_node)
			{
			}

			explicit iterator(__const_pointer_t& cpn)
				: _pointer_node(cpn)
			{
			}

			~iterator() = default;

			// operator overloading
			iterator& operator=(__const_pointer_t& pnode)
			{
				return &iterator(pnode);
			}

			//prefix
			iterator& operator++()
			{
				if (this->_pointer_node)
					_pointer_node = _pointer_node->next;
				return *this;
			}

			//postfix
			iterator& operator++(int)
			{
				iterator temp = *this;
				++*this;
				return &iterator{temp};
			}

			//prefix
			iterator& operator--()
			{
				if (this->_pointer_node)
					_pointer_node = _pointer_node->prev;
				return *this;
			}

			//postfix
			iterator& operator--(int)
			{
				iterator temp = *this;
				++*this;
				return &iterator{temp};
			}

			iterator& operator+(size_t const val) noexcept
			{
				for (size_t i = 0; i < val; ++i)++this;
				return *this;
			}

			iterator& operator-(size_t const val) noexcept
			{
				for (size_t i = 0; i < val; ++i)--this;
				return *this;
			}

			_Ty& operator *() const { return this->_pointer_node->data; } // dereferencing overload

			constexpr bool operator ==(iterator const& rhs) noexcept
			{
				return _pointer_node == rhs._pointer_node;
			}

			constexpr bool operator !=(iterator const& rhs) noexcept
			{
				return _pointer_node != rhs._pointer_node;
			}
		};
		friend class iterator;

		//iterating class super method
		// -> iterator to the top of the list
		_NODISCARD constexpr iterator begin() const noexcept { return iterator(this->head_); }
		// leads to the end of the list
		_NODISCARD constexpr iterator end() const noexcept { return iterator(this->tail_->next); }
#endif

		// ============== DOUBLE LINKED LIST CLASS SPECIFIERS ============== //
		Double_linked_list() :
			head_(nullptr), tail_(nullptr), size_(0)
		{}

		/**
		 * @name Double_linked_list
		 * @param1 beginning <dbl_ll::iterator>
		 * @param2 ending <dbl_ll::iterator>
		 * ==============Description==============
		 * Constructor that takes beginning and ending iterators
		 * used to copy another linked list on initialization.
		 */
		explicit Double_linked_list(iterator const& beginning, iterator const& ending)
		{
			for (auto itr = beginning; itr != ending; ++itr)
				this->push_back(*itr);
		}

		/**
		 * @name Double_linked_list
		 * @params Double_linked_list constant qualified template typed
		 * ==============Description==============
		 * Deep copy constructor
		 */
		explicit Double_linked_list(Double_linked_list const& lst)
		{
			for (auto itr = lst.begin(); itr != lst.end(); ++itr)
				this->push_back(*itr);
		} //end cpy_init

		/**
		 * @name Double_linked_list
		 * @params Double_linked_list constant qualified template typed
		 * ==============Description==============
		 * Deep copy constructor for heap deep copy
		 */l
		explicit Double_linked_list(Double_linked_list* const& lst)
		{
			for (auto itr = lst->begin(); itr != lst->end(); ++itr)
				this->push_back(*itr);
		} //end cpy_init

		/**
		 * @name ~Double_linked_list
		 * ==============Description==============
		 * Destructor function that loop through every node in
		 * the linked list and reduces the size numerically as well as
		 * unlinking the node and deleting them using the dbl_node destructor.
		 */
		~Double_linked_list()
		{
			while (!is_empty())
			{
				auto* const temp = head_;
				head_ = head_->next;
				delete temp;
				--this->size_;
			}
		} //end destructor

		// stretcher methods
		_NODISCARD constexpr size_t size() const { return size_; }
		_NODISCARD constexpr bool is_empty() const { return size_ == 0; }

		/**
		 * @name push_back
		 * @param val constant qualified template typed
		 * @returns void
		 * ==============Description==============
		 * Object method that links a new node on to the back (i.e. tail)
		 * of the double linked list.
		 */
		void push_back(_Ty const& val)
		{
			//TODO
			auto* node = new dbl_node<_Ty>(val, nullptr, tail_);
			if (is_empty())
				head_ = node;
			else
				tail_->next = node;
			tail_ = node;
			++size_;
		}

		/**
		 * @name pop_back
		 * @returns _Ty
		 * ==============Description==============
		 * Object method unlinks and deletes the last node on
		 * the chain and returns the data value of the unlinked node.
		 */
		_Ty pop_back()
		{
			if (is_empty())
				return nullptr;
			auto* const temp = tail_;
			const _Ty val = temp->data;
			this->tail_ = tail_->prev;
			delete temp;
			--size_;
			return val;
		}

		/**
		 * @name: push_front
		 * @param val constant qualified template typed
		 * @returns void
		 * ==============Description==============
		 * Apends a node to head (front) of the list.
		 */
		void push_front(_Ty const& val)
		{
			auto* const node = new dbl_node<_Ty>(val, head_, nullptr);
			if (is_empty())
			{
				head_ = tail_ = node;
			}
			else
			{
				head_->prev = node;
				head_ = node;
			}
			++size_;
		}

		/**
		 * @name: pop_front
		 * @returns void
		 * ==============Description==============
		 * removes node from the front of the list
		 */
		_Ty pop_front() noexcept
		{
			if (is_empty())
				return nullptr;

			auto* const temp = head_;
			head_ = head_->next;
			head_->prev = nullptr;
			const _Ty val = temp->data;
			delete temp;
			--size_;
			return val;
		}

		void insert()
		{
			//TODO 
		}//end insert

		//void insert(const unsigned pos, const _Ty& rval); //inserts and replaces at position
		//void insert_before();
		//void insert_after();

	private:
		// list node mutatbles
		__pointer_t head_;
		__pointer_t tail_;
		unsigned size_;
	};

	// global functions
	namespace static_dlist_dh
	{
		template <class _Ty>
		_NODISCARD auto begin(const Double_linked_list<_Ty>& dll) noexcept
		{
			return dll.begin();
		}

		template <class _Ty>
		_NODISCARD auto end(const Double_linked_list<_Ty>& dll) noexcept
		{
			return dll.end();
		}

		template <class _Ty>
		_NODISCARD auto begin(const Double_linked_list<_Ty>*& dll) noexcept
		{
			return dll->begin();
		}

		template <class _Ty>
		_NODISCARD auto end(const Double_linked_list<_Ty>*& dll) noexcept
		{
			return dll->end();
		}
	}
}
