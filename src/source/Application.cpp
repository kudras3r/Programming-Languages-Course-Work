#include "Application.h"


Application::Application()
{
    this->controller.setConn(&this->connector);
    this->inter.setController(&this->controller);
}


void Application::run()
{
    this->inter.runPolling();
}
