#ifndef APPLICATION_H
#define APPLICATION_H


#include "Interface.h"
#include "DBConnector.h"
#include "Controller.h"


class Application
{

    public:
        Application();
        void run();

    private:
        DBConnector connector;
        Controller controller;
        Interface inter;

};

#endif //APPLICATION_H
