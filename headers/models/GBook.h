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

    double calculateAvgMarkForSems(std::vector<unsigned> sems)
    {
        std::vector<double> marks;

        for (const unsigned& sem : sems)
        {   
            unsigned sem_points = 0;

            std::vector<std::string> subjects;
            for (const auto& pair : this->grades[sem]) subjects.push_back(pair.first);


            for (const std::string sub : subjects)
            {
                unsigned sub_points = 0;
                for (const unsigned m : this->grades[sem][sub]) sub_points += m;

                sem_points += round((double)sub_points / this->grades[sem][sub].size());
            }
            
            double avg_for_sem = (double)sem_points / this->grades[sem].size();
            marks.push_back(avg_for_sem);
        }

        double sum = 0;
        for (const double m : marks) sum += m;

        double avg = sum / marks.size();

        return avg;
    }
};

#endif //GBOOK_H
