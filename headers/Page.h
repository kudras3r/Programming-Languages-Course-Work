#ifndef PAGE_H
#define PAGE_H


#include "Libs.h"


typedef std::vector<std::string> header;
typedef std::vector<std::string> body;
typedef std::vector<std::string> footer;
typedef std::string name;


struct Page
{
    name title;
    header head;
    body meta;
    footer invite;
};

#endif //PAGE_H
