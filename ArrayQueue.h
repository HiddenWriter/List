#pragma once
#include <algorithm>
#include <iostream>
#include "Array.h"

template <typename T>
class ArrayQueue
{
private:
	Array<T> mArr;
	int mElem2Remove; // j 
	int mNumOfElem; // n

private:

	void Resize();

public:
	
	ArrayQueue();
	~ArrayQueue() {}
	bool Add(T _x);
	
	T Remove();

	void Print();

	const int GetSize() const noexcept;
};

template <typename T>
ArrayQueue<T>::ArrayQueue()
	: mArr(1), mElem2Remove(0), mNumOfElem(0)
{}

template <typename T>
bool ArrayQueue<T>::Add(T _x)
{
	if (mNumOfElem + 1 > mArr.GetLength()) Resize();

	mArr[(mNumOfElem + mElem2Remove) % mArr.GetLength()] = _x;
	mNumOfElem++;

	return true;
}

template <typename T>
T ArrayQueue<T>::Remove()
{
	T x = mArr[mElem2Remove];
	mElem2Remove = (mElem2Remove + 1) % mArr.GetLength();
	mNumOfElem--;

	if (mArr.GetLength() >= 3 * mNumOfElem) Resize();
	return x;
}

template <typename T>
void ArrayQueue<T>::Resize()
{
	Array<T> b(std::max(2 * mNumOfElem, 1));
	for (int i = 0; i < mNumOfElem; i++)
	{
		b[i] = mArr[(mElem2Remove + i) % mArr.GetLength()];
	}
	mArr = b;
	mElem2Remove = 0;
	
	return;
}

template <typename T>
void ArrayQueue<T>::Print()
{
	for (int i = 0; i < mNumOfElem; i++)
	{
		std::cout << mArr[(mElem2Remove + i) % mArr.GetLength()];
	}
	return;
}

template <typename T>
const int ArrayQueue<T>::GetSize() const noexcept
{
	return this->mNumOfElem;
}