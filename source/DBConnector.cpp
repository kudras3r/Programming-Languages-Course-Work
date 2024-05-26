#include "/home/kud/Projects/ProgLanCoursework/headers/DBConnector.h"


DBConnector::DBConnector()
{
    this->path_to_table["group"] = "/home/kud/Projects/ProgLanCoursework/storage/group.txt";
    this->path_to_table["student"] = "/home/kud/Projects/ProgLanCoursework/storage/student.txt";

    this->groups_count = 0;
    this->students_count = 0;

    // get groups count
    std::string tmp;
    this->read_stream.open(this->path_to_table["group"]);
    while ( std::getline(this->read_stream, tmp) )
        this->groups_count++;
    this->read_stream.close();

    // get students count
    this->read_stream.open(this->path_to_table["student"]);
    while( std::getline(this->read_stream, tmp) )
        this->students_count++;
    this->read_stream.close();
}


void DBConnector::insertInto(const std::string table_name, const Record rec)
{
    if (table_name == "group")
    {
        this->write_stream.open(this->path_to_table["group"], std::ios_base::app);
        Group g = rec.group_data;
        this->write_stream << g.id 
            << " " << g.members_count << " " << g.name << " |" << std::endl;
        this->write_stream.close();

        this->groups_count++;
    }
    else if (table_name == "student")
    {
        this->write_stream.open(this->path_to_table["student"], std::ios_base::app);
        Student s = rec.student_data;
        this->write_stream << s.id << " " << s.group_id << " " << s.first_name 
            << " " << s.middle_name << " " << s.last_name << " " << s.date_of_birth.day 
            << " " << s.date_of_birth.month << " " << s.date_of_birth.year << " " << s.sex
            << " " << s.date_of_receipt.day << " " << s.date_of_receipt.month << " " << s.date_of_receipt.year 
            << " " << s.departament << " " << s.pulpit << " |" << std::endl;
        this->write_stream.close();


        Group g = this->selectFromById("group", s.group_id).group_data;
        g.members_count++;
        
        Record rec;
        rec.type = 'g';
        rec.group_data = g;

        this->update_q.push(rec);
        
        this->updateTables();

        this->students_count++;
    }
}


Record DBConnector::selectFromById(const std::string table_name, const unsigned id)
{
    std::map<unsigned, Record> table_data;
    Record rec;

    table_data = this->parseTable(table_name);
    
    return table_data[id];
}


std::string DBConnector::recToString(Record rec, std::string rec_type)
{
    std::string line;

    if (rec_type == "group")
    {
        line.append(std::to_string(rec.group_data.id));
        line.append(" ");
        line.append(std::to_string(rec.group_data.members_count));
        line.append(" ");
        line.append(rec.group_data.name);
        line.append(" |");
        line.append("\n");
    }

    return line;
}


std::map<unsigned, Record> DBConnector::parseTable(std::string table) 
{
    /*
    * return table data :
    * {
    *   id : Record
    *   ...
    * }
    */


    Record rec;
    std::map<unsigned, Record> table_data;

    std::string line;
    std::string delimiter = " ";

    if (table == "group")
    {
        Group g;

        this->read_stream.open(this->path_to_table["group"]);

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
    }

    else if (table == "student")
    {
        Student s;

        this->read_stream.open(this->path_to_table["student"]);

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
                
                s.date_of_birth = d_o_b;
                s.date_of_receipt = d_o_r;
                
                rec.student_data = s;
                table_data[s.id] = rec;
            }
        }   
    }

    this->read_stream.close();
    
    return table_data;
}


void DBConnector::updateTables()
{
    while (!this->update_q.empty())
    {
        Record rec = this->update_q.front();
        this->update_q.pop();

        if (rec.type == 'g')
        {
            Group g = rec.group_data;
            unsigned group_id = g.id;

            std::map<unsigned, Record> table_data = this->parseTable("group");
            
            table_data[group_id] = rec;

            this->write_stream.open(this->path_to_table["group"]);
            for (unsigned group_id = 1; group_id <= this->groups_count; group_id++)
            {   
                std::string line = this->recToString(table_data[group_id], "group");
                this->write_stream << line;
            }
            this->write_stream.close();
        }
    }
}
