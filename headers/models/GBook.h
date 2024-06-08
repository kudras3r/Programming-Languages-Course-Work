#ifndef GBOOK_H
#define GBOOK_H


struct GBook
{
    /*
        storage grades in structure looks like:
            { 
                semester1 : 
                {
                    subject1 : [ grade, grade, grade..],
                    subject2 
                    ..
                } 
                semester2 
                ..
            }
    */
    std::map<unsigned, std::map<std::string, std::vector<unsigned>>> grades;
};

#endif //GBOOK_H
