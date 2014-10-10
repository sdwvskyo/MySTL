#ifndef VECTOR_HPP_
#define VECTOR_HPP_ 

#include <memory>
#include <algorithm>
#include <limits>
#include <stddef.h>

template <typename T, typename Alloc>
class Vector;

//运算符的函数声明
template <typename T, typename Alloc>
bool operator==(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);
template <typename T, typename Alloc>
bool operator!=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);
template <typename T, typename Alloc>
bool operator< (const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);
template <typename T, typename Alloc>
bool operator<=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);
template <typename T, typename Alloc>
bool operator> (const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);
template <typename T, typename Alloc>
bool operator>=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);

template <typename T, typename Alloc = std::allocator<T> >
class Vector
{
	friend bool operator==<T, Alloc> (const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);
	friend bool operator!=<T, Alloc> (const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);
	friend bool operator< <T, Alloc> (const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);
	friend bool operator<=<T, Alloc> (const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);
	friend bool operator> <T, Alloc> (const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);
	friend bool operator>=<T, Alloc> (const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);

	class reverse_iterator;
	class const_reverse_iterator;
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
		explicit reverse_iterator(iterator it = NULL) : current_(it) {  }

		iterator base() { return current_; }

		reverse_iterator &operator++(){ 
			--current_; 
			return *this; 
		}
		reverse_iterator &operator++(int) {
			reverse_iterator temp(*this);
			--current_;
			return temp;
		}

		reverse_iterator &operator--() {
			++current_;
			return *this;
		}
		reverse_iterator &operator--(int) {
			reverse_iterator temp(*this);
			++current_;
			return temp;
		}

		reference operator*() { return *(current_ - 1); }
		const_reference operator*() const { return *(current_ - 1); }

		pointer operator->() { return current_ - 1; }
		const_pointer operator->() const { return current_ - 1; }

		friend bool operator==(reverse_iterator lhs, reverse_iterator rhs)
		{ return lhs.current_ == rhs.current_; }
		friend bool operator!=(reverse_iterator lhs, reverse_iterator rhs)
		{ return lhs.current_ != rhs.current_; }
		friend bool operator-(reverse_iterator lhs, reverse_iterator rhs)
		{ return lhs.current_ - rhs.current_; }
	private:
		iterator current_;
	};

	class const_reverse_iterator
	{
	public:
		explicit const_reverse_iterator(const_iterator it = NULL) 
			: current_(it) 
		{  }
		const_reverse_iterator(reverse_iterator it) : current_(it) {  }
		const_iterator base() { return current_; }

		const_reverse_iterator &operator++() {
			--current_;
			return *this;
		}
		const_reverse_iterator &operator++(int) {
			const_reverse_iterator temp(*this);
			--current_;
			return temp;
		}

		const_reverse_iterator &operator--() {
			++current_;
			return *this;
		}
		const_reverse_iterator &operator--(int) {
			const_reverse_iterator temp(*this);
			++current_;
			return temp;
		}

		const_reference operator*() const { return *(current_ - 1); }
		const_pointer operator->() const { return current_ -1; }

		friend bool operator==(const_reverse_iterator lhs, const_reverse_iterator rhs) 
		{ return lhs.current_ == rhs.current_; }
		friend bool operator!=(const_reverse_iterator lhs, const_reverse_iterator rhs) 
		{ return lhs.current_ != rhs.current_; }
		friend bool operator-(const_reverse_iterator lhs, const_reverse_iterator rhs) 
		{ return lhs.current_ -  rhs.current_; }

	private:
		const_iterator current_;
	};

