#include "person.h"

Person::Person()
{
}
Person::Person(const string &name, int age, bool gender)
{
    this->name = name;
    this->age = age;
    this->gender = gender;
}

bool Person::is_male() const
{
    return gender == MALE;
}
bool Person::is_female() const
{
    return gender == FEMALE;
}
bool Person::is_child() const
{
    return age < 18;
}
bool Person::is_adult() const
{
    return age >= 18;
}
bool Person::is_men() const
{
    return is_male() && is_adult();
}
bool Person::is_women() const
{
    return is_female() && is_adult();
}
string Person::get_name() const
{
    return name;
}