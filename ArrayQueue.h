#pragma once

template <typename T>
class ArrayQueue
{
private:
	Array<T> mArr;
	int mCurrentIndex;
	int mNumOfElem;

private:

	void Resize();

public:
	
	ArrayQueue();
	~ArrayQueue() {}
	bool Add(T _x);
	
	std::optional<T> Delete();
	
	void Print();
};

template <typename T>
ArrayQueue<T>::ArrayQueue()
	: mArr(1), mCurrentIndex(0), mNumOfElem(0)
{}

template <typename T>
bool ArrayQueue<T>::Add(T _x)
{
	if (mNumOfElem + 1 > mArr.GetLength()) Resize();

	mArr[(mNumOfElem + mCurrentIndex) % mArr.GetLength()] = _x;
	mNumOfElem++;

	return true;
}

template <typename T>
std::optional<T> ArrayQueue<T>::Delete()
{
	if (mNumOfElem == 0) { return {}; }
	T x = mArr[mCurrentIndex];
	mCurrentIndex = (mCurrentIndex + 1) % mArr.GetLength();
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
		b[i] = mArr[(mCurrentIndex + i) % mArr.GetLength()];
	}
	mArr = b;
	mCurrentIndex = 0;
	
	return;
}

template <typename T>
void ArrayQueue<T>::Print()
{
	for (int i = 0; i < mNumOfElem; i++)
	{
		std::cout << mArr[(mCurrentIndex + i) % mArr.GetLength()];
	}
	return;
}
