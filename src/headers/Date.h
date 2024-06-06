#ifndef DATE_H
#define DATE_H


struct Date
{
    int day;
    int month;
    int year;

    bool isValid()
    {
        if (this->day >= 1 && this->day <= 31 
            && this->month >= 1 && this->month <= 12
            && this->year >= 1800 && this->year <= 2024)
                return true;
        
        return false;
    }

    std::string likeStr()
    {
        std::string line;
        if (this->day < 10) line = "0";
        line.append(std::to_string(this->day));
        line.append("/");
        if (this->month < 10) line.append("0");
        line.append(std::to_string(this->month));
        line.append("/");
        line.append(std::to_string(this->year));

        return line;
    }
};

#endif //DATE_H
