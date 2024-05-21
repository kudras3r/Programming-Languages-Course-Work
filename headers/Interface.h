// #ifndef INTERFACE_H
// #define INTERFACE_H
//
//
// #include "Libs.h"
//
// #include "Controller.h"
// #include "Page.h"
//
//
// class Interface
// {
//
//     /* draw the interface:
//      * for drawing use frame variable looks like (go to Page.h):
//      *      title : string
//      *      head : vector[str, str...]        message to user
//      *      meta : vector[str, str...]        some data
//      *      invite : vector[str, str...]      invite user (display commands)
//      *
//      * connect with controller for data exchange.
//      */
//
//     public:
//         Interface();
//         void setController(Controller* conn);
//
//         void runPolling();  // wait user input in while(true) cycle
//
//
//     private:
//         Controller* controller;
//
//         // std::string partition;  // maybe groups, grader, students or help
//         unsigned cur_group_id;
//         std::stack<std::string> path;
//
//         std::vector<Record>* groups;
//         std::vector<Record>* students;
//
//         short line_size;
//
//         Page cur_page, last_page;
//
//         void update(const std::string& command);  // update frame
//         void render();  // draw frame
//
//         void drawLine() const;
//         bool isId(const std::string& command);  // check user command is id
//
// };
//
//
// #endif //INTERFACE_H

#ifndef INTERFACE_H
#define INTERFACE_H


#include "Libs.h"

#include "Controller.h"
#include "Page.h"


class Interface
{

    /* draw the interface:
     * for drawing use frame variable looks like (go to Page.h):
     *      title : string
     *      head : vector[str, str...]        message to user
     *      meta : vector[str, str...]        some data
     *      invite : vector[str, str...]      invite user (display commands)
     *
     * connect with controller for data exchange.
     */

public:
    Interface();
    void setController(Controller* conn);

    void runPolling();  // wait user input in while(true) cycle


private:
    Controller* controller;

    // std::string partition;  // maybe groups, grader, students or help
    std::stack<std::string> path;

    std::vector<Record>* groups;
    std::vector<Record>* students;
    std::vector<Record>* buffer;

    short line_size;

    Page cur_page, last_page;



    void update(const std::string& command);  // update frame
    void render();  // draw frame

    void drawLine() const;
    bool isId(const std::string& command);  // check user command is id

};


#endif //INTERFACE_H
