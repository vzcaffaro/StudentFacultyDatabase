#include <iostream>
#include <fstream>
#include "BST.h"

using namespace std;

extern BST<Student> *masterStudent;
extern BST<Faculty> *masterFaculty;

class fileReader
{
public:
    fileReader();
    ~fileReader();

    void readStudent();
    void readFaculty();

    void writeStudent();
    string getStudentInfo(TreeNode<Student> * node);

    void writeFaculty();
    string getFacultyInfo(TreeNode<Faculty> * node);

    string line;
    string data;

    int s_ID;
    string s_name;
    string s_level;
    string major;
    double gpa;
    int advisor;


    int f_ID;
    string f_name;
    string f_level;
    string department;
    DoublyLinkedList<int>* advisees;

};
