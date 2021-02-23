#pragma once
class ItemType
{
public:
	ItemType()
		: mID(0), mName("STRING")
	{}
	ItemType(int _id, std::string _name)
		: mID(_id), mName(_name)
	{}
	std::string GetName() const noexcept
	{
		return this->mName;
	}
	int GetID() const noexcept
	{
		return this->mID;
	}
	void SetID(int _id)
	{
		mID = _id;
		return;
	}
	void SetName(std::string _name)
	{
		mName = _name;
		return;
	}
	void SetIDFromKeyboard()
	{
		std::cout <<
			"\t Type ID : ";
		std::cin >> this->mID;
	}
	void SetNameFromKeyboard()
	{
		std::cout <<
			"\t Type Name : ";
		std::cin >> this->mName;
	}
	void PrintDataInfo() const noexcept
	{
		std::cout <<
			"\t ID   : " << this->mID << "\n"
			"\t NAME : " << this->mName << "\n";
		return;
	}
	void SetAll() 
	{
		SetIDFromKeyboard();
		SetNameFromKeyboard();
		return;
	}
public:
	bool operator>(const ItemType& _data)
	{
		if (this->mID > _data.mID) return true;
		else return false;
	}
	bool operator>=(const ItemType& _data)
	{
		if (this->mID >= _data.mID) return true;
		else return false;
	}
	bool operator<(const ItemType& _data)
	{
		if (this->mID < _data.mID) return true;
		else return false;
	}
	bool operator<=(const ItemType& _data)
	{
		if (this->mID <= _data.mID) return true;
		else return false;
	}
	bool operator==(const ItemType& _data)
	{
		if (this->mID == _data.mID) return true;
		else return false;
	}
	bool operator!=(const ItemType& _data)
	{
		if (this->mID != _data.mID) return true;
		else return false;
	}

	friend std::ostream& operator<<(std::ostream& _os, const ItemType& _data)
	{
		std::cout <<
			"\t ID    : " << _data.mID << "\n"
			"\t Name  : " << _data.mName << "\n";
		return _os;
	}
protected:
	std::string mName;
	int mID;
};