#ifndef GROUP_H
#define GROUP_H


#include "../Libs.h"


struct Group
{
    unsigned id;
    unsigned members_count;
    std::string name;


    bool nameIsValid() 
    {
        if (std::isalpha(this->name[0]) && std::isalpha(this->name[1]) 
            && std::isalpha(this->name[2]) && std::isalpha(this->name[3]) 
            && this->name[4] == '-' && this->name[7] == '-' 
            && std::isdigit(this->name[5]) && std::isdigit(this->name[6]) 
            && std::isdigit(this->name[8]) && std::isdigit(this->name[9]))
        {
            return true;
        }
        return false;
    }

};

#endif //GROUP_H
