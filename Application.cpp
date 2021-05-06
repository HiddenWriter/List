#include "Application.h"

Application::Application()
    : mCmd(-1)
{
    msg.first = "\t\t Successfully Done. \n";
    msg.second = "\t\t Error. \t\n";
}
Application::~Application()
{
}
void Application::Run()
{
    while (1)
    {
        bool appType(false);
        while (!appType)
        {
            std::cout <<
                "\n\t       Array Test \n" <<
                "\n\t 1 : Array Stack " <<
                "\n\t 2 : Array Queue " <<
                "\n\t 0 : Terminate Programme" <<
                "\n\t >>";
            std::cin >> mCmd;
            std::cout << "\n";
            switch (mCmd)
            {
				case 1:
				{
					GetType() = TYPE::STACKARRAY;
					mPtr = new ArrayStack<ItemType>[1];
					appType = true;
					break;
				}
				case 2:
				{
					GetType() = TYPE::ARRAYQUEUE;
					mPtr = new ArrayQueue<ItemType>[1];
					appType = true;
					break;
				}
				case 0:
					return;
				default:
				{
					std::cout <<
						"\n\t\t Undefined Command \n";
					break;
				}
            }
        }
        bool workCmd(false);
        while (!workCmd)
        {
            PrintType();
            std::cin >> mCmd;

            switch (mCmd)
            {
            case 1:
                Add();
                break;
            case 2:
                Remove();
                break;
            case 3:
                Print();
                break;
            case 4:
                Get();
                break;
            case 5:
                Set();
                break;
            case 6:
                Size();
                break;
            case 0:
                workCmd = true;
                Destroy();
                break;
            default:
                break;
            }
        }
    }
}

TYPE& Application::GetType() noexcept
{
    static TYPE type(TYPE::UNDEFINED);
    return type;
}

void Application::PrintType() noexcept
{
    switch (GetType())
    {
		case TYPE::STACKARRAY:
		{
			std::cout << "\t\t Array Stack \n";
			std::cout <<
				"\n" <<
				"\n\t 1 : Add Item \n" <<
				"\n\t 2 : Remove Item \n" <<
				"\n\t 3 : Print Item \n" <<
				"\n\t 4 : Get Item \n" <<
				"\n\t 5 : Set Item \n" <<
                "\n\t 6 : Size \n" <<
				"\n\t 0 : Return to main menu \n";

			break;
		}
        case TYPE::ARRAYQUEUE:
        {
            std::cout << "\t\t Array Queue \n";
            std::cout <<
                "\n" <<
                "\n\t 1 : Add Item \n" <<
                "\n\t 2 : Remove Item \n" <<
                "\n\t 3 : Print Item \n" <<
                "\n\t 0 : Return to main menu \n";
            break;
        }
    default:
        break;
    }
}

void Application::Add()
{
    bool sux(false);
    switch (GetType())
    {
    case TYPE::STACKARRAY:
        {
		    ItemType tempItem;
            tempItem.SetAll();
            static_cast<ArrayStack<ItemType> *>(mPtr)->Add(
            static_cast<ArrayStack<ItemType> *>(mPtr)->GetSize(), tempItem);
            sux = true;
            break;
        }
    case TYPE::ARRAYQUEUE:
        {
			ItemType tempItem;
			tempItem.SetAll();
			if (static_cast<ArrayQueue<ItemType>*>(mPtr)->Add(tempItem)) sux = true;
		}
        break;
    default:
        break;
    }
    if (sux)
    {
        std::cout << msg.first;
    }
    else
    {
        std::cout << msg.second;
    }
}

