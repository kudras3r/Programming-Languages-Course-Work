#ifndef STUDENT_H
#define STUDENT_H

#include "/home/kud/Projects/ProgLanCoursework/headers/Libs.h"

#include "/home/kud/Projects/ProgLanCoursework/headers/models/Date.h"


struct Student
{

    unsigned id;
    unsigned group_id;

    std::string first_name;
    std::string middle_name;
    std::string last_name;

    Date date_of_birth;

    bool sex;  // 1 - man; 0 - woman

    Date date_of_receipt;

    std::string departament;
    std::string pulpit;

    std::string grade_book;

    bool namesIsValid()
    {
        if (nameIsValid(this->first_name) 
            && nameIsValid(this->middle_name)
            && nameIsValid(this->last_name)) return true;
        
        return false;
    }

    bool nameIsValid(const std::string name)
    {
        if (std::isupper(name[0])) 
        {
            unsigned c = 0;
            for (unsigned i = 1; i < name.length(); i++)
            {
                if (std::islower(name[i])) c++;
            }
            if (c == name.length() - 1) return true;
        }
        return false;
    }

    bool pulIsValid()
    {
        std::string pul = this->pulpit;
        if (pul[2] == '-' && std::isdigit(pul[3]))
        {
            if (std::isalpha(pul[0]) && std::isalpha(pul[1]))
            {
                if (std::isupper(pul[0]) && std::isupper(pul[1]))
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool GBookIsValid()
    {
        std::string gb = this->grade_book;
        if (gb.length() == 7) {
            if (std::isdigit(gb[0]) && std::isdigit(gb[1])
                && std::isdigit(gb[3]) && std::isdigit(gb[4])
                && std::isdigit(gb[5]) && std::isdigit(gb[6]))
            {
                if (std::isalpha(gb[2]) && std::isupper(gb[2]))
                {
                    return true;
                }
            }
        }
        return false;
    }

};

#endif //STUDENT_H
