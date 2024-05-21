// #include "../headers/Libs.h"
// #include "../headers/Interface.h"
// #include "../headers/Page.h"
// #include "../headers/models/Student.h"
//
//
// Interface::Interface() {
//
//     this->line_size = 50;
//
//     // creating first page
//     this->cur_page.title = "HOME";
//     this->cur_page.head = {
//         "Hello!",
//         "You have launched the StudentsDB.",
//         "Created by kudras3r.",
//         "Enjoy your study management."
//     };
//     this->cur_page.meta = {
//         "kekw)"
//     };
//     this->cur_page.invite = {
//         "commands : ",
//         "help | exit | groups | students"
//     };
//
//     // set this page like last for 'back' command
//     this->last_page = this->cur_page;
//
// }
//
//
// void Interface::setController(Controller *conn)
// {
//     this->controller = conn;
// }
//
//
// void Interface::runPolling()
// {
//
//     std::string command;
//     this->render();
//
//     while (true)
//     {
//         std::cout << "let> ";
//         std::cin >> command;
//         this->update(command);
//         this->render();
//     }
//
// }
//
//
// void Interface::update(const std::string& command)
// {
//     /* event cases */
//
//     // support
//     if (command == "exit")
//     {
//
//         this->cur_page.title = "Okey..";
//         this->cur_page.head = { "Bye!" };
//         this->cur_page.meta = { "))" };
//         this->cur_page.invite = { "See u later" };
//
//         this->render();
//
//         exit(0);
//
//     }
//
//     else if (command == "help")
//     {
//
//         // this->partition = "help";
//         this->path.push("help");
//
//         this->last_page = this->cur_page;
//
//         this->cur_page.title = "HELP";
//         this->cur_page.head = { "Help for u:" };
//         this->cur_page.meta = { "Some help" };
//         this->cur_page.invite = {
//             "commands:",
//             "back | exit"
//         };
//
//     }
//
//     else if (command == "back")
//     {
//         std::string partition = this->path.top();
//
//         if (partition == "students")
//         {
//             this->path.pop();
//             this->path.push("groups");
//         };
//         this->cur_page = this->last_page;
//     }
//
//     // main logic interfaces
//     else if (command == "groups")
//     {
//         this->path.push("groups");
//
//         this->last_page = this->cur_page;
//
//         this->groups = this->controller->getAllGroups();
//
//         this->cur_page.title = "GROUPS";
//         this->cur_page.head = {
//             "Your groups:",
//             "id | name"};
//
//         this->cur_page.meta.clear();
//
//         std::string line;
//         for (auto& rec : *this->groups)
//         {
//             line = std::to_string(rec.group_data.id);
//             line.append(") ");
//             line.append(rec.group_data.name);
//
//             this->cur_page.meta.push_back(line);
//         }
//
//         this->cur_page.invite = {
//             "back | exit | help",
//             "create | delete | {id}"
//         };
//
//     }
//
//     else if (command == "create")
//     {
//
//         this->last_page = this->cur_page;
//
//         if (this->path.top() == "groups")
//         {
//
//             Group new_group;
//             std::string group_name;
//
//             this->cur_page.title = "GROUP CREATE";
//             this->cur_page.head = { "So, lets create a new group" };
//             this->cur_page.meta = {
//                 "Please enter the group name.."
//             };
//             this->cur_page.invite = {
//                 "back | exit | help",
//                 "{name}"
//             };
//
//             this->render();
//
//             std::cout << "name> ";
//             std::cin >> group_name;
//
//             bool ok_status_code = this->controller->createNewGroup(group_name);
//
//             if (ok_status_code)
//             {
//                 this->cur_page.head = { "Nice!" };
//                 this->cur_page.meta = { "New group was created!" };
//                 this->cur_page.invite = {
//                     "groups | exit | help"
//                 };
//             }
//             else
//             {
//                 this->cur_page.head = { "Something went wrong.." };
//                 this->cur_page.meta = { "Name is invalid!" };
//                 this->cur_page.invite = {
//                     "back | exit | help"
//                 };
//             }
//         }
//
//         else if (this->path.top() == "students")
//         {
//
//         }
//         // TODO : students
//     }
//
//     else if (this->isId(command))  // user enter the id
//     {
//         // TODO : g : BISO в хеде
//         this->last_page = this->cur_page;
//
//         unsigned id = std::stoi(command);
//
//         if (this->path.top() == "groups")
//         {
//
//             this->path.top() = "students";
//
//             this->students = this->controller->getStudentsByGroupId(id);
//             Group g = this->controller->getGroupById(id);
//
//             std::string line;
//             line = "STUDENTS ( ";
//             line.append(g.name);
//             line.append(" )");
//
//             this->cur_page.title = line;
//
//             this->cur_page.head = { "Look:" };
//
//             if (this->students->size() != 0)
//             {
//                 this->cur_page.meta.clear();
//
//                 for (auto& s : *this->students)
//                 {
//                     line = std::to_string(s.student_data.id);
//                     line.append(") ");
//                     line.append(s.student_data.first_name);
//                     line.append(" ");
//                     line.append(s.student_data.middle_name);
//
//                     this->cur_page.meta.push_back(line);
//                 }
//
//                 this->cur_page.invite = {
//                     "back | exit | help",
//                     "create | delete | {id}"
//                 };
//             }
//             else
//             {
//                 this->cur_page.meta = { "You have not students in this group" };
//
//                 this->cur_page.invite = {
//                     "back | exit | help",
//                     "create"
//                 };
//             }
//
//         }
//
//     }
//
//     else
//     {
//         this->cur_page.title = "HUYNU NE NESI!";
//         this->cur_page.head = { "wtf..." };
//         this->cur_page.meta = { "i dont understand u" };
//         this->cur_page.invite = { "help | exit | back" };
//     }
//
// }
//
//
// void Interface::render()
// {
//
//     this->drawLine();
//     std::cout << "\t\t\t\t\t" << "<- " << this->cur_page.title << " ->" << std::endl;
//
//     for (auto& token : this->cur_page.head)
//     {
//         std::cout << '\t' << token << std::endl;
//     }
//
//     this->drawLine();
//
//     for (auto& token : this->cur_page.meta)
//     {
//         std::cout << '\t' << token << std::endl;
//     }
//
//     this->drawLine();
//
//     for (auto& token : this->cur_page.invite)
//     {
//         std::cout << '\t' << token << std::endl;
//     }
//
//     this->drawLine();
// }
//
//
// void Interface::drawLine() const
// {
//     for (unsigned short i = 0; i < this->line_size; i++)
//     {
//         std::cout << '-';
//     }
//     std::cout << std::endl;
// }
//
//
// bool Interface::isId(const std::string &command)
// {
//     unsigned short digits_count = 0;
//     unsigned short comm_len = command.size();
//
//     for (auto& c : command)
//     {
//         if (std::isdigit(c)) digits_count++;
//     }
//
//     return (digits_count == comm_len);
// }
//

