#include "../headers/Controller.h"

#include "../headers/models/Student.h"


Controller::Controller()
{

}

void Controller::setConn(DBConnector *conn)
{
    this->conn = conn;
}

std::vector<Record>* Controller::getAllGroups()
{
    unsigned groups_count = this->conn->groups_count;
    std::vector<Record> data;
    unsigned id = 1;

    Record tmp;

    while (id <= groups_count)
    {
        tmp = this->conn->selectFromById("group", id);
        data.push_back(tmp);

        id++;
    }

    this->groups_data = data;
    return &this->groups_data;
}

std::vector<Record>* Controller::getStudentsByGroupId(const unsigned& id)
{
    unsigned groups_count = this->conn->groups_count;
    unsigned students_count = this->conn->students_count;
    unsigned student_id = 1;

    Record tmp;
    std::vector<Record> data;

    if (id <= groups_count)
    {

        while (student_id <= students_count)
        {
            tmp = this->conn->selectFromById("student", student_id);
            Student s = tmp.student_data;

            if (s.group_id == id) data.push_back(tmp);

            student_id++;
        }

    }
    else data.clear();

    this->students_data = data;
    return &this->students_data;
}

Group Controller::getGroupById(const unsigned &id)
{
    Record rec = this->conn->selectFromById("group", id);
    Group g = rec.group_data;

    return g;
}


bool Controller::createNewGroup(const std::string& group_name)
{
    if (this->validateName("groups", group_name))
    {
        Group g;
        g.name = group_name;
        g.members_count = 0;
        g.id = this->conn->groups_count + 1;

        Record rec;
        rec.group_data = g;

        this->conn->insertInto("group", rec);

        return true;
    }
    else
    {
        return false;
    }
}


bool Controller::validateName(const std::string& table, const std::string& name)
{
    // TODO Cyrillik letters !! (maybe uppercase)
    if (table == "groups")
    {
        if (
            // check that name looks like LLLL-NN-NN (L-letter; N-number)
            std::isalpha(name[0]) && std::isalpha(name[1]) && std::isalpha(name[2]) &&
                std::isalpha(name[3]) &&
            name[4] == '-' && name[7] == '-' &&
            std::isdigit(name[5]) && std::isdigit(name[6]) && std::isdigit(name[8]) && std::isdigit(name[9])
        ) return true;

        return false;

    }
    return false;
}

