#include "/home/kud/Projects/ProgLanCoursework/headers/Libs.h"
#include "/home/kud/Projects/ProgLanCoursework/headers/Interface.h"
#include "/home/kud/Projects/ProgLanCoursework/headers/Page.h"
#include "/home/kud/Projects/ProgLanCoursework/headers/models/Student.h"


Interface::Interface() {

    this->line_size = 50;

    this->path.push("H");
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

        // path clear 
        if (this->path.size() >= 10)
        {
            std::string last = this->path.top();
            while (!this->path.empty())
            {
                this->path.pop();
            }
            this->path.push("H");
            this->path.push(last);
        }

        // commands cases
        if (command == "help" && this->path.top() != "h") this->path.push("h");

        else if (command == "exit") this->path.push("e");

        else if (command == "back" && this->path.size() > 1) 
        {
            this->path.pop();
            if (this->path.top() == "cg-") this->path.pop();
        }

        else if (command == "groups" && this->path.top() != "g-") this->path.push("g-");

        else if (command == "students" && this->path.top() != "s-") this->path.push("s-");

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
        }
        // user enter id..
        else if (this->isId(command))
        {
            // group id;
            if (this->path.top() == "g-")
            {
                unsigned id = std::stoi(command);
                unsigned groups_count = this->controller->getGroupsCount();
                
                if (!(id < 1 || id > groups_count))  
                {
                    std::string line = "g";
                    line.append(command);
                    this->path.push(line);
                }
            }
            // student id;
            else if (this->path.top()[0] == 'g' || this->path.top() == "s-")
            {
                // validate that input id is in range of group / all students
                unsigned id = std::stoi(command);
                
                if (this->path.top()[0] == 'g') 
                {                
                    unsigned group_id = std::stoi(this->path.top().substr(1, this->path.top().size()));
                    this->buffer = this->controller->getStudentsByGroupId(group_id);
                }
                else this->buffer = this->controller->getAll("students");
                
                std::set<unsigned> ids;

                for (auto& rec : *this->buffer)
                {
                    ids.insert(rec.student_data.id);
                }

                if (ids.find(id) != ids.end()) 
                {
                    std::string line = "s";
                    line.append(command);
                    this->path.push(line);
                }
            }
             
        }

        else if (command == "delete")
        {
            if (this->path.top() == "g-")
            {
                std::string id;
                std::cout << "GroupId> ";
                std::cin >> id;
                if (this->isId(id))
                {
                    std::string line = "dg";
                    line.append(id);
                    this->path.push(line);
                }
            }
            // TODO... 
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
    std::stack a = this->path;

    while (!a.empty())
    {
        std::cout << a.top() << " | ";
        a.pop();
    }

    // home 
    if (comm == 'H')
    {
        this->setHomePage();
    }

    // help
    else if (comm == 'h')
    {
        this->setHelpPage();
    }
    
    // exit
    else if (comm == 'e')
    {
        this->setByePage();

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
            this->buffer = this->controller->getAll("groups");
            this->setGroupsPage(this->buffer);
        }
        // show group with id;
        else
        {
            unsigned id = std::stoi(param);
            this->buffer = this->controller->getStudentsByGroupId(id);
            Group g = this->controller->getById("group", id).group_data;

            this->setGroupPage(&g, this->buffer);   
        }

    }

    // show students..
    else if (comm == 's')
    {
        std::string param = action.substr(1, action.size());
        // all;
        if (param == "-")
        {
            this->buffer = this->controller->getAll("students");
            this->setStudentsPage(this->buffer);
        }
        // with id;
        else 
        {
            unsigned id = std::stoi(param);
            Record rec = this->controller->getById("student", id);

            this->setStudentPage(&rec);     
        }
    }

    //  create..
    else if (comm == 'c')
    {
        char first_param = action[1]; 
        
        // group;
        if (first_param == 'g')
        {
            Group new_group;
            std::string group_name;

           this->setGroupCreatingPage();

            this->render();

            std::cout << "name> ";
            std::cin >> group_name;

            bool status_code = this->controller->createNewGroup(group_name);

            setResponsePage(status_code);
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

                this->setStudentCreatingPage();

                this->render();

                std::cout << "FMLnames> ";
                std::cin >> new_student.first_name 
                    >> new_student.middle_name 
                    >> new_student.last_name;
                
                std::string d1, m1, y1, d2, m2, y2, s;
                
                std::cout << "DMYofBirth> ";
                std::cin >> d1 >> m1 >> y1;

                std::cout << "DMYofReceipt> ";
                std::cin >> d2 >> m2 >> y2;

                std::cout << "Sex> ";
                std::cin >> s;

                if (this->isNumber(d1) && this->isNumber(m1) && this->isNumber(y1)
                    && this->isNumber(d2) && this->isNumber(m2) && this->isNumber(y2)
                    && (s == "1" || s == "0")) 
                {
                    Date d = {std::stoi(d1), std::stoi(m1), std::stoi(y1)};
                    new_student.date_of_birth = d;

                    d = {std::stoi(d2), std::stoi(m2), std::stoi(y2)};
                    new_student.date_of_receipt = d;


                    new_student.sex = std::stoi(s);
                    std::cout << "Departament> ";
                    std::cin >> new_student.departament;

                    std::cout << "Pulpit> ";
                    std::cin >> new_student.pulpit;

                    std::cout << "GBook> ";
                    std::cin >> new_student.grade_book;

                    bool status_code = this->controller->createNewStudent(new_student, group_id);

                    setResponsePage(status_code);
                }
                else setResponsePage(0);
            }
        }
    }

    
}


void Interface::render()
{   
    std::cout << std::endl;
    
    this->drawLine('~');

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

    this->drawLine('-');

    for (auto& token : this->cur_page.meta)
    {
        std::cout << '\t' << token << std::endl;
    }

    this->drawLine('-');

    for (auto& token : this->cur_page.invite)
    {
        std::cout << '\t' << token << std::endl;
    }

    this->drawLine('~');
}


void Interface::drawLine(char c) const
{
    for (unsigned short i = 0; i < this->line_size; i++)
    {
        std::cout << c;
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


bool Interface::isNumber(const std::string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
