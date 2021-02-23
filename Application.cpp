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
    bool appType(false);
    while (!appType)
    {
        std::cout <<
            "\t\t Array Test \n\n" <<
            "\t\t 1 : Array Stack \n" <<
            "\t\t >>";
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
            default:
            {
                std::cout <<
                "\n\t\t Undefined Command \n";
                break;
            }
        }
    }
    bool workCmd(false);
    while(!workCmd)
    {
         PrintType();
        std::cout << 
        "\n" <<
        "\t\t 1 : Add Item \n" <<
        "\t\t 2 : Delete Item \n" <<
        "\t\t 3 : Print Item \n" <<
        "\t\t 4 : Search Item \n"
        "\t\t 0 : Return to main menu \n";
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
        case 0:
            appType = false;
            Destroy();
            break;
        default:
            break;
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
            std::cout << "\t\t STACKARRAY \n";
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
    default:
        break;
    }
}