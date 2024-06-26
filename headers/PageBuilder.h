#ifndef PAGEBUILDER_H
#define PAGEBUILDER_H

#include "Page.h"
#include "Controller.h"
#include "Record.h"
#include "models/GBook.h"
#include "models/Student.h"


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
        void setStudentsPage (
            std::vector<Record>* data
        );

        void setSortedGroupPage (
            std::vector<Student>* data,
            std::vector<unsigned>* sems
        );

        void setGroupPage (
            const Group* g,
            std::vector<Record>* data
        );
        void setStudentPage (
            Record* rec
        );

        void setGroupCreatingPage();
        void setStudentCreatingPage();

        void setGroupEditPage();
        void setStudentEditPage();

        void setStudentDeletePage();

        void setGradesPage (
            GBook* book,
            Student* s
        );

        void setResponsePage (
            bool all_is_good 
        );
};

#endif //PAGEBUILDER_H
