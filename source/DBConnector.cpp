#include "../headers/DBConnector.h"

// TODO

DBConnector::DBConnector()
{
    this->groups_count = 0;
    this->students_count = 0;

    // get groups count
    std::string tmp;
    this->read_stream.open("../Storage/group.txt");
    while ( std::getline(this->read_stream, tmp) )
        this->groups_count++;
    this->read_stream.close();

    // get students count
    this->read_stream.open("../Storage/student.txt");
    while( std::getline(this->read_stream, tmp) )
        this->students_count++;
    this->read_stream.close();
}




void DBConnector::insertInto(const std::string &table_name, const Record &rec)
{

    if (table_name == "group")
    {
        this->write_stream.open("../Storage/group.txt", std::ios_base::app);
        this->write_stream << rec.group_data.id << " "
            << rec.group_data.members_count << " " << rec.group_data.name << " |" << std::endl;
        this->write_stream.close();

        this->groups_count++;
    }

}


Record DBConnector::selectFromById(const std::string &table_name, const unsigned id)
{
    /*
     * to takin something by id we need to return Record type,
     * cauze user can try to get group such like student,
     * but there is different models.
     *
     * map<int, Record> - structure to temporary storage of table data and fast searching by id.
     * if user want ot get group, method will create Group g variable and put it to Record.group_data
     * etc with another models..
     *
     * to parse model method:
     * 1 gets line from file.
     * 2 split line by 'space' separator into tokens.
     * 3 convert str id to int.
     * 4 put all data in model(Group / Student...) variable.
     *
     * after this model variable puts into Record.{model_data} and returns to controller
     */

    std::map<int, Record> table_data;
    Record rec;

    std::string line;
    std::string delimiter = " ";

    if (table_name == "group")
    {
        Group g;

        this->read_stream.open("../Storage/group.txt");

        if (read_stream.is_open())
        {
            while (getline(read_stream, line))
            {
                size_t pos = 0;
                std::string token;
                unsigned short token_count = 0;  // positional pointer to model field: 0 for Group - id...

                // spliting lines
                while ((pos = line.find(delimiter)) != std::string::npos)
                {
                    token = line.substr(0, pos);

                    if (token_count == 0) g.id = std::stoi(token);

                    else if (token_count == 1) g.members_count = std::stoi(token);

                    else g.name = token;

                    token_count++;
                    line.erase(0, pos + delimiter.length());
                }
                rec.group_data = g;
                table_data[g.id] = rec;
            }
        }

        this->read_stream.close();

        return table_data[id];
    }

    else if (table_name == "student")
    {
        Student s;

        this->read_stream.open("../Storage/student.txt");

        if (read_stream.is_open())
        {
            while (getline(read_stream, line))
            {
                size_t pos = 0;
                std::string token;
                unsigned short token_count = 0;

                Date d_o_b;
                Date d_o_r;

                while ((pos = line.find(delimiter)) != std::string::npos)
                {
                    token = line.substr(0, pos);

                    if (token_count == 0) s.id = std::stoi(token);

                    else if (token_count == 1) s.group_id = std::stoi(token);

                    else if (token_count == 2) s.first_name = token;

                    else if (token_count == 3) s.middle_name = token;

                    else if (token_count == 4) s.last_name = token;

                    else if (token_count == 5) d_o_b.day = std::stoi(token);

                    else if (token_count == 6) d_o_b.month = std::stoi(token);

                    else if (token_count == 7) d_o_b.year = std::stoi(token);

                    else if (token_count == 8) s.sex = std::stoi(token);

                    else if (token_count == 9) d_o_r.day = std::stoi(token);

                    else if (token_count == 10) d_o_r.month = std::stoi(token);

                    else if (token_count == 11) d_o_r.year = std::stoi(token);

                    else if (token_count == 12) s.departament = token;

                    else s.pulpit = token;

                    token_count++;

                    line.erase(0, pos + delimiter.length());
                }
                rec.student_data = s;
                table_data[s.id] = rec;
            }
        }

        this->read_stream.close();

        return table_data[id];
    }
}

