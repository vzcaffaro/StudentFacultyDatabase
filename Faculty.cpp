#include "Faculty.h"

using namespace std;

Faculty::Faculty()
{}

Faculty::Faculty(int id, string nombre, string lev, string dept, DoublyLinkedList<int>* advisees_list)
{
    this->FacultyID = id;
    this->name = nombre;
    this->level = lev;
    this->department = dept;
    this->advisees = advisees_list;
}

Faculty::~Faculty()
{}


int Faculty::getID()
{
    return this->FacultyID;
}
string Faculty::getName()
{
    return this->name;
}
string Faculty::getLevel()
{
    return this->level;
}
string Faculty::getDepartment()
{
    return this->department;
}
string Faculty::getAdvisees()
{
    string advisees_list = "";
    DoublyNode<int> * curr = this->advisees->front;
    advisees_list += "[";
    while(curr != NULL)
    {
        advisees_list += to_string(curr->data);
        if(curr->next != NULL)
            advisees_list += ",";
        curr = curr->next;
    }
    advisees_list += "]";
    return advisees_list;
}
