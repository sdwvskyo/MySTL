#ifndef MYVECTOR_HPP_
#define MYVECTOR_HPP_ 

template <typename ElemType>
MyVector<ElemType>::MyVector()
{
	arr = new ElemType[10];
	numAllocated = 10;
	numUsed = 0;
}

template <typename ElemType>
MyVector<ElemType>::~MyVector()
{
	delete [] arr;
}

template <typename ElemType>
int MyVector<ElemType>::size()
{
	return numUsed;
}

template <typename ElemType>
ElemType MyVector<ElemType>::getAt(int index)
{
	if (index < 0 || index >= size())
		ERR_EXIT("out of range");
	return arr[index];
}

template <typename ElemType>
void MyVector<ElemType>::add(ElemType s)
{
	if (numUsed == numAllocated) 
		doubleSpace();	
	arr[numUsed++] = s;
}

template <typename ElemType>
void MyVector<ElemType>::insertAt(int index, ElemType s)
{
	if (index < 0 || index >= size())
		ERR_EXIT("out of range");
	if (numUsed == numAllocated) 
		doubleSpace();	
	for (int i = size() - 1; i >= index; i--) 
		arr[i+1] = arr[i];
	arr[index] = s;
	numUsed++;
}


template <typename ElemType>
ElemType MyVector<ElemType>::removeAt(int index)
{
	return arr[numUsed--];
}

template <typename ElemType>
void MyVector<ElemType>::doubleSpace()
{
	ElemType *bigger = new ElemType[numAllocated*2];
	for (int i = 0; i < numUsed; i++) {
		bigger[i] = arr[i];
	}
	delete [] arr;
	arr = bigger;
	numAllocated *= 2;
}


#endif  /*MYVECTOR_HPP_*/
