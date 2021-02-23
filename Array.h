#pragma once

template <typename T>
class Array
{
public:
    Array();
    ~Array();
    Array(int _length);
    Array& operator=(Array& _arr);
    T& operator[](int _i);
    
    const int GetLength() const noexcept;

protected:
    int mLength;
    T* mArray;
};

template <typename T>
Array<T>::Array(int _length)
    : mLength(_length)
{
    mArray = new T[mLength];
}

template <typename T>
Array<T>::Array()
    : mLength(9)
{
    mArray = new T[9];   
}

template <typename T>
Array<T>::~Array()
{
    delete[] mArray;
}

template <typename T>
T& Array<T>::operator[](int _i)
{
    assert(_i >= 0 && _i < mLength);
    return mArray[_i];
}

template <typename T>
Array<T>& Array<T>::operator=(Array<T>& _arr)
{
    if (mArray != nullptr)
    {
        delete[] mArray;
    }
    mArray = _arr.mArray;
    _arr.mArray = nullptr;
    mLength = _arr.mLength;
    return *this;
}

template <typename T>
const int Array<T>::GetLength() const noexcept
{
    return mLength;
}