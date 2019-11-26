#include <iostream>
#include "DoublyLinkedList.h"

class Faculty
{
public:
    Faculty();
    Faculty(int id, std::string nombre, std::string lev, std::string dept, DoublyLinkedList<int>* advisees_list);
    ~Faculty();


    int getID();
    std::string getName();
    std::string getLevel();
    std::string getDepartment();
    std::string getAdvisees();

    int FacultyID;
    std::string name;
    std::string level;
    std::string department;
    DoublyLinkedList<int>* advisees;

};