public:
	Vector() { create(); }
	explicit Vector(size_type n, const value_type &val = value_type())
	{ create(n, val); }

	template <typename In>
	Vector(In i, In j) { create(i, j); }	//用迭代器初始化容器

	Vector(const Vector &v) { create(v.begin(), v.end()); }
	Vector &operator=(const Vector &v);
	~Vector() { uncreate(); }

	template <typename In>
	void assign(In i, In j) {
		uncreate();
		create(i, j);
	}
	void assign(size_type n, const T &val) {
		uncreate();
		create(n, val);
	}

	reference operator[](size_type n) { return *(data_ + n); }
	const_reference operator[](size_type n) const {return *(data_ + n); }

	reference at(size_type n) { return *(data_ + n); }
	const_reference at(size_type n) const { return *(data_ + n); }

	iterator begin() { return data_; }
	iterator rbegin() { return reverse_iterator(avail_); }
	iterator end() { return avail_; }
	iterator rend() { return reverse_iterator(data_); }
	const_iterator begin() const { return data_; }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(avail_); }
	const_iterator end() const { return avail_; }
	const_reverse_iterator rend() const { return const_reverse_iterator(data_); }

	reference front() { return *begin(); }
	reference back() { return *rbegin(); }
	const_reference front() const { return *begin(); }
	const_reference back() const { return *rbegin(); }

	void push_back(const T &t) {
		if (avail_ == limit_)	//if full 
			grow();
		unCheckedAppend(t);
	}

	void pop_back() { alloc_.destroy(--avail_); }

	void swap(Vector &other) {
		std::swap(data_, other.data_);
		std::swap(avail_, other.avail_);
		std::swap(limit_, other.limit_);
	}
	
	iterator insert(iterator position, const value_type &val);
	void insert(iterator position, size_type n, const value_type &val);
	template <typename In>
	void insert(iterator position, In first, In last);

	iterator erase(iterator position);
	iterator erase(iterator first, iterator last);

	void resize(size_type n, value_type val = value_type());
	void reserve(size_type n);

	bool empty() const { return data_ == avail_; }
	size_type size() const { return avail_ - data_; }
	size_type capacity() const { return limit_ - data_; }
	size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(T); }
	allocator_type get_allocator() const { return alloc_; }

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

//public function

template <typename T, typename Alloc>
Vector<T, Alloc> &Vector<T, Alloc>::operator=(const Vector &v)
{
	if (this != &v) {
		uncreate();
		create(v.begin, v.end());
	}
	return this;
}


template <typename T, typename Alloc>
typename Vector<T, Alloc>::iterator Vector<T, Alloc>::insert(iterator position, const value_type &val)
{
	difference_type pos = position - data_;
	insert(position, 1, val);
	return  data_ + pos;
	
}

template <typename T, typename Alloc>
void Vector<T, Alloc>::insert(iterator position, size_type n, const value_type &val)
{
	difference_type pos = position - data_;	//保存position长度，防止重新分配后position失效
	while (static_cast<size_type>(limit_ - avail_) < n) //使用while，防止一次grow不够
		grow();
	position = data_ + pos;

	size_type left = avail_ - position;
	if (n < left)	//小于则先移动后半部分，再反向移动前半部分，直接移动会覆盖后面的元素
	{
		size_type len_copy = left - n;
		std::uninitialized_copy(position + len_copy, avail_, avail_);
		std::copy_backward(position, position + len_copy, avail_);
		std::fill_n(position, n, val);
	}
	else if (n > left)	//大于则直接移动元素
	{
		std::uninitialized_copy(position, avail_, position + n);

		//新分配内存的填充方式不同，所以要分为两次进行
		std::fill_n(position, avail_ - position, val);
		std::uninitialized_fill(avail_, position + n, val);
	}
	else	//刚好相等则移动和填充都只需要一部完成
	{
		std::uninitialized_copy(position, avail_, avail_);
		std::fill_n(position, n, val);
	}
	avail_ += n;
}

template <typename T, typename Alloc>
template <typename In>
void Vector<T, Alloc>::insert(iterator position, In first, In last)
{
	difference_type pos = position - data_; //防止position失效
	size_type n = last - first; 	//需要插入的元素个数
	while (static_cast<size_type>(limit_ - avail_) < n)
		grow();
	position = data_ + pos;

	size_type left = avail_ - position;
	if (n < left)
	{
		size_type len_copy = left - n;
		std::uninitialized_copy(position + len_copy, avail_, avail_);
		std::copy_backward(position, position + len_copy, avail_);

		std::copy(first, last, position);
	}
	else if (n < left)
	{
		std::uninitialized_copy(position, avail_, position + n);

		std::copy(first, first + left, position);
		std::uninitialized_copy(first + left, last, avail_);
	}
	else
	{
		std::uninitialized_copy(position, avail_, avail_);

		std::copy(first, last, position);
	}

	avail_ += n;
}

template <typename T, typename Alloc>
typename Vector<T, Alloc>::iterator Vector<T, Alloc>::erase(iterator position)
{
	std::copy(position + 1, avail_, position);
	alloc_.destroy(--avail_);
	return position;
}

