#include "Student.h"

using namespace std;

Student::Student()
{}

Student::Student(int id, string nombre, string year, string maj, double gradepoint, int adv_id)
{
    this->StudentID = id;
    this->name = nombre;
    this->level = year;
    this->major = maj;
    this->gpa = gradepoint;
    this->advisor = adv_id;
}

Student::~Student()
{}


int Student::getID()
{
    return this->StudentID;
}
string Student::getName()
{
    return this->name;
}
string Student::getLevel()
{
    return this->level;
}
string Student::getMajor()
{
    return this->major;
}
double Student::getGPA()
{
    return this->gpa;
}
int Student::getAdvisorID()
{
    return this->advisor;
}
void Student::setAdvisorID(int id)
{
    this->advisor = id;
}
