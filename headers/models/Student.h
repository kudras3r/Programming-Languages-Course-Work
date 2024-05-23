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

};

#endif //STUDENT_H
