#pragma once
template <typename T>
class ArrayDeque
{
private:

	Array<T> mArr;
	int mCurrentIndex;
	int mNumOfElem;

private:

	void Resize();

public:

	ArrayDeque();
	~ArrayDeque() {}

	std::optional<T> Get(int _i);

	std::optional<T> Set(int _i, T _x);
	
	bool Add(int _i, T _x);

	std::optional<T> Delete(int _i);

	void Print();

};

template <typename T>
ArrayDeque<T>::ArrayDeque()
	: mArr(1), mCurrentIndex(0), mNumOfElem(0)
{}

template <typename T>
std::optional<T> ArrayDeque<T>::Get(int _i)
{
	if (_i >= mArr.GetLength()) return {};
	else return mArr[(mCurrentIndex + _i) % mArr.GetLength()];
}

template <typename T>
std::optional<T> ArrayDeque<T>::Set(int _i, T _x)
{
	if (_i >= mArr.GetLength()) return {};

	T y = mArr[(mCurrentIndex + _i) % mArr.GetLength()];
	mArr[(mCurrentIndex + _i) % mArr.GetLength()] = _x;
	return y;
}

template <typename T>
bool ArrayDeque<T>::Add(int _i, T _x)
{
	if (_i > mArr.GetLength()) return false;
	if (mNumOfElem + 1 > mArr.GetLength()) Resize();
	if (_i < mNumOfElem / 2)
	{
		mCurrentIndex = (mCurrentIndex == 0) ? mArr.GetLength() - 1 : mCurrentIndex - 1;
		for (int k = 0; k < _i; k++)
		{
			mArr[(mCurrentIndex + k) % mArr.GetLength()] = mArr[(mCurrentIndex + k + 1) % mArr.GetLength()];
		}
	}
	else
	{
		for (int k = mNumOfElem; k > _i; k--)
		{
			mArr[(mCurrentIndex + k) % mArr.GetLength()] = mArr[(mCurrentIndex + k - 1) % mArr.GetLength()];
		}
	}
	mArr[(_i + mCurrentIndex) % mArr.GetLength()] = _x;
	mNumOfElem++;
	return true;
}

template <typename T>
std::optional<T> ArrayDeque<T>::Delete(int _i)
{
	if (_i > mArr.GetLength()) return {};
	
	T y = mArr[(mCurrentIndex + _i) % mArr.GetLength()];

	if (_i < mNumOfElem / 2)
	{
		for (int k = _i; k > 0; k--)
		{
			mArr[(mCurrentIndex + k) % mArr.GetLength()] = mArr[(mCurrentIndex + k - 1) % mArr.GetLength()];
		}
		mCurrentIndex = (mCurrentIndex + 1) % mArr.GetLength();
	}
	else
	{
		for (int k = _i; k < mNumOfElem - 1; k++)
		{
			mArr[(mCurrentIndex + k) % mArr.GetLength()] = mArr[(mCurrentIndex + k + 1) % mArr.GetLength()];
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
		std::cout << mArr[(mCurrentIndex + i) % mArr.GetLength()];
	}
	return;
}

template <typename T>
void ArrayDeque<T>::Resize()
{
	Array<T> b(std::max(2 * mNumOfElem, 1));
	for (int k = 0; k < mNumOfElem; k++)
	{
		b[k] = mArr[(mCurrentIndex + k) % mArr.GetLength()];
	}
	mArr = b;
	mCurrentIndex = 0;

	return;
}
