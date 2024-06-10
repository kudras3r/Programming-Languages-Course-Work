#include "../headers/PageBuilder.h"


void PageBuilder::setHomePage()
{
    this->cur_page.title = "HOME";
    this->cur_page.head = {
        "           ▄█▌ ▄ ▄ ▐█▄",
        "           ██▌▀▀▄▀▀▐██",
        "           ██▌─▄▄▄─▐██",
        "           ▀██▌▐█▌▐██▀",
        "        ▄██████ ▀ ██████▄",
        "",
        "Hello!",
        "You have launched the StudentsDB.",
        "Created by kudras3r.",
        "Enjoy your study management."
    };
    this->cur_page.meta = {
        "kekw)"
    };
    this->cur_page.invite = {
        "commands : ",
        "help | exit | groups | students"
    };
}


void PageBuilder::setHelpPage()
{
    this->cur_page.title = "HELP";
    this->cur_page.head = {
        "StudentsDB is a project,",
        "designed to simplify the management",
        "of student data",
    };
    this->cur_page.meta = {
        "Main information to application using:",
        "Application works with you with commands",
        "All commands that you have access now",
        "storage in the bottom of page.",
        ""
        "You have access to three main partitions:",
        "students | groups | grades",
        "",
        "STUDENTS:",
        "In this section you can:",
        "create | edit | delete students",
        "",
        "Student model:",
        "---",
        "private ID",
        "private GROUP_ID",
        "public FIRST | M | L NAMES",
        "public DATEOFBIRTH",
        "public SEX",
        "public DATEOFRECEIPT",
        "public DEPARTAMENT",
        "public PULPIT",
        "public GRADEBOOK",
        "",
        "To CREATE the student go to the group",
        "to which the student belongs,",
        "type 'create' and follow the instructions.",
        "",
        "To EDIT student info go to this student,",
        "you can do this by two ways :",
        "from group | from students page.",
        "Here you can type 'edit' and change the student info.",
        "",
        "To DELETE student go to his page and run delete command."
        "",
        "All of this knowlages you can use in groups and grades partions."
    
    };
    this->cur_page.invite = {
        "back | exit | help",
        "students | groups"
    };
}


void PageBuilder::setByePage()
{
    this->cur_page.title = "Have a good time!";
    this->cur_page.head = { 

        "      █  ██████    ██████  █",
        "      █ ██    ██  ██    ██ █",
        "       ███ ██ ██████ ██ ███",
        "        ██    ██  ██    ██",
        "         ██████    ██████",
        
        "",
        "Bye!" 
    };
    this->cur_page.meta = { "Thanks for your attention!" };
    this->cur_page.invite = { "See you later :)" };
}


void PageBuilder::setGroupsPage(std::vector<Record>* data)
{
    this->cur_page.title = "GROUPS";
    this->cur_page.head = { "Your groups:" };
    this->cur_page.meta.clear();

    std::string line;
    for (auto& rec : *data)
    {
        line = std::to_string(rec.group_data.id);
        line.append(") ");
        line.append(rec.group_data.name);

        this->cur_page.meta.push_back(line);
    }

    this->cur_page.invite = {
        "back | exit | help",
        "create | delete | {id}",
        "students"
    };
}


void PageBuilder::setGroupPage(const Group* g, std::vector<Record>* data)
{
    std::string line;
    line = "STUDENTS ( ";
    line.append(g->name);
    line.append(" )");

    this->cur_page.title = line;
    this->cur_page.head = {
        "Members count:",
        std::to_string(g->members_count),
        "id | f name | s name"
    };

    this->cur_page.meta.clear();
    if (data->size()) 
    {
        for (auto& rec : *data)
        {
            line = std::to_string(rec.student_data.id);
            line.append(") ");
            line.append(rec.student_data.first_name);
            line.append(" ");
            line.append(rec.student_data.middle_name);

            this->cur_page.meta.push_back(line);
        }
    }  
    else this->cur_page.meta = { 
        "You have not students" 
    };
    
    this->cur_page.invite = {
        "back | exit | help",
        "create | delete | edit | {id}",
        "students | groups",
        "",
        "(individual task) sort"
    };
}


