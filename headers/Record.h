#ifndef RECORD_H
#define RECORD_H

#include "models/Group.h"
#include "models/Student.h"


struct Record
{
    char type;
    bool deleted = false;
    
    Group group_data;
    Student student_data;
};

#endif //RECORD_H
