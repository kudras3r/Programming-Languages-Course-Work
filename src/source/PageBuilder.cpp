#include "PageBuilder.h"



void PageBuilder::setHomePage()
{
    this->cur_page.title = "HOME";
    this->cur_page.head = {
    };
    this->cur_page.meta = {
        "Пожалуйста,",
        "Вас приветствует StudentsDB!",
        "перед тем как приступать к управлению студентами",
        "пропишите команду help для ознакомления с системой."
    };
    this->cur_page.invite = {
        "команды : ",
        "help | exit | groups | students"
    };
}


void PageBuilder::setHelpPage()
{
    this->cur_page.title = "HELP";
    this->cur_page.head = {
        "StudentsDB - это проект, призванный упростить учебу."
    };
    this->cur_page.meta = {
        "В системе присутствует три основных раздела(модели)",
        "students | groups | grade",
        "",
        "STUDENTS:",
        "модель студента - таблица всех студентов ссылающаяся на группу",
        "и содержащая в себе ссылку на таблицу оценок студента."
        "",
        "Поля модели студента:",
        "---",
        "private ID",
        "private GROUP_ID",
        "public FIRST | M | L NAMES",
        "public DATEOFBIRTH",
        "public SEX",
        "public DATEOFRECEIPT",
        "public DEPARTAMENT",
        "public PULPIT",
        "public GRADEBOOK",
        "",
        "ВАЖНО!",
        "Пожалуйста будьте внимательны при создании и редактировании студента",
        "тк некоторые поля обязаны соответствовать особым требованиям:"
        "Дни дат должны быть 31 >= day >= 1,",
        "Все поля ФИО студента должны иметь только одну заглавную букву - первую.",
        "Поле кафедры должно выглядеть как ББ-Ц, где Б - заг. буква, а Ц - цифра",
        "Поле номера зачетной книжки должно выглядеть как ЦЦБЦЦЦЦ"
    };
    this->cur_page.invite = {
        "back | exit | help",
        "students | groups"
    };
}


void PageBuilder::setByePage()
{
    this->cur_page.title = "Bye!";
    this->cur_page.head = {
        "До свидания!"
    };
    this->cur_page.meta = { "Спасибо за ваше внимание!" };
    this->cur_page.invite = { ":)" };
}


void PageBuilder::setGroupsPage(std::vector<Record>* data)
{
    this->cur_page.title = "GROUPS";
    this->cur_page.head = { "Ваши группы:" };
    this->cur_page.meta.clear();

    std::string line;
    for (auto& rec : *data)
    {
        line = std::to_string(rec.group_data.id);
        line.append(") ");
        line.append(rec.group_data.name);

        this->cur_page.meta.push_back(line);
    }

    this->cur_page.invite = {
        "back | exit | help",
        "create | delete | {id}",
        "students"
    };
}


void PageBuilder::setGroupPage(const Group* g, std::vector<Record>* data)
{
    std::string line;
    line = "STUDENTS ( ";
    line.append(g->name);
    line.append(" )");

    this->cur_page.title = line;
    this->cur_page.head = {
        "Members count:",
        std::to_string(g->members_count),
        "id | f name | s name"
    };

    this->cur_page.meta.clear();
    if (data->size())
    {
        for (auto& rec : *data)
        {
            line = std::to_string(rec.student_data.id);
            line.append(") ");
            line.append(rec.student_data.first_name);
            line.append(" ");
            line.append(rec.student_data.middle_name);

            this->cur_page.meta.push_back(line);
        }
    }
    else this->cur_page.meta = {
        "Нет студентов"
    };

    this->cur_page.invite = {
        "back | exit | help",
        "create | delete | edit | {id}",
        "students | groups"
    };
}


void PageBuilder::setStudentsPage(std::vector<Record>* data)
{
    this->cur_page.title = "STUDENTS";
    this->cur_page.head = { "Все студенты:" };
    this->cur_page.meta.clear();
    std::string line;
    for (auto& rec : *data)
    {
        line = std::to_string(rec.student_data.id);
        line.append(") ");
        line.append(rec.student_data.first_name);
        line.append(" ");
        line.append(rec.student_data.middle_name);
        line.append(" <");
        line.append(rec.student_data.pulpit);
        line.append(" : ");
        line.append(rec.group_data.name);
        line.append(">");

        this->cur_page.meta.push_back(line);
    }

    this->cur_page.invite = {
        "back | exit | help",
        "delete | edit",
        "groups"
    };
}


