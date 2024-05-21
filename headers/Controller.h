//
// Created by kud on 11.05.24.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Libs.h"

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
        void setConn(DBConnector* conn);  // look at Application constructor

        std::vector<Record>* getAllGroups();
        std::vector<Record>* getStudentsByGroupId(const unsigned& id);
        Group getGroupById(const unsigned& id);

        bool createNewGroup(const std::string& group_name);

    private:
        DBConnector* conn;

        std::vector<Record> groups_data;
        std::vector<Record> students_data;

        bool validateName(const std::string& table, const std::string& name);

};

#endif //CONTROLLER_H
