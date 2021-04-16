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
            std::cout << "\n\t 1 : List Interface : Array Stack "
                      << "\n\t 2 : FIFO Interface : Array Queue "
                      << "\n\t 3 : List Interface : Array Deque "
                      << "\n\t 0 : Terminate Programme"
                      << "\n\t >>";
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
            case 3:
            {
                GetType() = TYPE::DEQUEARRAY;
                mPtr = new ArrayDeque<ItemType>[1];
                appType = true;
                break;
            }
            case 0:
                return;
            default:
            {
                std::cout << "\n\t\t Undefined Command \n";
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

TYPE &Application::GetType() noexcept
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
        std::cout << "\n"
                  << "\n\t 1 : Add Item \n"
                  << "\n\t 2 : Remove Item \n"
                  << "\n\t 3 : Print Item \n"
                  << "\n\t 4 : Get Item \n"
                  << "\n\t 5 : Set Item \n"
                  << "\n\t 6 : Get Size \n "
                  << "\n\t 0 : Return to main menu \n";

        break;
    }
    case TYPE::QUEUEARRAY:
    {
        std::cout << "\t\t Array Queue \n";
        std::cout << "\n"
                  << "\n\t 1 : Add Item \n"
                  << "\n\t 2 : Remove Item \n"
                  << "\n\t 3 : Print Item \n"
                  << "\n\t 6 : Get Size \n"
                  << "\n\t 0 : Return to main menu \n";

        break;
    }
    case TYPE::DEQUEARRAY:
    {
        std::cout << "\t\t Array Deque \n";
        std::cout << "\n"
                  << "\n\t 1 : Add Item \n"
                  << "\n\t 2 : Remove Item \n"
                  << "\n\t 3 : Print Item \n"
                  << "\n\t 4 : Get Item \n"
                  << "\n\t 5 : Set Item \n"
                  << "\n\t 6 : Get Size \n"
                  << "\n\t 0 : Return to main menu \n";
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
    case TYPE::QUEUEARRAY:
    {
        ItemType tempItem;
        tempItem.SetAll();
        if (static_cast<ArrayQueue<ItemType> *>(mPtr)->Add(tempItem))
            sux = true;
        break;
    }
    case TYPE::DEQUEARRAY:
    {
        ItemType tempItem;
        int tempIndex(0);
        tempItem.SetAll();
        std::cout << "\n\t Index to Add : ";
        std::cin >> tempIndex;
        std::cout << "\n";
        static_cast<ArrayDeque<ItemType>*>(mPtr)->Add(tempIndex, tempItem);
        sux = true;
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

void Application::Remove()
{
    bool sux(false);
    ItemType tempItem;
    switch (GetType())
    {
    case TYPE::STACKARRAY:
    {
        std::cout << "\n";
        tempItem = static_cast<ArrayStack<ItemType> *>(mPtr)->Remove(
            static_cast<ArrayStack<ItemType> *>(mPtr)->GetSize() - 1);
        sux = true;

        break;
    }
    case TYPE::QUEUEARRAY:
    {
        tempItem = static_cast<ArrayQueue<ItemType> *>(mPtr)->Remove();
        sux = true;
        break;
    }
    case TYPE::DEQUEARRAY:
    {
        int idx(0);
        std::cout << "\n\t Index : ";
        std::cin >> idx;
        std::cout << "\n";
        tempItem = static_cast<ArrayDeque<ItemType> *>(mPtr)->Remove(idx);
        sux = true;
        break;
    }
    default:
        break;
    }
    if (sux)
    {
        std::cout << 
        msg.first << "\n" <<
        "Removed Item : << " << tempItem << '\n';
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
        static_cast<ArrayStack<ItemType> *>(mPtr)->Print();
        break;
    }
    case TYPE::QUEUEARRAY:
    {
        static_cast<ArrayQueue<ItemType> *>(mPtr)->Print();
        break;
    }
    case TYPE::DEQUEARRAY:
    {
        static_cast<ArrayDeque<ItemType> *>(mPtr)->Print();
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
    case TYPE::QUEUEARRAY:
    {
        std::cout << "\n\t Not implemented \n";
        break;
    }

    default:
        break;
    case TYPE::DEQUEARRAY:
    {
        int idx(0);
        std::cout << "\n\t Index : ";
        std::cin >> idx;
        item = static_cast<ArrayDeque<ItemType> *>(mPtr)->Get(idx);
        sux = true;
        break;
    }
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
    case TYPE::QUEUEARRAY:
    {
        std::cout << "\n\t Not implemented \n";
        break;
    }
    case TYPE::DEQUEARRAY:
    {
        ItemType tempItem;
        int idx(0);

        std::cout << "\n\t Index : ";
        std::cin >> idx;
        tempItem.SetAll();

        item = static_cast<ArrayDeque<ItemType> *>(mPtr)->Set(idx, tempItem);
        sux = true;
        std::cout << 
        "\n\t Item Changed " << 
        "\n\t ID   : " << item.GetID() << " -> " << tempItem.GetID() << 
        "\n\t NAME : " << item.GetName() << " -> " << tempItem.GetName() << "\n";
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
        delete[] static_cast<ArrayStack<ItemType> *>(mPtr);
        break;
    case TYPE::QUEUEARRAY:
        delete[] static_cast<ArrayQueue<ItemType> *>(mPtr);
        break;
    case TYPE::DEQUEARRAY:
        delete[] static_cast<ArrayDeque<ItemType> *>(mPtr);
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
        std::cout << 
        "\n\t Current Size : " << static_cast<ArrayStack<ItemType> *>(mPtr)->GetSize() << "\n";
        break;
    case TYPE::QUEUEARRAY:
        std::cout << 
        "\n\t Current SIze : " << static_cast<ArrayQueue<ItemType> *>(mPtr)->GetSize() << "\n";
        break;
    case TYPE::DEQUEARRAY:
        delete[] static_cast<ArrayDeque<ItemType> *>(mPtr);
        break;
    default:
        break;
    }
}