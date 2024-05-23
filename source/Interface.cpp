#include "/home/kud/Projects/ProgLanCoursework/headers/Libs.h"
#include "/home/kud/Projects/ProgLanCoursework/headers/Interface.h"
#include "/home/kud/Projects/ProgLanCoursework/headers/Page.h"
#include "/home/kud/Projects/ProgLanCoursework/headers/models/Student.h"


Interface::Interface() {

    this->line_size = 50;

    this->path.push("h");
    this->update();

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
            std::string action = this->path.top();
            char comm = action[0];

            if (comm == 'g')
            {
                char param = action[1];
                
                if (param == '-') this->path.push("cg-");
                else 
                {
                    std::string line = "cs";
                    line += param;
                    this->path.push(line);
                }
            }
            else if (this->path.top()[0] == 'g')
            {

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

        this->update();
        this->render();
    }
}


void Interface::update()
{
    /* event cases */
    std::string action = this->path.top();
    char comm = action[0];

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
    
    // exit
    else if (comm == 'e')
    {
        this->cur_page.title = "Okey..";
        this->cur_page.head = { "Bye!" };
        this->cur_page.meta = { "))" };
        this->cur_page.invite = { "see u later" };

        this->render();

        exit(0);
    }

    // show groups..
    else if (comm == 'g')
    {
        std::string param = action.substr(1, action.size());

        // all;
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
        // show group with id;
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
                std::to_string(g.members_count),
                "id | f name | s name"
            };

            this->cur_page.meta.clear();
            if (this->buffer->size()) 
            {
                for (auto& rec : *this->buffer)
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

    }

    // create..
    else if (comm == 'c')
    {
        char first_param = action[1]; 
        
        // group;
        if (first_param == 'g')
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

        // student
        else if (first_param == 's')
        {
            char second_param = action[2];

            // in groups with id
            if (second_param != '-')
            {
                unsigned group_id = std::stoi(action.substr(2, action.size()));
               
                Student new_student;
                new_student.group_id = group_id;

                this->cur_page.title = "CREATE NEW STUDENT";
                this->cur_page.head = {
                    "Lets create a new student."
                };
                this->cur_page.meta = {
                    "Please enter the : first middle and last names with spaces"
                };
                this->cur_page.invite = {
                    "back | exit | help"
                };

                this->render();

                std::cout << "FMLnames> ";
                std::cin >> new_student.first_name 
                    >> new_student.middle_name 
                    >> new_student.last_name;

                this->cur_page.meta = {
                    "Nice! Now enter the : day month and year of birth with spaces"
                };

                this->render();
                
                std::cout << "DMYofBirth> ";

                Date d;
                std::cin >> d.day >> d.month >> d.year;

                new_student.date_of_birth = d;

                new_student.sex = 1;
                new_student.date_of_receipt.day = 1;
                new_student.date_of_receipt.month = 2;
                new_student.date_of_receipt.year = 3;
                new_student.departament = "ASD";
                new_student.pulpit = "DSA";

                // .... TODO
                bool ok_status_code = this->controller->createNewStudent(new_student, group_id);
                if (ok_status_code)
                {
                    this->cur_page.title = "CREATE NEW STUDENT";
                    this->cur_page.head = {
                        "All is good!"
                    };
                    this->cur_page.meta = {
                        "New student was created"
                    };
                    this->cur_page.invite = {
                        "back | exit | help"
                    };
                    this->path.pop();
                }
            }
        }
    }
}


void Interface::render()
{
    std::cout << this->path.top() << std::endl;

    this->drawLine();

    unsigned short space = this->line_size - this->cur_page.title.size() - 6;
    for (unsigned short i = 0; i < space / 2; i++) std::cout << ' ';
    std::cout << "<- ";
    std::cout << this->cur_page.title;
    std::cout << " ->" << std::endl;
    for (unsigned short i = 0; i < space / 2; i++) std::cout << ' ';
    std::cout << std::endl;


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


bool Interface::isId(const std::string command)
{
    unsigned short digits_count = 0;
    unsigned short comm_len = command.size();

    for (auto& c : command)
    {
        if (std::isdigit(c)) digits_count++;
    }

    return (digits_count == comm_len);
}


