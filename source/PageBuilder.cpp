#include "/home/kud/Projects/ProgLanCoursework/headers/PageBuilder.h"


void PageBuilder::setHomePage()
{
    this->cur_page.title = "HOME";
    this->cur_page.head = {
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


void PageBuilder::setByePage()
{
    this->cur_page.title = "Okey..";
    this->cur_page.head = { "Bye!" };
    this->cur_page.meta = { "))" };
    this->cur_page.invite = { "see u later" };
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
        "create | delete | {id}"
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
    else this->cur_page.meta = { "You have not students" };
    
    this->cur_page.invite = {
        "back | exit | help",
        "create | delete | {id}"
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
        "delete | {id}"
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
}

// TODO!

// void PageBuilder::setGroupCreatingPage()
// {
//     Group new_group;
//     std::string group_name;

//     this->cur_page.title = "GROUP CREATE";
//     this->cur_page.head = { "So, lets create a new group" };
//     this->cur_page.meta = {
//         "Please enter the:"
//     };
//     this->cur_page.invite = {
//         "{group name}"
//     };

//     // this->render();

//     std::cout << "name> ";
//     std::cin >> group_name;

//     bool ok_status_code = this->controller->createNewGroup(group_name);

//     if (ok_status_code)
//     {
//         this->cur_page.head = { "Nice!" };
//         this->cur_page.meta = { "New group was created!" };
//         this->cur_page.invite = {
//             "groups | exit | help"
//         };
//     }
//     else
//     {
//         this->cur_page.head = { "Something went wrong.." };
//         this->cur_page.meta = { "Name is invalid!" };
//         this->cur_page.invite = {
//             "back | exit | help"
//         };
//     }
// }