void PageBuilder::setStudentPage(Record* rec)
{
    std::string line;
    Student s = rec->student_data;

    line = "STUDENT <";
    line.append(rec->group_data.name);
    line.append(">");

    this->cur_page.title = line;

    line = s.first_name;
    line.append(" ");
    line.append(s.middle_name);
    line.append(" ");
    line.append(s.last_name);

    this->cur_page.head = {
        line
    };
    this->cur_page.meta.clear();

    line = "Дата рождения: ";
    line.append(s.date_of_birth.likeStr());
    this->cur_page.meta.push_back(line);

    line = "Дата поступления: ";
    line.append(s.date_of_receipt.likeStr());
    this->cur_page.meta.push_back(line);

    line = "Пол: ";
    if (s.sex) line.append("Мужской");
    else line.append("Женский");
    this->cur_page.meta.push_back(line);

    line = "Факультет: ";
    line.append(s.departament);
    this->cur_page.meta.push_back(line);

    line = "Кафедра: ";
    line.append(s.pulpit);
    this->cur_page.meta.push_back(line);

    line = "№ зачетной книжки: ";
    line.append(s.grade_book);
    this->cur_page.meta.push_back(line);

    this->cur_page.invite = {
        "back | exit | help",
        "delete | edit",
        "groups | students"
    };
}


void PageBuilder::setGroupCreatingPage()
{
    this->cur_page.title = "GROUP CREATE";
    this->cur_page.head = {
        "Создание группы"
    };
    this->cur_page.meta = {
        "Пожалуйста введите:"
    };
    this->cur_page.invite = {
        "{group name}"
    };
}


void PageBuilder::setStudentCreatingPage()
{
    this->cur_page.title = "CREATE NEW STUDENT";
    this->cur_page.head = {
        "Создание студента"
    };
    this->cur_page.meta = {
        "Пожалуйста введите:"
    };
    this->cur_page.invite = {
        "Б - Буква; Ц - Цифра",
        "",
        "FMLnames> {first} {middle} {last}",
        "DMYofBirth> {day} {month} {year}",
        "DMYofReceipt> {day} {month} {year}",
        "Sex> {1} - мужской или {0} - женский",
        "Departament> {Факультет} без пробелов",
        "Pulpit> {Кафедра} : ББ-Ц",
        "GBook> {Зачетная книжка} : ЦЦБЦЦЦЦ"

    };
}


void PageBuilder::setGroupEditPage()
{
    this->cur_page.title = "GROUP EDIT";
    this->cur_page.head = {
        "Изменение группы"
    };
    this->cur_page.meta = {
        "Пожалуйста введите: "
    };
    this->cur_page.invite = {
        "NewName> {имя группы}"
    };
}


void PageBuilder::setStudentEditPage()
{
    this->cur_page.title = "STUDENT EDIT";
    this->cur_page.head = {
        "Изменение студента"
    };
    this->cur_page.meta = {
        "Выберите поле для изменения: "
    };
    this->cur_page.invite = {
        "Б - Буква; Ц - Цифра",
        "",
        "-name> {Ф | И | О}",
        "DMYofBirth> {день} {месяц} {год}",
        "DMYofReceipt> {день} {месяц} {год}",
        "Sex> {1} - мужской или {0} - женский",
        "Departament> {Факультет} без пробелов",
        "Pulpit> {Кафедра} : ББ-Ц",
        "GBook> {GB number} : ЦЦБЦЦЦЦ"
        "",
        "{0} - exit",
        "{1} - Фамилия",
        "{2} - Имя",
        "{3} - Отчество",
        "{4} - Дата рождения",
        "{5} - Пол",
        "{6} - Дата поступления",
        "{7} - Факультет",
        "{8} - Кафедра",
        "{9} - Зачетная книжка"
    };
}


void PageBuilder::setResponsePage(bool all_is_good)
{
    if (all_is_good)
    {
        this->cur_page.head = { "Отлично!" };
        this->cur_page.meta = { "Все хорошо!" };
        this->cur_page.invite = {
            "back | exit | help"
        };
    }
    else
    {
        this->cur_page.head = { "Что то пошло не так.." };
        this->cur_page.meta = { "Проверьте введенные данные!" };
        this->cur_page.invite = {
            "back | exit | help"
        };
    }
}