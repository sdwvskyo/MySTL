#ifndef MYQUEUE_H_
#define MYQUEUE_H_ 

#include <iostream>
#include <stdexcept>

template <typename T>
struct Node {
	T data;
	Node<T> *next;

	Node(const T &d) 
		: data(d), next(NULL)  
	{  }
};

template <typename T>
class MyQueue {
	public:
		MyQueue();
		~MyQueue();
		MyQueue(const MyQueue &q);
		MyQueue & operator= (const MyQueue &q);
		void clear();
		void enQueue(T data);
		void deQueue();
		T frontElem() const { return front->data; }
		T backElem() const { return rear->data; }
		bool isEmpty() const { return size_ == 0; }
		int size() const { return size_; }
	private:
		Node<T> *front;
		Node<T> *rear;
		int size_;
		void copyQueue(const MyQueue &q);
};

#include "myQueue.hpp"
#endif  /*MYQUEUE_H_*/
