#ifndef PAGEBUILDER_H
#define PAGEBUILDER_H

#include "Page.h"
#include "Controller.h"
#include "Record.h"

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
    void setStudentsPage(
        std::vector<Record>* data
    );

    void setGroupPage(
        const Group* g,
        std::vector<Record>* data
    );
    void setStudentPage(
        Record* rec
    );

    void setGroupCreatingPage();
    void setStudentCreatingPage();

    void setGroupEditPage();
    void setStudentEditPage();

    void setResponsePage(
        bool all_is_good
    );
};

#endif //PAGEBUILDER_H