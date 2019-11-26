#include "fileReader.h"
#include <iostream>
#include <fstream>

using namespace std;

fileReader::fileReader()
{}

fileReader::~fileReader()
{}

void fileReader::readStudent()
{
    ifstream inf;
    inf.open("studentTable.txt");
    if(inf.fail())
        return;
    while(inf.peek() != EOF)
    {
        int count = 0;
        getline(inf,line);

        data = "";
        for(int i = count; i<line.size() ; ++i)//reads the student ID
        {
            ++count;
            if(line[i] == ',')//format of file breaks info between commas
                break;
            data+=line[i];
        }
        s_ID = stoi(data);//stores ID

        data = "";
        for(int i = count; i<line.size() ; ++i) //Reads the student name
        {
            ++count;
            if(line[i] == ',')
                break;
            data+=line[i];
        }
        s_name = data;

        data = "";
        for(int i = count; i<line.size() ; ++i) //Reads the student level
        {
            ++count;
            if(line[i] == ',')
                break;
            data+=line[i];
        }
        s_level = data;

        data = "";
        for(int i = count; i<line.size() ; ++i) //Reads the student major
        {
            ++count;
            if(line[i] == ',')
                break;
            data+=line[i];
        }
        major = data;

        data = "";
        for(int i = count; i<line.size() ; ++i) //Reads the student gpa
        {
            ++count;
            if(line[i] == ',')
                break;
            data+=line[i];
        }
        gpa = stod(data);

        data = "";
        for(int i = count; i<line.size() ; ++i) //Reads the advisor's ID
        {
            ++count;
            if(line[i] == ',')
                break;
            data+=line[i];
        }
        advisor = stoi(data);

        masterStudent->insert(new Student(s_ID, s_name, s_level, major, gpa, advisor));//inserts a new student with all the info that was read
    }


    inf.close();
}




void fileReader::readFaculty()
{
    ifstream inf;
    inf.open("facultyTable.txt");
    if(inf.fail())
        return;
    while(inf.peek() != EOF)
    {
        int count = 0;
        getline(inf,line);

        data = "";
        for(int i = 0; i<line.size() ; ++i)//reads the faculty ID
        {
            ++count;
            if(line[i] == ',')
                break;
            data+=line[i];
        }
        f_ID = stoi(data);

        data = "";
        for(int i = count; i<line.size() ; ++i) //Reads the faculty member's name
        {
            ++count;
            if(line[i] == ',')
                break;
            data+=line[i];
        }
        f_name = data;

        data = "";
        for(int i = count; i<line.size() ; ++i) //Reads the faculty member's level
        {
            ++count;
            if(line[i] == ',')
                break;
            data+=line[i];
        }
        f_level = data;

        data = "";
        for(int i = count; i<line.size() ; ++i) //Reads the faculty member's department
        {
            ++count;
            if(line[i] == ',')
                break;
            data+=line[i];
        }
        department = data;

        advisees = new DoublyLinkedList<int>();
        data = "";
        for(int i = count+1; i<line.size() ; ++i) //Reads the list of advisees, starts at count+1 to ignore open bracket
        {
            if(line[i] == ']')
            {
                if(data.size()>0)
                    advisees->insertBack(stoi(data));
                break;
            }
            else if(line[i] == ',')
            {
                advisees->insertBack(stoi(data));
                data = "";
            }else{
                data+=line[i];
            }

        }



        masterFaculty->insert(new Faculty(f_ID, f_name, f_level, department, advisees));
    }

    inf.close();
}



void fileReader::writeStudent()
{
    ofstream outf;
    outf.open("studentTable.txt");
    TreeNode<Student> * curr = masterStudent->root;

    while(true)
    {
        outf << getStudentInfo(curr) << endl;//writes student info to the file
        Student * s = curr->value;
        masterStudent->deleteNode(s); //deletes the root, which is reassigned with getSuccessor method in BST
        curr = masterStudent->root; //reassigns curr
        if(curr == NULL)
            break; //breaks if root is NULL/tree is empty
    }

}

string fileReader::getStudentInfo(TreeNode<Student> * node)
{
    s_ID = node->value->getID();
    s_name = node->value->getName();
    s_level = node->value->getLevel();
    major = node->value->getMajor();
    gpa = node->value->getGPA();
    advisor = node->value->getAdvisorID();

    return (to_string(s_ID)+","+s_name+","+s_level+","+major+","+to_string(gpa)+","+to_string(advisor));
}



void fileReader::writeFaculty()
{
    ofstream outf;
    outf.open("facultyTable.txt");
    TreeNode<Faculty> * curr = masterFaculty->root;

    while(true)
    {
        outf << getFacultyInfo(curr) << endl;
        Faculty * f = curr->value;
        masterFaculty->deleteNode(f);
        curr = masterFaculty->root;
        if(curr == NULL)
            break;
    }

}

string fileReader::getFacultyInfo(TreeNode<Faculty> * node)
{
    f_ID = node->value->getID();
    f_name = node->value->getName();
    f_level = node->value->getLevel();
    department = node->value->getDepartment();
    string adv = node->value->getAdvisees();

    return (to_string(f_ID)+","+f_name+","+f_level+","+department+","+adv);
}
