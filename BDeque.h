#pragma once

template <typename T>
class BDeque : public ArrayDeque<T>
{
public:
    BDeque(int _b)
    {
        ArrayDeque<T>::mCurrentIndex = 0;
        ArrayDeque<T>::mNumOfElem = 0;
        Array<int> z(_b + 1);
        ArrayDeque<T>::mArr = z;
    }
    ~BDeque() {}

};