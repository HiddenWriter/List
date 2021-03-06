#pragma once
template <typename T>
class ArrayStack
{
public:

    ArrayStack();
    ~ArrayStack();
    
    ArrayStack<T>& operator=(Array<T>& _arr);
    ArrayStack<T>& operator=(int _int);
    std::optional<T> Get(int _i);
    std::optional<T> Set(int _i, T _x);
    bool Add(int _i, T _x);
    std::optional<T> Delete(int _i);
    const int GetSize() const noexcept;
    const int GetLength() const noexcept;
    void Print() noexcept;

private:

    void Resize();

protected:

    Array<T> mArr;
    int mSize;

};
template <typename T>
ArrayStack<T>::ArrayStack()
    : mArr(1), mSize(0)
{}

template <typename T>
ArrayStack<T>::~ArrayStack()
{
    return;
}
template <typename T>
std::optional<T> ArrayStack<T>::Get(int _i)
{
    if (_i > this->mSize) return {};
    else return mArr[_i];
}

template <typename T>
std::optional<T> ArrayStack<T>::Set(int _i, T _x)
{
    if (_i > this->mSize)
    {
        return {};
    }
    T y = mArr[_i];
    mArr[_i] = _x;
    return y;
}

template <typename T>
bool ArrayStack<T>::Add(int _i, T _x)
{
    if (_i > mArr.GetLength()) return false;
    if (mSize + 1 > mArr.GetLength()) 
    {
        Resize();
    }

    for (int j = mSize; j > _i; j--)
    {
        mArr[j] = mArr[j - 1];
    }
    mArr[_i] = _x;
    mSize++;
    return true;
}


template <typename T>
std::optional<T> ArrayStack<T>::Delete(int _i)
{
    if (_i > mSize - 1)
    {
        return {};
    }
    else 
    {
        T x = mArr[_i];
        for(int j = _i; j < mSize - 1; j++)
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
}

template <typename T>
void ArrayStack<T>::Resize()
{
    Array<T> resizedArray(std::max(2 * mSize, 1));
    for(int i = 0; i < mSize; i++)
    {
        resizedArray[i] = mArr[i];
    }
    mArr = resizedArray;
    return;
}

template <typename T>
const int ArrayStack<T>::GetSize() const noexcept
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
ArrayStack<T>& ArrayStack<T>::operator=(Array<T>& _arr)
{
    this->mArr = _arr;
    return *this;
}

template <typename T>
ArrayStack<T>& ArrayStack<T>::operator=(int _int)
{
    this->mSize = _int;
    return *this;
}

template <typename T>
const int ArrayStack<T>::GetLength() const noexcept
{
    return mArr.GetLength();
}
