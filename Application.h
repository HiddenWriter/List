#pragma once

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

    void Delete();

    void Print();

    void Destroy();

    void Search();

private:
    int mCmd;
    void* mPtr;
    std::pair<std::string, std::string> msg;
};