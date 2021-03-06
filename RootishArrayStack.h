#pragma once
template <typename T>
class RootishArrayStack
{
private:

	ArrayStack<T*> blocks;
	int n;

private:

	int	i2b(int _i);
	void Grow();
	void Shrink();

public:
	
	RootishArrayStack():n(0), blocks(){}
	~RootishArrayStack(){}

	T Get(int _i);

	T Set(int _i, T _x);

	bool Add(int _i, T _x);

	T Delete(int _i);
	
	void Print();
};

template <typename T>
int RootishArrayStack<T>::i2b(int _i)
{
	double db(static_cast<double>((-3.0f + std::sqrt(9.0f + 8.0f * _i)) / 2.0f));
	int b = static_cast<int>(std::ceil(db));
	return b;
}

template <typename T>
T RootishArrayStack<T>::Get(int _i)
{
	int b(i2b(_i));
	int j(_i - (b + 1) * b / 2);
	return blocks.Get(b).value()[j];
}

template <typename T>
T RootishArrayStack<T>::Set(int _i, T _x)
{
	int b(i2b(_i));
	int j(_i - (b + 1) * b / 2);

	T y = blocks.Get(b).value()[j];
	blocks.Get(b).value()[j] = _x;
	return y;
}

template <typename T>
bool RootishArrayStack<T>::Add(int _i, T _x)
{
	int r(blocks.GetSize());
	if (r * (r + 1) / 2 < this->n + 1)
	{
		Grow();
	}
	this->n++;

	for (int j = n - 1; j > _i; j--)
	{
		Set(j, Get(j - 1));
	}
	Set(_i, _x);
	return true;
}

template <typename T>
T RootishArrayStack<T>::Delete(int _i)
{
	T x = Get(_i);
	for (int j = _i; j < this->n - 1; j++)
	{
		Set(j, Get(j + 1));
	}
	this->n--;

	int r(blocks.GetSize());
	if ((r - 2) * (r - 1) / 2 >= this->n)
	{
		Shrink();
	}
	return x;
}
template <typename T>
void RootishArrayStack<T>::Grow()
{
	blocks.Add(blocks.GetSize(), new T[blocks.GetSize() + static_cast<int>(1)]);
	return;
}

template <typename T>
void RootishArrayStack<T>::Shrink()
{
	int r(blocks.GetSize());
	while (r > 0 && (r - 2) * (r - 1) / 2 >= this->n)
	{
		delete[] blocks.Delete(blocks.GetSize() - 1).value();
		r--;
	}
}

template <typename T>
void RootishArrayStack<T>::Print()
{
	for (int i = 0; i < this->n; i++)
	{
		std::cout << Get(i) << "\n";
	}
	return;
}
