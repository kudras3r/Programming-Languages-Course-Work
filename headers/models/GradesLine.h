#ifndef GRADESLINE_H
#define GRADESLINE_H


struct GradesLine
{
    /*
        Line looks like {student id} {subject} {sem} {grade}, {grade}...
    */
    
    unsigned student_id;
    std::string subject;
    unsigned semester;
    std::vector<unsigned> grades;
    
};

#endif //GRADESLINE_H
