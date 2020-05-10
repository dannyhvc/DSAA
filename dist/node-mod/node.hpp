// ReSharper disable CppClangTidyHicppSpecialMemberFunctions
#pragma once
/**
 * \brief takes the class name and
 * \param cl
 */
#include <memory>
namespace linears_dh
{
	//node base class `has no implementation`
	template <typename Ty>
	class Node	{
	public:
		using pointer_type = std::shared_ptr<Node<Ty>>;
		using const_pointer_type = std::shared_ptr<Node<Ty>> const;;
	};

	//brief double sided node
	template <typename Ty>	class
	dbl_node : public Node<Ty>  // NOLINT(hicpp-special-member-functions)
	{
	private:
		using __pointer_t = dbl_node<Ty>*;
		using __const_pointer_t = const dbl_node<Ty>*;
		
	public:
		using pointer_type = std::shared_ptr<dbl_node<Ty>>;
		using const_pointer_type = std::shared_ptr<dbl_node<Ty>> const;
		// init constructor
		dbl_node() = default;
		// ReSharper disable once CppNonExplicitConvertingConstructor
		dbl_node(Ty const& val, const __pointer_t& n = nullptr, const __pointer_t& p = nullptr) :
			data(val), next(n), prev(p)
			{
			}
		// copy constructor
		explicit dbl_node(dbl_node const& dn) noexcept :
			data(dn.data), next(dn.next), prev(dn.prev)
			{
			}
		explicit dbl_node(__const_pointer_t& pdn) noexcept :
			data(pdn->data), next(pdn->next), prev(pdn->prev)
			{
			}
		~dbl_node() = default; // inline destructor

				 Ty data;
		__pointer_t next;
		__pointer_t prev;
	};

	template <typename Ty>	class
	sngl_node : public Node<Ty>
	{
	protected:
		using pointer_type = std::shared_ptr<sngl_node <Ty>>;
		using const_pointer_type = std::shared_ptr<sngl_node<Ty>> const;
		
	public:
		using __pointer_t = sngl_node<Ty>*;
		using __const_pointer_t = const sngl_node<Ty>*;
		
		sngl_node() = default;
		explicit sngl_node(const Ty& val, __const_pointer_t& nxt = nullptr) :
			data(val), next(nxt)
			{
			}
		explicit sngl_node(const sngl_node& sn) :
			data(sn.data), next(sn.data)
			{
			}
		explicit sngl_node(__const_pointer_t& psn) :
			data(psn->data), next(psn->next)
			{
			}
		~sngl_node() = default;

				 Ty	data;
		__pointer_t next;
	};
}