#include "../headers/Libs.h"
#include "../headers/Interface.h"
#include "../headers/Page.h"
#include "../headers/models/Student.h"


struct Action
{
    char command;

};


Interface::Interface() {

    this->line_size = 50;

    this->path.push("h");

}


void Interface::setController(Controller *conn)
{
    this->controller = conn;
}


void Interface::runPolling()
{

    std::string command;
    this->render();

    while (true)
    {
        std::cout << "let> ";
        std::cin >> command;

        if (command == "help") this->path.push("h");
        else if (command == "exit") this->path.push("e");
        else if (command == "back") this->path.pop();
        else if (command == "groups") this->path.push("g-");
        else if (command == "students") this->path.push("s-");

        else if (command == "create")
        {
            if (this->path.top() == "g-")
            {
                this->path.push("cg-");
            }
        }
        else if (this->isId(command))
        {
            if (this->path.top() == "g-")
            {
                std::string line = "g";
                line.append(command);
                this->path.push(line);
            }
        }

        this->update(command);
        this->render();
    }

}







void Interface::update(const std::string& command)
{
    /* event cases */
    std::string action = this->path.top();
    char comm = action[0];

    // HELP...
    if (comm == 'h')
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

    else if (comm == 'e')
    {
        this->cur_page.title = "Okey..";
        this->cur_page.head = { "Bye!" };
        this->cur_page.meta = { "))" };
        this->cur_page.invite = { "see u later" };

        this->render();

        exit(0);
    }

    else if (comm == 'g')
    {
        std::string param = action.substr(1, action.size());

        if (param == "-")
        {
            this->buffer = this->controller->getAllGroups();
            this->cur_page.title = "GROUPS";
            this->cur_page.head = { "Your groups:" };
            this->cur_page.meta.clear();
            std::string line;
            for (auto& rec : *this->buffer)
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
        else
        {
            unsigned id = std::stoi(param);

            this->buffer = this->controller->getStudentsByGroupId(id);
            Group g = this->controller->getGroupById(id);

            std::string line;
            line = "STUDENTS ( ";
            line.append(g.name);
            line.append(" )");

            this->cur_page.title = line;
            this->cur_page.head = {
                "Members count:",
                std::to_string(g.members_count)
            };

            this->cur_page.meta.clear();
            for (auto& rec : *this->buffer)
            {
                line = std::to_string(rec.student_data.id);
                line.append(") ");
                line.append(rec.student_data.first_name);
                line.append(" ");
                line.append(rec.student_data.middle_name);

                this->cur_page.meta.push_back(line);
            }
            this->cur_page.invite = {
                "back | exit | help",
                "create | delete | {id}"
            };
        }

    }

    else if (comm == 'c')
    {
        if (action[1] == 'g')
        {
            Group new_group;
            std::string group_name;

            this->cur_page.title = "GROUP CREATE";
            this->cur_page.head = { "So, lets create a new group" };
            this->cur_page.meta = {
                "Please enter the group name.."
            };
            this->cur_page.invite = {
                "exit | help",
                "{name}"
            };

            this->render();

            std::cout << "name> ";
            std::cin >> group_name;


            bool ok_status_code = this->controller->createNewGroup(group_name);

            if (ok_status_code)
            {
                this->cur_page.head = { "Nice!" };
                this->cur_page.meta = { "New group was created!" };
                this->cur_page.invite = {
                    "groups | exit | help"
                };
            }
            else
            {
                this->cur_page.head = { "Something went wrong.." };
                this->cur_page.meta = { "Name is invalid!" };
                this->cur_page.invite = {
                    "back | exit | help"
                };
            }
        }
    }
}


void Interface::render()
{

    this->drawLine();
    std::cout << "\t\t\t\t\t" << "<- " << this->cur_page.title << " ->" << std::endl;

    for (auto& token : this->cur_page.head)
    {
        std::cout << '\t' << token << std::endl;
    }

    this->drawLine();

    for (auto& token : this->cur_page.meta)
    {
        std::cout << '\t' << token << std::endl;
    }

    this->drawLine();

    for (auto& token : this->cur_page.invite)
    {
        std::cout << '\t' << token << std::endl;
    }

    this->drawLine();
}


void Interface::drawLine() const
{
    for (unsigned short i = 0; i < this->line_size; i++)
    {
        std::cout << '-';
    }
    std::cout << std::endl;
}


bool Interface::isId(const std::string &command)
{
    unsigned short digits_count = 0;
    unsigned short comm_len = command.size();

    for (auto& c : command)
    {
        if (std::isdigit(c)) digits_count++;
    }

    return (digits_count == comm_len);
}


