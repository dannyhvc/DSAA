// ReSharper disable CppClangTidyHicppSpecialMemberFunctions
#pragma once
/**
 * \brief takes the class name and 
 * \param cl 
 */
#define POINTER_TYPE(cls) using pointer = cls*;
#define CONST_POINTER_TYPE(cls) using const_pointer = const cls*;

template <class Ty>
class Node {};

/**
 * \brief double sided node
 * \tparam Ty 
 */
template <class Ty>
class dbl_node : public Node<Ty>  // NOLINT(hicpp-special-member-functions)
{
protected:
	POINTER_TYPE(dbl_node<Ty>)
	CONST_POINTER_TYPE(dbl_node<Ty>)
public:
	// init constructor
	dbl_node() = default;
	// ReSharper disable once CppNonExplicitConvertingConstructor
	dbl_node(const Ty val, const pointer nxt = nullptr, const pointer prv = nullptr) :
		data(val), next(nxt), prev(prv) {}

	// copy constructor
	explicit dbl_node(const dbl_node& dn) noexcept :
		data(dn.data), next(dn.next), prev(dn.prev) {}
	explicit dbl_node(const typename dbl_node::pointer& pdn) noexcept :
		data(pdn->data), next(pdn->next), prev(pdn->prev) {}

	~dbl_node() { delete next; delete prev; } // inline destructor

	Ty		data = 0;
	pointer next = nullptr;
	pointer prev = nullptr;
};

template <class Ty>
class sngl_node : public Node<Ty>
{
protected:
	POINTER_TYPE(sngl_node<Ty>)
	CONST_POINTER_TYPE(sngl_node<Ty>)
public:
	sngl_node() = default;
	sngl_node(const Ty val, const pointer nxt = nullptr) :
		data(val), next(nxt) {}
	
	explicit sngl_node(const sngl_node& sn):
		data(sn.data), next(sn.data) {}
	explicit sngl_node(const pointer psn) :
		data(psn->data), next(psn->next) {}
	
	~sngl_node() { delete next; }
	
	Ty		data = 0;
	pointer next = nullptr;
};