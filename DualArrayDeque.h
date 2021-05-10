#pragma once

#include <algorithm>
#include "Array.h"
#include "ArrayStack.h"

template <typename T>
class DualArrayDeque 
{
private:
    ArrayStack<T> front;
    ArrayStack<T> back;

public:
    DualArrayDeque();
    ~DualArrayDeque();

    T Get(int _i);

    T Set(int _i, T _x);

    const int GetSize() const noexcept;

    void Add(int _i, T _x);

    T Remove(int _i);

    void Print() noexcept;
private:

    void Balance();

};

template <typename T>
DualArrayDeque<T>::DualArrayDeque()
    : front(1), back(1)
{}

template <typename T>
DualArrayDeque<T>::~DualArrayDeque() 
{}

template <typename T>
void DualArrayDeque<T>::Balance()
{
    if 
    (
        3 * front.GetSize() < back.GetSize() 
        ||
        3 * back.GetSize() < front.GetSize()
    )
    {
        int n (GetSize());
        int nf ( n / 2);
        Array<T> af(std::max(2*nf, 1));
        for (int i = 0; i < nf; i++)
        {
            af[nf - i - 1] = Get(i);
        }

        int nb (n - nf);
        Array<T> ab(std::max(2*nb, 1));
        for(int j = 0; j < nb; j++)
        {
            ab[j] = Get(nf + j);
        }
        front.mArr = af;
        front.mSize = nf;
        back.mArr = ab;
        back.mSize = nb;
    }
        return;
}

template <typename T>
const int DualArrayDeque<T>::GetSize() const noexcept
{
    return front.GetSize() + back.GetSize();
}

template <typename T>
T DualArrayDeque<T>::Get(int _i)
{
    if (_i < front.GetSize())
    {
        return front.Get(front.GetSize() - _i - 1);
    }
    else 
    {
        return back.Get(_i - front.GetSize());
    }
}

template <typename T>
T DualArrayDeque<T>::Set(int _i, T _x)
{
    if(_i < front.GetSize())
    {
        return front.Set(front.GetSize() - _i - 1, _x);
    }
    else 
    {
        return back.Set(_i - front.GetSize(), _x);
    }
}

template <typename T>
void DualArrayDeque<T>::Add(int _i, T _x)
{
    if(_i < front.GetSize())
    {
        front.Add(front.GetSize() - _i - 1, _x);
    }
    else 
    {
        back.Add(_i - front.GetSize(), _x);
    }
    Balance();

    return;
}

template <typename T>
T DualArrayDeque<T>::Remove(int _i)
{
    T x;
    if( _i < front.GetSize())
    {
        x = front.Remove(front.GetSize() - _i - 1);
    }
    else 
    {
        x = back.Remove(_i - front.GetSize());
    }
    Balance();

    return x;
}

template <typename T>
void DualArrayDeque<T>::Print() noexcept
{
    front.Print();
    back.Print();

    return;
}