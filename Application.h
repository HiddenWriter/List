#pragma once

// Represents List interface
class Application
{
public:
    Application();
    Application(Application&) = delete;
    Application& operator=(Application&) = delete;
    ~Application();

    void Run();

    TYPE& GetType() noexcept;

    void PrintType() noexcept;

    void Add();

    void Remove();

    void Print();

    void Destroy();

    void Set();

    void Get();

    void Size();    
private:
    int mCmd;
    void* mPtr;
    std::pair<std::string, std::string> msg;
};