#pragma once
#include <functional>
#include "../node-mod/node.hpp"

/**
 * \brief 
 * \tparam Ty 
 */
template <class Ty>
class Double_linked_list : private dbl_node<Ty>
{
protected:
	POINTER_TYPE(dbl_node<Ty>)
	CONST_POINTER_TYPE(dbl_node<Ty>)
public:
	Double_linked_list()
		: head_(nullptr), tail_(nullptr) { }
	/**
	 * \brief 
	 * \param nod
	 * \param h 
	 * \param func 
	 */
	Double_linked_list(
		const_pointer& nod,std::function<void (const_pointer val)> func);
	Double_linked_list(const_pointer& h, const_pointer& t, 
		std::function<void(const_pointer val)> func1,
		std::function<void(const_pointer val)> func2);

	~Double_linked_list();

	
	/**
	 * \brief 
	 */
	class iterator
	{
		friend class Double_linked_list;
	private:
		pointer nodePtr_;
		// The constructor is private, so only our friends
		// can create instances of iterators.
		iterator(const_pointer newPtr) : nodePtr_(newPtr) {}
	public:
		iterator() : nodePtr_(nullptr) {}

		// Overload for the comparison operator !=
		bool operator!=(const iterator& itr) const { return nodePtr_ != itr.nodePtr_;	}

		// Overload for the dereference operator *
		Ty& operator*() const { return nodePtr_->next_->data_; }

		// Overload for the postincrement operator ++
		iterator operator++(int)
		{
			iterator temp = *this;
			nodePtr_ = nodePtr_->next_;
			return temp;
		}

		iterator operator++()
		{
			return nodePtr_->next_;
		}
	}; // End of inner class iterator

public:
	iterator begin() const { return iterator(this->head_); }
	iterator end() const { return iterator(this->tail_); }
	
private:
	pointer  head_ = nullptr;
	pointer  tail_ = nullptr;
	unsigned size_ = 0;
};