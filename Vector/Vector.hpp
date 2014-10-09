#ifndef VECTOR_HPP_
#define VECTOR_HPP_ 

#include <memory>
#include <algorithm>
#include <limits>
#include <stddef.h>


template <typename T, typename Alloc = std::allocator<T> >
class Vector
{
	friend bool operator==<T, Alloc> (const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);
	friend bool operator!=<T, Alloc> (const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);
	friend bool operator< <T, Alloc> (const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);
	friend bool operator<=<T, Alloc> (const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);
	friend bool operator> <T, Alloc> (const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);
	friend bool operator>=<T, Alloc> (const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);

public:
	typedef T value_type;
	typedef T * iterator;
	typedef const T * const_iterator;
	typedef reverse_iterator reverse_iterator;
	typedef const_reverse_iterator const_reverse_iterator;
	typedef T & reference;
	typedef const T & const_reference;
	typedef T * pointer;
	typedef const T * const_pointer;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef Alloc allocator_type;
private:
	class reverse_iterator
	{
	public:

	private:
		iterator current_;
	};

	class const_reverse_iterator
	{
	public:

	private:
		const_iterator current_;
	};

	
public:

private:
	iterator data_;		//首元素指针
	iterator avail_;	//尾元素的下一个位置
	iterator limit_;	//尾内存的下一个位置

	std::allocator<T> alloc_;	//内存分配器

	//开辟内存和初始化
	void create();
	void create(size_type, const value_type &);
	template <typename In>
	void create(In, In);

	void uncreate();

	//用于push_back函数
	void grow();
	void unCheckedAppend(const value_type &);

	void growToN(size_type n);
};



#endif  /*VECTOR_HPP_*/
