#ifndef PAGEBUILDER_H
#define PAGEBUILDER_H

#include "/home/kud/Projects/ProgLanCoursework/headers/Page.h"
#include "/home/kud/Projects/ProgLanCoursework/headers/Controller.h"
#include "/home/kud/Projects/ProgLanCoursework/headers/Libs.h"
#include "/home/kud/Projects/ProgLanCoursework/headers/Record.h"

class PageBuilder
{
    public:
        // Controller* controller;
        
        // std::vector<Record>* buffer;

        Page cur_page;

        // void setController (  // look at Application constructor
            // Controller* conn
        // );  

        void setHomePage();
        void setHelpPage();
        void setByePage();
        void setGroupsPage(
            std::vector<Record>* data
        );
        void setGroupPage (
            const Group* g,
            std::vector<Record>* data
        );
        void setStudentsPage (
            std::vector<Record>* data
        );
        void setStudentPage (
            Record* rec
        );
        void setGroupCreatingPage();

        void setResponsePage (
            bool all_is_good 
        );
};

#endif //PAGEBUILDER_H
