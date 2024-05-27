#ifndef APPLICATION_H
#define APPLICATION_H


#include "/home/kud/Projects/ProgLanCoursework/headers/Interface.h"
#include "/home/kud/Projects/ProgLanCoursework/headers/DBConnector.h"
#include "/home/kud/Projects/ProgLanCoursework/headers/Controller.h"
#include "/home/kud/Projects/ProgLanCoursework/headers/PageBuilder.h"


class Application
{

    public:
        Application();
        void run();

    private:
        DBConnector connector;
        Controller controller;
        PageBuilder page_builder;
        Interface interface;

};

#endif //APPLICATION_H
