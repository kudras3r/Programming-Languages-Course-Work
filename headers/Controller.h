//
// Created by kud on 11.05.24.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "DBConnector.h"


class Controller
{

    /*
     * makes requests to db with DBconn help.
     * takes enquiries from Interface.
     * storage data and manages the cache.
     */

    public:
        Controller();
        void setConn (  // look at Application constructor
            DBConnector* conn
        );  


        std::vector<Student> getSortedGroupBySems (
            const unsigned g_id,
            const std::vector<unsigned> sems
        );


        std::vector<Record>* getAll (
            std::string items_name
        );
        std::vector<Record>* getStudentsByGroupId (
            const unsigned id
        );
        Record getById (
            std::string item_name,
            const unsigned id
        );

        bool createNewGroup (
            const std::string group_name
        );    
        bool createNewStudent (
            Student s, 
            const unsigned group_id
        );

        bool updateGroup (
            Group g
        );
        bool updateStudent (
            Student s
        );

        unsigned getGroupsCount();

        void shakerSort (
            std::vector<Student>& students,
            std::vector<double>& marks
        );
        // std::vector<Record> data;

    private:
        DBConnector* conn;
        std::vector<Record> data;

};

#endif //CONTROLLER_H
