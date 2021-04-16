#pragma once
#include "Array.h"
#include <iostream>
#include <algorithm>
template <typename T>
class ArrayDeque
{
private:

	Array<T> mArr;
	int mElem2Remove;
	int mNumOfElem;

private:

	void Resize();

public:

	ArrayDeque();
	~ArrayDeque() {}

	T Get(int _i);

	T Set(int _i, T _x);
	
	void Add(int _i, T _x);

	T Remove(int _i);

	void Print();

	const int GetSize() const noexcept;
};

template <typename T>
ArrayDeque<T>::ArrayDeque()
	: mArr(1), mElem2Remove(0), mNumOfElem(0)
{}

template <typename T>
T ArrayDeque<T>::Get(int _i)
{
	return mArr[(mElem2Remove + _i) % mArr.GetLength()];
}

template <typename T>
T ArrayDeque<T>::Set(int _i, T _x)
{
	T y = mArr[(mElem2Remove + _i) % mArr.GetLength()];
	mArr[(mElem2Remove + _i) % mArr.GetLength()] = _x;
	return y;
}

template <typename T>
void ArrayDeque<T>::Add(int _i, T _x)
{
	if (mNumOfElem + 1 > mArr.GetLength()) Resize();
	if (_i < mNumOfElem / 2)
	{
		mElem2Remove = (mElem2Remove == 0) ? mArr.GetLength() - 1 : mElem2Remove - 1;
		for (int k = 0; k < _i; k++)
		{
			mArr[(mElem2Remove + k) % mArr.GetLength()] = mArr[(mElem2Remove + k + 1) % mArr.GetLength()];
		}
	}
	else
	{
		for (int k = mNumOfElem; k > _i; k--)
		{
			mArr[(mElem2Remove + k) % mArr.GetLength()] = mArr[(mElem2Remove + k - 1) % mArr.GetLength()];
		}
	}
	mArr[(_i + mElem2Remove) % mArr.GetLength()] = _x;
	mNumOfElem++;
	return;
}

template <typename T>
T ArrayDeque<T>::Remove(int _i)
{
	T y = mArr[(mElem2Remove + _i) % mArr.GetLength()];

	if (_i < mNumOfElem / 2)
	{
		for (int k = _i; k > 0; k--)
		{
			mArr[(mElem2Remove + k) % mArr.GetLength()] = mArr[(mElem2Remove + k - 1) % mArr.GetLength()];
		}
		mElem2Remove = (mElem2Remove + 1) % mArr.GetLength();
	}
	else
	{
		for (int k = _i; k < mNumOfElem - 1; k++)
		{
			mArr[(mElem2Remove + k) % mArr.GetLength()] = mArr[(mElem2Remove + k + 1) % mArr.GetLength()];
		}
	}
	mNumOfElem--;
	if (mNumOfElem * 3 < mArr.GetLength()) Resize();
	return y;
}

template <typename T>
void ArrayDeque<T>::Print()
{
	for (int i = 0; i < mNumOfElem; i++)
	{
		std::cout << mArr[(mElem2Remove + i) % mArr.GetLength()];
	}
	return;
}

template <typename T>
void ArrayDeque<T>::Resize()
{
	Array<T> b(std::max(2 * mNumOfElem, 1));
	for (int k = 0; k < mNumOfElem; k++)
	{
		b[k] = mArr[(mNumOfElem + k) % mArr.GetLength()];
	}
	mArr = b;
	mNumOfElem = 0;

	return;
}

template <typename T>
const int ArrayDeque<T>::GetSize() const noexcept
{
	return this->mNumOfElem;
}