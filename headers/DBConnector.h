#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H


#include "Record.h"


class DBConnector
{

    /*
        works with files.
        responsible for encryption.
     
        emulated a relational db model:
        in 'storage' directory stored 'tables' like student or group..
        to work with tables connector uses standart read\write file streams.
     */

    public:
        DBConnector();

        unsigned groups_count;  
        unsigned students_count;

        void insertInto (
            const std::string table_name, 
            const Record rec
        );

        Record selectFromById ( 
            const std::string table_name, 
            const unsigned id
        );

        void save (
            Record r
        );

    private:
        std::ofstream write_stream;
        std::ifstream read_stream;

        std::queue<Record> update_q;  // queue with records to update tables

        std::map<std::string, std::string> path_to_table;  // 

        std::string recToString (
            Record rec
        );

        std::map<unsigned, Record> parseTable (
            std::string table
        );

        void updateTables();
        
};

#endif //DBCONNECTOR_H
