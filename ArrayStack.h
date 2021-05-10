#pragma once
#include <iostream>
#include "Array.h"

template <typename T>
class DualArrayDeque;

template <typename T>
class ArrayStack
{
public:
    ArrayStack();
    ArrayStack(int _i);
    ~ArrayStack();

    T& operator[](int _idx);
    T Get(int _i);
    T Set(int _i, T _x);
    void Add(int _i, T _x);
    T Remove(int _i);
    int GetSize() const noexcept;
    void Print() noexcept;

protected:
    friend class DualArrayDeque<T>;
    void Resize();
    Array<T> mArr;
    int mSize;
};

template <typename T>
ArrayStack<T>::ArrayStack()
    : mArr(1), mSize(0)
{}
template <typename T>
ArrayStack<T>::ArrayStack(int _i)
    : mArr(_i), mSize(0)
{}
template <typename T>
ArrayStack<T>::~ArrayStack()
{}
template <typename T>
T ArrayStack<T>::Get(int _i)
{
    return mArr[_i];
}

template <typename T>
T ArrayStack<T>::Set(int _i, T _x)
{
    T y = mArr[_i];
    mArr[_i] = _x;
    return y;
}

template <typename T>
void ArrayStack<T>::Add(int _i, T _x)
{
    if (mSize + 1 > mArr.GetLength()) Resize();

    for (int j = mSize; j > _i; j--)
    {
        mArr[j] = mArr[j - 1];
    }
    mArr[_i] = _x;
    mSize++;
}

template <typename T>
T ArrayStack<T>::Remove(int _i)
{
    T x = mArr[_i];
    for (int j = _i; j < mSize - 1; j++)
    {
        mArr[j] = mArr[j + 1];
    }
    mSize--;

    if (mArr.GetLength() >= 3 * mSize)
    {
        Resize();
    }
    return x;
}

template <typename T>
void ArrayStack<T>::Resize()
{
    Array<T> resizedArray(std::max(2 * mSize, 1));
    for (int i = 0; i < mSize; i++)
    {
        resizedArray[i] = mArr[i];
    }
    mArr = resizedArray;
    return;
}

template <typename T>
int ArrayStack<T>::GetSize() const noexcept
{
    return this->mSize;
}

template <typename T>
void ArrayStack<T>::Print() noexcept
{
    for (int i = 0; i < mSize; i++)
    {
        std::cout << "*\n";
        std::cout << mArr[i];
    }
    return;
}

template <typename T>
T& ArrayStack<T>::operator[](int _idx)
{
    return mArr[_idx];
}