#pragma once
template <typename T>
class DualArrayDeque
{
private:

	ArrayStack<T> front;
	ArrayStack<T> back;

public:
	DualArrayDeque();
	~DualArrayDeque() {}

	int GetSize() const noexcept;

	std::optional<T> Get(int _i);

	std::optional<T> Set(int _i, T _x);

	bool Add(int _i, T _x);
	
	std::optional<T> Delete(int _i);

	void Balance();

	void Print() noexcept;
};

template <typename T>
DualArrayDeque<T>::DualArrayDeque()
{}

template <typename T>
int DualArrayDeque<T>::GetSize() const noexcept
{
	return front.GetSize() + back.GetSize();
}

template <typename T>
std::optional<T> DualArrayDeque<T>::Set(int _i, T _x)
{
	if (_i > 2 * front.GetSize() || _i < 0) return {};

	if (_i < front.GetSize())
	{
		return front.Set(front.GetSize() - _i - 1, _x);
	}
	else
	{
		return back.Set(_i - front.GetSize(), _x);
	}
}

template <typename T>
std::optional<T> DualArrayDeque<T>::Get(int _i)
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
bool DualArrayDeque<T>::Add(int _i, T _x)
{
	bool sux(false);
	if (_i < front.GetSize())
	{
		sux = front.Add(front.GetSize() - _i - 1, _x);
	}
	else
	{
		sux = back.Add(_i - front.GetSize(), _x);
	}
	if (sux)
	{
		Balance();
		return true;
	}
	else
	{
		return false;
	}
}

template <typename T>
std::optional<T> DualArrayDeque<T>::Delete(int _i)
{
	if (_i < 0 || _i > 2 * front.GetSize()) return {};
	std::optional<T> sux;
	if (_i < front.GetSize())
	{
		sux = front.Delete(front.GetSize() - _i - 1);
	}
	else
	{
		sux = back.Delete(_i - front.GetSize());
	}
	if (sux)
	{
		Balance();
		return sux;
	}
	else
	{
		return {};
	}
}

template <typename T>
void DualArrayDeque<T>::Balance()
{
	if (3 * front.GetSize() < back.GetSize() ||
		3 * back.GetSize() < front.GetSize())
	{
		T temp;
		int numOfElem(front.GetSize() + back.GetSize());
		int numFront(numOfElem / 2);
		int numBack(numOfElem - numFront);
		Array<T> arrFront(std::max(2 * numFront, 1));
		Array<T> arrBack(std::max(2 * numBack, 1));
		for (int i = 0; i < numFront; i++)
		{
			arrFront[numFront - i - 1] = Get(i).value();
		}
		for (int i = 0; i < numBack; i++)
		{
			arrBack[i] = Get(i + numFront).has_value() ? Get(i + numFront).value() : temp;
		}
		front = arrFront;
		front = numFront;
		back = arrBack;
		back = numBack;
	}
	return;
}

template <typename T>
void DualArrayDeque<T>::Print() noexcept
{
	for (int i = 0; i < front.GetSize(); i++)
	{
		std::cout <<
			"\n" <<
			front.Get(front.GetSize() - i - 1).value() << "\t ( Front Index : " << i << " )\n";
	}
	for (int i = 0; i < back.GetSize(); i++)
	{
		std::cout <<
			"\n" <<
			back.Get(i).value() << "\t ( Back Index : " << front.GetSize() + i << " ) \n";
	}
	return;
}
