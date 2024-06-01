#ifndef PAGEBUILDER_H
#define PAGEBUILDER_H

#include "/home/kud/Projects/ProgLanCoursework/headers/Page.h"
#include "/home/kud/Projects/ProgLanCoursework/headers/Controller.h"
#include "/home/kud/Projects/ProgLanCoursework/headers/Libs.h"
#include "/home/kud/Projects/ProgLanCoursework/headers/Record.h"

class PageBuilder
{
    public:
        Page cur_page;

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
        void setStudentCreatingPage();
        void setResponsePage (
            bool all_is_good 
        );
};

#endif //PAGEBUILDER_H
