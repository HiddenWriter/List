#include "pch.h"

int main(void)  
{
    std::unique_ptr<Application> app = std::make_unique<Application>();
    app->Run();

    return 0;
}