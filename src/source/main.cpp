
#include "Libs.h"
#include "Application.h"


int main()
{

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "RU");
    
    

    Application app;
    app.run();

    return 0;

}