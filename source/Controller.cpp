#include "../headers/Controller.h"
#include "../headers/models/Student.h"
#include "../headers/models/GBook.h"


Controller::Controller()
{
}

void Controller::setConn(DBConnector *conn)
{
    this->conn = conn;
}


std::vector<Student> Controller::getSortedGroupBySems(const unsigned g_id, const std::vector<unsigned> sems)
{
    std::vector<Record>* recs = this->getStudentsByGroupId(g_id);

    std::vector<Student> students;
    std::vector<double> grades;

    for (const auto rec : *recs) students.push_back(rec.student_data);
    
    for (const Student s : students)
    {
        GBook s_book = this->getById("grades", s.id).grades_data;
        grades.push_back(s_book.calculateAvgMarkForSems(sems));
    }

    this->shakerSort(students, grades);
    
    return students;
}


std::vector<Record>* Controller::getAll(std::string items_name)
{
    unsigned count;
    std::string table_name;
    if (items_name == "groups") 
    {
        table_name = "group";
        count = this->conn->groups_count;
    }
    else 
    {
        table_name = "student";
        count = this->conn->students_count;
    }
    std::vector<Record> data;
    unsigned id = 1;

    Record tmp;
    while (id <= count)
    {
        tmp = this->conn->selectFromById(table_name, id);
        if (table_name == "student")
        {
            Group g = this->conn->selectFromById("group", tmp.student_data.group_id).group_data;
            tmp.group_data = g;
        }
        data.push_back(tmp);

        id++;
    }

    this->data = data;
    return &(this->data);
}

std::vector<Record>* Controller::getStudentsByGroupId(const unsigned id)
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
            
            if (s.group_id == id) {
                
                data.push_back(tmp);
            }

            student_id++;
        }
    }
    else data.clear();

    this->data = data;
    return &this->data;
}


Record Controller::getById(std::string item_name, const unsigned id)
{
    Record rec = this->conn->selectFromById(item_name, id);
    if (item_name == "student")
    {
        Group g = this->conn->selectFromById("group", rec.student_data.group_id).group_data;
        rec.group_data = g;
    }
    return rec;
}


bool Controller::createNewGroup(const std::string group_name)
{
    Group g;
    g.name = group_name;

    if (g.nameIsValid())
    {
        g.members_count = 0;
        g.id = this->conn->groups_count + 1;

        Record rec;
        rec.group_data = g;

        this->conn->insertInto("group", rec);

        return true;
    }   
    return false;
}

bool Controller::createNewStudent(Student s, const unsigned group_id)
{
    if (s.date_of_birth.isValid() && s.date_of_receipt.isValid() 
        && s.namesIsValid()
        && s.pulIsValid()
        && s.GBookIsValid())
    {
        Group g = this->getById("group", group_id).group_data;
        unsigned s_count = this->conn->students_count;
        s.id = ++s_count;

        Record rec;
        rec.student_data = s;

        this->conn->insertInto("student", rec);

        return true;
    }
    else 
    {
        return false;
    }
}


bool Controller::updateGroup(Group g)
{
    // TODO ! validate g name in g model
    if (g.nameIsValid())
    {
        Record rec;
        rec.group_data = g;
        rec.type = 'g';
        
        this->conn->save(rec);

        return true;
    }
    return false;
}


bool Controller::updateStudent(Student s)
{   
    if (s.date_of_birth.isValid() && s.date_of_receipt.isValid() 
        && s.namesIsValid()
        && s.pulIsValid()
        && s.GBookIsValid())
    {
        Record rec;
        rec.student_data = s;
        rec.type = 's';

        this->conn->save(rec);
        return true;
    }
    return false;
}


unsigned Controller::getGroupsCount() { return this->conn->groups_count; }


void Controller::shakerSort(std::vector<Student>& students, std::vector<double>& marks)
{
    bool swapped = true;
    int start = 0;
    int end = marks.size() - 1;

    while (swapped)
    {
        swapped = false;

        for (int i = start; i < end; i++)
        {
            if (marks[i] < marks[i + 1])
            {
                std::swap(marks[i], marks[i + 1]);
                std::swap(students[i], students[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;

        --end;

        swapped = false;

        for (int i = end; i > start; i--)
        {
            if (marks[i] > marks[i - 1])
            {
                std::swap(marks[i], marks[i - 1]);
                std::swap(students[i], students[i - 1]);
                swapped = true;
            }
        }
    }
}