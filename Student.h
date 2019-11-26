#include <iostream>

class Student
{
public:
    Student();
    Student(int id, std::string nombre, std::string year, std::string maj, double gradepoint, int adv_id);
    ~Student();


    int getID();
    std::string getName();
    std::string getLevel();
    std::string getMajor();
    double getGPA();
    int getAdvisorID();
    void setAdvisorID(int id);


    int StudentID;
    std::string name;
    std::string level;
    std::string major;
    double gpa;
    int advisor;
};
