#include "../headers/Application.h"
#include "../headers/models/Group.h"


Application::Application()
{
    this->controller.setConn(&this->connector);
    this->interface.setController(&this->controller);
}


void Application::run()
{
    this->interface.runPolling();
}