template <typename T, typename Alloc>
typename Vector<T, Alloc>::iterator Vector<T, Alloc>::erase(iterator first, iterator last)
{
	difference_type n = last - first;
	std::copy(last, avail_, first);

	while (n--)
		alloc_.destroy(--avail_);

	return first;
}

template <typename T, typename Alloc>
void Vector<T, Alloc>::resize(size_type n, value_type val)
{
	size_type current_size = size();
	if (n < current_size)	//减少数量
	{
		size_type diff = current_size - n;
		while (diff--) {
			alloc_.destroy(--avail_);
		}
	} 
	else if (n > current_size) 	//增加数量
	{
		size_type diff = n - current_size;
		size_type left = static_cast<size_type>(limit_ - avail_);

		//判断是否需要重新分配内存
		if (left < diff) 
			growToN(n);

		//填充后面的元素
		while (size() < n)
			unCheckedAppend(val);
	}
}

template <typename T, typename Alloc>
void Vector<T, Alloc>::reserve(size_type n)
{
	size_type current_capacity = capacity();
	if (n > current_capacity) 
		growToN(n);	
}

//private function implatation
template <typename T, typename Alloc>
void Vector<T, Alloc>::create()
{
	data_ = avail_ = limit_ = NULL;
}

template <typename T, typename Alloc>
void Vector<T, Alloc>::create(size_type n, const value_type &val)
{
	//分配内存
	data_ = alloc_.allocate(n);
	//执行构造函数 拷贝构造函数
	std::uninitialized_fill(data_, data_ + n, val);
	avail_ = limit_ = data_ + n;
}

template <typename T, typename Alloc>
template <typename In>
void Vector<T, Alloc>::create(In i, In j)
{
	data_ = alloc_.allocate(j - i);
	avail_ = limit_ = std::uninitialized_copy(i, j, data_);
}

template <typename T, typename Alloc>
void Vector<T, Alloc>::uncreate()
{
	//先析构有数据的部分
	if (data_) {
		iterator it(avail_);
		while (it != data_)
			alloc_.destroy(--it);
	}
	//再释放内存
	alloc_.deallocate(data_, limit_ - data_);
	data_ = avail_ = limit_ = NULL;
}

template <typename T, typename Alloc>
void Vector<T, Alloc>::grow()
{
	size_type new_size = std::max(2*(limit_ - data_), difference_type(1));

	growToN(new_size);
}

template <typename T, typename Alloc>
void Vector<T, Alloc>::unCheckedAppend(const value_type &val)
{
	//插入新元素
	alloc_.construct(avail_++, val);
}

template <typename T, typename Alloc>
void Vector<T, Alloc>::growToN(size_type n)
{
	//先申请内存并构造
	iterator new_data = alloc_.allocate(n);
	iterator new_avail = std::uninitialized_copy(data_, avail_, new_data);
	//析构之前的内存
	uncreate();
	//重置指针
	data_ = new_data;
	avail_ = new_avail;
	limit_ = data_ + n;
}


template <typename T, typename Alloc>
bool operator==(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs)
{
	return lhs.size() == rhs.size() && 
		std::equal(lhs.begin(), lhs.end(), rhs.begin());
}


template <typename T, typename Alloc>
bool operator!=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs)
{
	return !(lhs == rhs);
}

template <typename T, typename Alloc>
bool operator<(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs)
{
	typedef typename Vector<T, Alloc>::size_type size_type;
	size_type size1 = lhs.size();
	size_type size2 = rhs.size();
	size_type min_size = (size1 < size2) ? size1 : size2;
	size_type ix = 0;
	for(; ix != min_size; ++ix)
	{
		if(lhs[ix] < rhs[ix])
			return true;
		else if(lhs[ix] > rhs[ix])
			return false;
	}
	if(ix != size2) //rhs较长
		return true;
	return false;
}

template <typename T, typename Alloc>
bool operator<=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs)
{
	return !(rhs < lhs);
}

template <typename T, typename Alloc>
bool operator>(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs)
{
	return rhs < lhs;
}

template <typename T, typename Alloc>
bool operator>=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs)
{
	return !(lhs < rhs);
}

#endif  /*VECTOR_HPP_*/
