#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include "Libs.h"

#include "Record.h"


class DBConnector
{

    /*
     * works with files.
     * responsible for encryption.
     */

    public:
        DBConnector();

        unsigned groups_count;
        unsigned students_count;

        void insertInto(const std::string& table_name, const Record& rec);
        Record selectFromById(const std::string& table_name, const unsigned id);

    private:
        std::ofstream write_stream;
        std::ifstream read_stream;



};

#endif //DBCONNECTOR_H
