#ifndef MYQUEUE_HPP_
#define MYQUEUE_HPP_ 

using namespace std;

template <typename T>
MyQueue<T>::MyQueue() 
	: front(NULL), rear(NULL), size_(0)
{  

}

template <typename T>
MyQueue<T>::~MyQueue()
{
	clear();
}

template <typename T>
void MyQueue<T>::clear()
{
	while (size_ > 0) {
		deQueue();
	}
}

template <typename T>
MyQueue<T>::MyQueue(const MyQueue<T> &q)
{
	clear();
	copyQueue(q);
}

template <typename T>
MyQueue<T> & MyQueue<T>::operator = (const MyQueue<T> &q)
{
	if (*this != q) {
		clear();
		copyQueue(q);
	}
	return *this;
}

template <typename T>
void MyQueue<T>::enQueue(T data)
{
	Node<T> *pNew = new Node<T>(data);
	if (size_ == 0) {
		front = pNew;
		rear = pNew;
	} else {
		rear->next = pNew;
		rear = pNew;
	}
	++size_;
}


template <typename T>
void MyQueue<T>::deQueue()
{
	if (size_ > 0) {
		Node<T> *p = front;
		front = front->next;
		if (front == NULL)
			rear = NULL;
		delete p;
		size_--;
	}
}

template <typename T>
void MyQueue<T>::copyQueue(const MyQueue &q)
{	
	Node<T> *p = q.front;
	while(p) {
		enQueue(p->data);
		p = p->next;
	}
}
#endif  /*MYQUEUE_HPP_*/