void Application::Remove()
{
    ItemType tempItem;
    bool sux(false);
    switch (GetType())
    {
    case TYPE::STACKARRAY:
		{
			if (static_cast<ArrayStack<ItemType>*>(mPtr)->GetSize() == 0) break;
            else 
            {
			    int tempIndex(static_cast<ArrayStack<ItemType>*>(mPtr)->GetSize() - 1);
			    tempItem = static_cast<ArrayStack<ItemType>*>(mPtr)->Remove(tempIndex); 
                sux = true;
            }
			break;
		}
    case TYPE::ARRAYQUEUE:
        {
            if (static_cast<ArrayQueue<ItemType>*>(mPtr)->GetSize() == 0) break;
            else
            {
                tempItem = static_cast<ArrayQueue<ItemType> *>(mPtr)->Remove();
                sux = true;
            }
            break;
        }
    default:
        break;
    }
    if (sux)
    {
        std::cout << 
        msg.first << "\n" <<
        "\t Removed Item \n" <<
        tempItem << '\n';
    }
    else
    {
        std::cout << msg.second;
    }
}

void Application::Print()
{
    switch (GetType())
    {
    case TYPE::STACKARRAY:
    {
        static_cast<ArrayStack<ItemType>*>(mPtr)->Print();
        break;
    }
    case TYPE::ARRAYQUEUE:
    {
        static_cast<ArrayQueue<ItemType>*>(mPtr)->Print();
        break;
    }
    default:
        break;
    }
}

void Application::Get()
{
    ItemType item;
    bool sux(false);
    switch (GetType())
    {
    case TYPE::STACKARRAY:
    {
        int tempIndex(0);
        std::cout << "\n\t Index : ";
        std::cin >> tempIndex;
        if (tempIndex >= static_cast<ArrayStack<ItemType> *>(mPtr)->GetSize());
        else
        {
            item = static_cast<ArrayStack<ItemType> *>(mPtr)->Get(tempIndex);
            sux = true;
        }
        break;
    }
    case TYPE::ARRAYQUEUE:
        std::cout <<
            "\n\t Not implemented \n";
        break;
    default:
        break;
    }
    if (sux)
    {
        std::cout << msg.first << "\n"
                  << item << "\n";
    }
    else
    {
        std::cout << msg.second;
    }
}

void Application::Set()
{
    ItemType item;
    bool sux(false);
    switch (GetType())
    {
    case TYPE::STACKARRAY:
    {
        ItemType tempItem;
        int tempIndex(0);
        std::cout << "\n\t Index : ";
        std::cin >> tempIndex;
        tempItem.SetAll();
        item = static_cast<ArrayStack<ItemType>*>(mPtr)->Set(tempIndex, tempItem);
        sux = true;
        std::cout << 
        "\n\t Item Changed "<< 
        "\n\t ID   : " << item.GetID() << " -> " << tempItem.GetID() << 
        "\n\t NAME : " << item.GetName() << " -> " << tempItem.GetName() << "\n";
        break;
    }
    case TYPE::ARRAYQUEUE:
        std::cout <<
            "\n\t Not implemented \n";
        break;
    default:
        break;
    }
    if (sux)
    {
        std::cout << msg.first;
    }
    else
    {
        std::cout << msg.second;
    }
}
void Application::Destroy()
{
    switch (GetType())
    {
    case TYPE::STACKARRAY:
        delete[] static_cast<ArrayStack<ItemType>*>(mPtr);
        break;
    case TYPE::ARRAYQUEUE:
        delete[] static_cast<ArrayQueue<ItemType>*>(mPtr);
        break;
    default:
        break;
    }
}

void Application::Size() 
{
    switch (GetType())
    {
        case TYPE::STACKARRAY:
        {
            std::cout << 
            "\n\t Current Size \n" << 
            static_cast<ArrayStack<ItemType>*>(mPtr)->GetSize() << "\n";
            break;
        }
        case TYPE::ARRAYQUEUE:
        {
            std::cout << 
            "\n\t Current Size \n" << 
            static_cast<ArrayQueue<ItemType>*>(mPtr)->GetSize() << "\n";
            break;
        }
        default:
            break;
    }
}