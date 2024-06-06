#ifndef RECORD_H
#define RECORD_H

#include "Group.h"
#include "Student.h"


struct Record
{
    char type;
    bool deleted = false;
    
    Group group_data;
    Student student_data;
};

#endif //RECORD_H
