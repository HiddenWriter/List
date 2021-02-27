#include "pch.h"
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
					GetType() = TYPE::QUEUEARRAY;
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
                Delete();
                break;
            case 3:
                Print();
                break;
            case 4:
                Search();
                break;
            case 5:
                Replace();
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
				"\n\t 2 : Delete Item \n" <<
				"\n\t 3 : Print Item \n" <<
				"\n\t 4 : Search Item \n" <<
				"\n\t 5 : Replace Item \n" <<
				"\n\t 0 : Return to main menu \n";

			break;
		}
        case TYPE::QUEUEARRAY:
        {
            std::cout << "\t\t Array Queue \n";
            std::cout <<
                "\n" <<
                "\n\t 1 : Add Item \n" <<
                "\n\t 2 : Delete Item \n" <<
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
            int tempIndex(0);
            int type(0);
            std::cout <<
                "\n\t 1 : Push Item ( Auto Index )" <<
                "\n\t 2 : Specify index " <<
                "\n\t >> ";
            std::cin >> type;
            if (type == 1)
            {
                tempIndex = static_cast<ArrayStack<ItemType>*>(mPtr)->GetSize();
            }
            else
            {
				std::cout <<
                "\n\t Index : ";
				std::cin >> tempIndex;
				std::cout << "\n";
            }
			tempItem.SetAll();
            if (static_cast<ArrayStack<ItemType>*>(mPtr)->Add(tempIndex, tempItem)) sux = true;

        }
    case TYPE::QUEUEARRAY:
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

void Application::Delete()
{
    bool sux(false);
    switch (GetType())
    {
    case TYPE::STACKARRAY:
		{
			int tempIndex(0);
			std::cout <<
				"\n\t Index : ";
			std::cin >> tempIndex;
			if (static_cast<ArrayStack<ItemType>*>(mPtr)->DeleteByIndex(tempIndex)) sux = true;

			break;
		}
    case TYPE::QUEUEARRAY:
        {
            std::optional<ItemType> x;
            if (x = static_cast<ArrayQueue<ItemType>*>(mPtr)->Delete())
            {
                std::cout <<
                    "\n\t Deleted Item : " <<
                    x.value() <<
                    "\n";
                sux = true;
            }
            break;
        }
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

void Application::Print()
{
    switch (GetType())
    {
    case TYPE::STACKARRAY:
    {
        static_cast<ArrayStack<ItemType>*>(mPtr)->Print();
        break;
    }
    case TYPE::QUEUEARRAY:
    {
        static_cast<ArrayQueue<ItemType>*>(mPtr)->Print();
        break;
    }
    default:
        break;
    }
}

void Application::Search()
{
    bool sux(false);
    switch (GetType())
    {
    case TYPE::STACKARRAY:
    {
        int tempIndex(0);
        std::cout <<
            "\n\t Index : ";
        std::cin >> tempIndex;
        if (auto item = static_cast<ArrayStack<ItemType>*>(mPtr)->Get(tempIndex))
        {
            sux = true;
            std::cout << "\n" << item.value();
        }
        break;
    }
    case TYPE::QUEUEARRAY:
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

void Application::Replace()
{
    bool sux(false);
    switch (GetType())
    {
    case TYPE::STACKARRAY:
    {
        ItemType tempItem;
        int tempIndex(0);
        std::cout <<
            "\n\t Index : ";
        std::cin >> tempIndex;
        tempItem.SetAll();

        if (auto item = static_cast<ArrayStack<ItemType>*>(mPtr)->Set(tempIndex, tempItem))
        {
            sux = true;
            std::cout <<
                "\n\t Item Changed " <<
                "\n\t ID   : " << item.value().GetID() << " -> " << tempItem.GetID() <<
                "\n\t NAME : " << item.value().GetName() << " -> " << tempItem.GetName() << "\n";

        }
        break;
    }
    case TYPE::QUEUEARRAY:
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
    case TYPE::QUEUEARRAY:
        delete[] static_cast<ArrayQueue<ItemType>*>(mPtr);
        break;
    default:
        break;
    }
}