void PageBuilder::setSortedGroupPage(std::vector<Student>* students, std::vector<unsigned>* sems)
{
    this->cur_page.title = "SORTED GROUP (var 82)";

    std::string line = "Sorted by ";
    for (const unsigned& s : *sems) 
    {
        line.append(std::to_string(s));
        line.append(" ");
    }
    line.append("semesters");
    this->cur_page.head = {
        line
    };
    this->cur_page.meta.clear();

    for (Student& s : *students)
    {
        line = std::to_string(s.id);
        line.append(") ");
        line.append(s.first_name);
        line.append(" ");
        line.append(s.middle_name);
        line.append(" <");
        line.append(s.date_of_birth.likeStr());
        line.append("> ");

        this->cur_page.meta.push_back(line);    
    }

    this->cur_page.invite = {
        "help | back | exit",
        "groups | students"
    };
}


void PageBuilder::setStudentsPage(std::vector<Record>* data)
{
    this->cur_page.title = "STUDENTS";
    this->cur_page.head = { "All students:" };
    this->cur_page.meta.clear();
    std::string line;
    for (auto& rec : *data)
    {
        line = std::to_string(rec.student_data.id);
        line.append(") ");
        line.append(rec.student_data.first_name);
        line.append(" ");
        line.append(rec.student_data.middle_name);
        line.append(" <");
        line.append(rec.student_data.pulpit);
        line.append(" : ");
        line.append(rec.group_data.name);
        line.append(">");

        this->cur_page.meta.push_back(line);
    }

    this->cur_page.invite = {
        "back | exit | help",
        "delete | edit | grades",
        "groups"
    };
}


void PageBuilder::setStudentPage(Record* rec)
{
    std::string line;
    Student s = rec->student_data;

    line = "STUDENT <";
    line.append(rec->group_data.name);
    line.append(">");

    this->cur_page.title = line;

    line = s.first_name;
    line.append(" ");
    line.append(s.middle_name);
    line.append(" ");
    line.append(s.last_name);

    this->cur_page.head = {
        "           ▄██████▄",
        "          ▐▀▀▀▀▀▀▀▀▌",
        "          ▌▌▀▀▌▐▀▀▐▐",
        "          ▐  ▄▄▄▄  ▌",
        "           ▌▐▌──▐▌▐",
        "",
        line
    };
    this->cur_page.meta.clear();
    
    line = "Date of birth: ";
    line.append(s.date_of_birth.likeStr());
    this->cur_page.meta.push_back(line);
    
    line = "Date of receipt: ";
    line.append(s.date_of_receipt.likeStr());
    this->cur_page.meta.push_back(line);

    line = "Sex: ";
    if (s.sex) line.append("male");
    else line.append("female");
    this->cur_page.meta.push_back(line);

    line = "Departament: ";
    line.append(s.departament);
    this->cur_page.meta.push_back(line);

    line = "Pulpit: ";
    line.append(s.pulpit);
    this->cur_page.meta.push_back(line); 

    line = "Grade book: ";
    line.append(s.grade_book);
    this->cur_page.meta.push_back(line);

    this->cur_page.invite = {
        "back | exit | help",
        "delete | edit | grades",
        "groups | students"
    };
}


void PageBuilder::setGroupCreatingPage()
{
    this->cur_page.title = "GROUP CREATE";
    this->cur_page.head = { 
        "So, lets create a new group" 
    };
    this->cur_page.meta = {
        "Please enter the:"
    };
    this->cur_page.invite = {
        "{group name}"
    };
}


