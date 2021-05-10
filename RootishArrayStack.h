#pragma once
#include <cmath>

#include "ArrayStack.h"

template <typename T>
class RootishArrayStack
{
private:
    ArrayStack<T*> blocks;

    int mSize;

    void Grow();

    void Shrink();

    int i2b(int _i);

public:

    RootishArrayStack();
    
    ~RootishArrayStack();

    T Get(int _i);

    T Set(int _i, T _x);

    void Add(int _i, T _x);

    T Remove(int _i);

    const int GetSize() const noexcept;

    void Print() noexcept;

};

template <typename T>
RootishArrayStack<T>::RootishArrayStack()
    : mSize(0)
{}

template <typename T>
RootishArrayStack<T>::~RootishArrayStack()
{
    int last(i2b(mSize));
    for (int i = 0; i < last; i++)
    {
        delete[] blocks.Get(i);
    }
}

template <typename T>
int RootishArrayStack<T>::i2b(int _i)
{
    double db = (-3.0f + std::sqrt(9 + 8 * _i)) / 2.0f;
    int b = (int)std::ceil(db);
    return b;
}

template <typename T>
T RootishArrayStack<T>::Get(int _i)
{
    int b (i2b(_i));
    int j (_i - (b + 1) * b / 2);
    return blocks.Get(b)[j];
}

template <typename T>
T RootishArrayStack<T>::Set(int _i, T _x)
{
    int b (i2b(_i));
    int j (_i - (b + 1) * b / 2);

    T y = blocks.Get(b)[j];
    blocks.Get(b)[j] = _x;

    return y;
}

template <typename T>
void RootishArrayStack<T>::Add(int _i, T _x)
{
    int r (blocks.GetSize());
    if ( r * (r + 1) / 2 < mSize + 1) Grow();
    mSize++;
    for (int j = mSize - 1; j > _i; j--)
    {
        Set(j, Get(j - 1));
    }
    Set(_i, _x);

    return;
}

template <typename T>
void RootishArrayStack<T>::Grow()
{
    blocks.Add(blocks.GetSize(), new T[blocks.GetSize() + 1]);
}

template <typename T>
void RootishArrayStack<T>::Shrink()
{
    int r (blocks.GetSize());
    while (r > 0 && (r - 2) * (r - 1) / 2 >= mSize)
    {
        delete[] blocks.Remove(blocks.GetSize() - 1);
        r--;
    }
}

template <typename T>
T RootishArrayStack<T>::Remove(int _i)
{
    int b (i2b(_i));
    T x = Get(_i);

    for (int j = _i; j < mSize - 1; j++)
    {
        Set(j, Get(j + 1));
    }
    mSize--;
    int r (blocks.GetSize());
    if ( (r - 2) * (r - 1) / 2 >= mSize)
    {
        Shrink();
    }
    return x;
}

template <typename T>
const int RootishArrayStack<T>::GetSize() const noexcept
{
    return mSize;
}

template <typename T>
void RootishArrayStack<T>::Print() noexcept
{
    for( int i = 0; i < mSize; i++)
    {
        std::cout << Get(i);
    }
    return;
}