//
// Created by kud on 11.05.24.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "/home/kud/Projects/ProgLanCoursework/headers/Libs.h"

#include "/home/kud/Projects/ProgLanCoursework/headers/DBConnector.h"


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
        
        std::vector<Record> data;

    private:
        DBConnector* conn;

        // std::vector<Record> data;

        std::vector<Record> groups_data;
        std::vector<Record> students_data;

        bool validateName (
            const std::string table, 
            const std::string name
        );

};

#endif //CONTROLLER_H