void PageBuilder::setStudentCreatingPage()
{
    this->cur_page.title = "CREATE NEW STUDENT";
    this->cur_page.head = {
        "Lets create a new student."
    };
    this->cur_page.meta = {
        "Please enter the :"
    };
    this->cur_page.invite = {
        "L - letter; N - number",
        "",
        "FMLnames> {first} {middle} {last}",
        "DMYofBirth> {day} {month} {year}",
        "DMYofReceipt> {day} {month} {year}",
        "Sex> {1} - male or {0} - female",
        "Departament> {departament} without spaces",
        "Pulpit> {pulpit} fe : LL-N",
        "GBook> {GB number} like : NNLNNNN"

    };
}


void PageBuilder::setGroupEditPage()
{
    this->cur_page.title = "GROUP EDIT";
    this->cur_page.head = {
        "Lets edit the group."
    };
    this->cur_page.meta = {
        "Please enter new group name: "
    };
    this->cur_page.invite = {
        "NewName> {group name}"
    };
}


void PageBuilder::setStudentEditPage()
{
    this->cur_page.title = "STUDENT EDIT";
    this->cur_page.head = {
        "Lets edit the student."
    };
    this->cur_page.meta = {
        "Please choose the field to edit: "
    };
    this->cur_page.invite = {
        "L - letter; N - number",
        "",
        "-name> {name}",
        "DMYofBirth> {day} {month} {year}",
        "DMYofReceipt> {day} {month} {year}",
        "Sex> {1} - male or {0} - female",
        "Departament> {departament} without spaces",
        "Pulpit> {pulpit} fe : LL-N",
        "GBook> {GB number} like : NNLNNNN"
        "",
        "{0} - exit",
        "{1} - f name",
        "{2} - m name",
        "{3} - l name",
        "{4} - date of birth",
        "{5} - sex",
        "{6} - date of receipt",
        "{7} - departament",
        "{8} - pulpit",
        "{9} - grade book"
    };
}


void PageBuilder::setStudentDeletePage()
{
    this->cur_page.title = "STUDENT DELETE";
    this->cur_page.head = { "Delete student John Doe." };
    this->cur_page.meta = { "Student were succefuly deleted!" };
    this->cur_page.invite = { 
        "back | help | exit",
        "students | groups"
    };
}


void PageBuilder::setGradesPage(GBook* book, Student* s)
{
    std::string line = "GRADES < ";
    line.append(s->first_name);
    line.append(" ");
    line.append(s->middle_name);
    line.append(" >");

    this->cur_page.title = line;
    this->cur_page.meta.clear();

    std::vector<unsigned> sems;

    for (const auto& p1 : book->grades)
    {
        sems.push_back(p1.first);
    }

    for (const unsigned& sem : sems)
    {
        std::vector<std::string> subjects;
        line = "Semester ";
        line.append(std::to_string(sem));

        this->cur_page.meta.push_back(line);

        for (const auto& p2 : book->grades[sem])
        {
            subjects.push_back(p2.first);
        }

        for (const std::string& sub : subjects)
        {
            line = "\t";
            line.append(sub);
            line.append(" marks : ");

            for (int i = 0; i < book->grades[sem][sub].size(); i++)
            {
                if (i != book->grades[sem][sub].size() - 1)
                {
                    line.append(std::to_string(book->grades[sem][sub][i]));
                    line.append(", ");
                }
                else line.append(std::to_string(book->grades[sem][sub][i]));
            }

            this->cur_page.meta.push_back(line);
        } 

        this->cur_page.meta.push_back("");
    }

    this->cur_page.invite = {
        "back | exit | help",
        "add | delete"
    };
}


void PageBuilder::setResponsePage(bool all_is_good)
{
    if (all_is_good)
    {
        this->cur_page.head = { "Nice!" };
        this->cur_page.meta = { "Everything is fine!" };
        this->cur_page.invite = {
            "back | exit | help"
        };
    }
    else
    {
        this->cur_page.head = { "Something went wrong.." };
        this->cur_page.meta = { "Check the entered data!" };
        this->cur_page.invite = {
            "back | exit | help"
        };
    }
}
