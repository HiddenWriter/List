#include "Application.h"

static int numOfTestCase (0);

Application::Application()
    : mCmd(-1)
{
    msg.first = "\t\t Successfully Done. \n";
    msg.second = "\t\t Error. \t\n";
}

Application::~Application()
{
}

bool Application::GenerateTestCase()
{
    std::ofstream outFile;
    outFile.open("TestCase.txt", std::ofstream::out | std::ofstream::trunc);
    if(!outFile)
    {
        std::cerr << 
        "\n\t Failed to Generating test case. \n";
        outFile.close();
        return false;
    }
    else
    {
        for(int i = 0; i < numOfTestCase; i++)
        {
            outFile << std::rand() % numOfTestCase << " " << std::rand() % numOfTestCase << "\n";
        }
        outFile.close();
        return true;
    }
}

bool Application::LoadTestCase() 
{
    std::cout << 
    "\n\t Type (only positive integer) number of test cases : ";
    std::cin >> numOfTestCase;
    std::cout << "\n";
    GenerateTestCase();

    std::fstream inFile;
    inFile.open("TestCase.txt");
    if(!inFile)
    {
        std::cout << 
        "\n\t Incorrect test case file path. \n";
        inFile.close();
        return false;
    }
    else 
    {
        int id(0);
        std::string name;
        for(int i = 0; i < numOfTestCase; i++)
        {
            inFile >> id;
            inFile >> name;
            ItemType tempItem(id, name);
            switch (GetType())
            {
                case TYPE::STACKARRAY:
                    static_cast<ArrayStack<ItemType>*>(mPtr)->Add
                    (
                        static_cast<ArrayStack<ItemType>*>(mPtr)->GetSize(), tempItem
                    );
                    break;
                case TYPE::ARRAYQUEUE:
                    static_cast<ArrayQueue<ItemType>*>(mPtr)->Add(tempItem);
                    break;
                case TYPE::ARRAYDEQUE:
                    static_cast<ArrayDeque<ItemType>*>(mPtr)->Add
                    (
                        static_cast<ArrayDeque<ItemType>*>(mPtr)->GetSize(), tempItem
                    );
                    break;
                case TYPE::DUALARRAYDEQUE:
                    static_cast<DualArrayDeque<ItemType>*>(mPtr)->Add
                    (
                        static_cast<DualArrayDeque<ItemType>*>(mPtr)->GetSize(), tempItem
                    );
                    break;
                default:
                break;
            }
    }
        inFile.close();
        return true;    
    }
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
                      << "\n\t 4 : List Interface : Dual Array Deque "
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
                GetType() = TYPE::ARRAYQUEUE;
                mPtr = new ArrayQueue<ItemType>[1];
                appType = true;
                break;
            }
            case 3:
            {
                GetType() = TYPE::ARRAYDEQUE;
                mPtr = new ArrayDeque<ItemType>[1];
                appType = true;
                break;
            }
            case 4:
            {
                GetType() = TYPE::DUALARRAYDEQUE;
                mPtr = new DualArrayDeque<ItemType>[1];
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
            case 99:
                LoadTestCase();
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
                  << "\n\t 99: Load Test Case \n"
                  << "\n\t 0 : Return to main menu \n";

        break;
    }
    case TYPE::ARRAYQUEUE:
    {
        std::cout << "\t\t Array Queue \n";
        std::cout << "\n"
                  << "\n\t 1 : Add Item \n"
                  << "\n\t 2 : Remove Item \n"
                  << "\n\t 3 : Print Item \n"
                  << "\n\t 6 : Get Size \n"
                  << "\n\t 99: Load Test Case \n"
                  << "\n\t 0 : Return to main menu \n";

        break;
    }
    case TYPE::ARRAYDEQUE:
    {
        std::cout << "\t\t Array Deque \n";
        std::cout << "\n"
                  << "\n\t 1 : Add Item \n"
                  << "\n\t 2 : Remove Item \n"
                  << "\n\t 3 : Print Item \n"
                  << "\n\t 4 : Get Item \n"
                  << "\n\t 5 : Set Item \n"
                  << "\n\t 6 : Get Size \n"
                  << "\n\t 99: Load Test Case \n"
                  << "\n\t 0 : Return to main menu \n";
        break;
    }
    case TYPE::DUALARRAYDEQUE:
    {
        std::cout << 
        "\n\t\t Dual Array Deque \n" <<
        "\n\t 1 : Add Item \n" <<
        "\n\t 2 : Remove Item \n" <<
        "\n\t 3 : Print Item \n " <<
        "\n\t 4 : Get Item \n" <<
        "\n\t 5 : Set Item \n" <<
        "\n\t 6 : Get Size \n" <<
        "\n\t 99: Load Test Case \n" <<
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
        if (static_cast<ArrayQueue<ItemType> *>(mPtr)->Add(tempItem))
            sux = true;
        break;
    }
    case TYPE::ARRAYDEQUE:
    {
        ItemType tempItem;
        int ctrlHT(0);
        tempItem.SetAll();
        std::cout << 
                "\n\t Add 0 index (1) "
                "\n\t Add Last index (2) \n";
        std::cin >> ctrlHT;
        std::cout << "\n";
        if(ctrlHT == 1) static_cast<ArrayDeque<ItemType>*>(mPtr)->Add(0, tempItem);
        else static_cast<ArrayDeque<ItemType>*>(mPtr)->Add(static_cast<ArrayDeque<ItemType>*>(mPtr)->GetSize(), tempItem);
        sux = true;
        break;
    }
    case TYPE::DUALARRAYDEQUE:
    {
        ItemType tempItem;
        int ctrlHT(0);
        tempItem.SetAll();
        std::cout <<
        "\n\t Add to 0 index (1)"
        "\n\t Add to last index (2) \n";
        std::cin >> ctrlHT;
        if(ctrlHT == 1) static_cast<DualArrayDeque<ItemType>*>(mPtr)->Add(0, tempItem);
        else static_cast<DualArrayDeque<ItemType>*>(mPtr)->Add(static_cast<DualArrayDeque<ItemType>*>(mPtr)->GetSize(), tempItem);
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
        if(static_cast<ArrayStack<ItemType>*>(mPtr)->GetSize() == 0) break;
        else
        {
            std::cout << "\n";
            tempItem = static_cast<ArrayStack<ItemType> *>(mPtr)->Remove(
                static_cast<ArrayStack<ItemType> *>(mPtr)->GetSize() - 1);
            sux = true;
        }
        break;
    }
    case TYPE::ARRAYQUEUE:
    {
        if(static_cast<ArrayQueue<ItemType>*>(mPtr)->GetSize() == 0) break;
        else
        {
            tempItem = static_cast<ArrayQueue<ItemType> *>(mPtr)->Remove();
            sux = true;
            break;
        }
    }
    case TYPE::ARRAYDEQUE:
    {
        if(static_cast<ArrayDeque<ItemType>*>(mPtr)->GetSize() == 0) break;
        else
        {
            int ctrlFL(0);
            std::cout << 
                    "\n\t Remove 0 index (1) " <<
                    "\n\t Remove last index (2) \n";
            std::cin >> ctrlFL;
            std::cout << "\n";
            if(ctrlFL == 1) tempItem = static_cast<ArrayDeque<ItemType> *>(mPtr)->Remove(0);
            else tempItem = static_cast<ArrayDeque<ItemType>*>(mPtr)->Remove(static_cast<ArrayDeque<ItemType>*>(mPtr)->GetSize() - 1);
            sux = true;
            break;
        }
    }
    case TYPE::DUALARRAYDEQUE:
    {
        if(static_cast<DualArrayDeque<ItemType>*>(mPtr)->GetSize() == 0) break;
        else
        {
            int ctrlFL(0);
            std::cout << 
                    "\n\t Remove 0 index (1) " <<
                    "\n\t Remove last index (2) \n";
            std::cin >> ctrlFL;
            std::cout << "\n";
            if(ctrlFL == 1) tempItem = static_cast<DualArrayDeque<ItemType> *>(mPtr)->Remove(0);
            else tempItem = static_cast<DualArrayDeque<ItemType>*>(mPtr)->Remove(static_cast<DualArrayDeque<ItemType>*>(mPtr)->GetSize() - 1);
            sux = true;
            break;
        }
    }
    default:
        break;
    }
    if (sux)
    {
        std::cout << 
        msg.first << "\n" <<
        "\t - Removed Item - \n" << tempItem << '\n';
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
    case TYPE::ARRAYQUEUE:
    {
        static_cast<ArrayQueue<ItemType> *>(mPtr)->Print();
        break;
    }
    case TYPE::ARRAYDEQUE:
    {
        static_cast<ArrayDeque<ItemType> *>(mPtr)->Print();
        break;
    }
    case TYPE::DUALARRAYDEQUE:
    {
        static_cast<DualArrayDeque<ItemType>*>(mPtr)->Print();
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
    {
        std::cout << "\n\t Not implemented \n";
        break;
    }
    case TYPE::ARRAYDEQUE:
    {
        int idx(0);
        std::cout << "\n\t Index : ";
        std::cin >> idx;
        item = static_cast<ArrayDeque<ItemType> *>(mPtr)->Get(idx);
        sux = true;
        break;
    }
    case TYPE::DUALARRAYDEQUE:
    {
        int idx(0);
        std::cout << "\n\t Index : ";
        std::cin >> idx;
        item = static_cast<DualArrayDeque<ItemType> *>(mPtr)->Get(idx);
        sux = true;
        break;
    }
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
    {
        std::cout << "\n\t Not implemented \n";
        break;
    }
    case TYPE::ARRAYDEQUE:
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
    case TYPE::DUALARRAYDEQUE:
    {
        ItemType tempItem;
        int idx(0);

        std::cout << "\n\t Index : ";
        std::cin >> idx;
        tempItem.SetAll();

        item = static_cast<DualArrayDeque<ItemType> *>(mPtr)->Set(idx, tempItem);
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
    case TYPE::ARRAYQUEUE:
        delete[] static_cast<ArrayQueue<ItemType> *>(mPtr);
        break;
    case TYPE::ARRAYDEQUE:
        delete[] static_cast<ArrayDeque<ItemType> *>(mPtr);
        break;
    case TYPE::DUALARRAYDEQUE:
        delete[] static_cast<DualArrayDeque<ItemType>*>(mPtr);
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
    case TYPE::ARRAYQUEUE:
        std::cout << 
        "\n\t Current SIze : " << static_cast<ArrayQueue<ItemType> *>(mPtr)->GetSize() << "\n";
        break;
    case TYPE::ARRAYDEQUE:
        std::cout <<
        "\n\t Current SIze : " << static_cast<ArrayDeque<ItemType> *>(mPtr)->GetSize() << "\n";
        break;
    case TYPE::DUALARRAYDEQUE:
        std::cout <<
        "\n\t Current SIze : " << static_cast<DualArrayDeque<ItemType> *>(mPtr)->GetSize() << "\n";
        break;
    default:
        break;
    }
}