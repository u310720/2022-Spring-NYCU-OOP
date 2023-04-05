#ifndef __PERSON_H__
#define __PERSON_H__

#include <string>
using std::string;

class Person
{
protected:
    string name;
    bool gender;
    unsigned int age;

public:
    enum GENDER
    {
        MALE,
        FEMALE
    };
    Person();
    Person(const string &name, int age, bool gender);

    bool is_male() const;
    bool is_female() const;

    bool is_adult() const;
    bool is_child() const;

    bool is_men() const;
    bool is_women() const;

    string get_name() const;
};

#endif // __PERSON_H__
