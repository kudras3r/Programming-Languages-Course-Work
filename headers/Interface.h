#ifndef INTERFACE_H
#define INTERFACE_H


#include "/home/kud/Projects/ProgLanCoursework/headers/Libs.h"

#include "/home/kud/Projects/ProgLanCoursework/headers/Controller.h"
#include "/home/kud/Projects/ProgLanCoursework/headers/Page.h"
#include "/home/kud/Projects/ProgLanCoursework/headers/PageBuilder.h"


class Interface : public PageBuilder
{

    /* draw the interface:
     * for drawing use frame variable looks like (go to Page.h):
     *      title : str
     *      head : vector[str, str...]        message to user
     *      meta : vector[str, str...]        some data
     *      invite : vector[str, str...]      invite user (display commands)
     *
     * connect with controller for data exchange.
     */

public:
    // using PageBuilder::PageBuilder;
    Interface();
    void setController (  // look at Application constructor
        Controller* conn
    );  

    void runPolling();  // wait user input in while(true) cycle


private:
    Controller* controller;

    std::stack<std::string> path;

    std::vector<Record>* buffer;

    short line_size;

    // Page cur_page;

    void update();  // update frame
    void render();  // draw frame

    // void setHomePage();
    // void setByePage();
    // void setGroupsPage();
    // void setGroupPage (
    //     const unsigned id
    // );
    // void setStudentsPage();
    // void setStudentPage (
    //     const unsigned id
    // );
    // void setGroupCreatingPage();

    void drawLine(char c) const;

    bool isId (
        const std::string command
    );  // check user command is id

    bool isNumber (
        const std::string s
    );

};

#endif //INTERFACE_H
