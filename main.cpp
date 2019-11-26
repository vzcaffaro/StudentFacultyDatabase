#include "fileReader.h"
#include "TreeStack.h"
#include "ChoiceStack.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void listAdvisor(int studID); //helper function to execute option 5
void listAdvisees(int facID);//helper function to execute option 6
bool addStudent(); //helper function for option 7
bool addFaculty(); //helper function for option 9
void Rollback(int lastChoice); //contains code for option 14
void rollPush(); //helper function to push versions of the tree to a stack
void rollPop(); //helper function to remove versions of trees from stack if error is detected

BST<Student> *masterStudent = new BST<Student>(); //main tree where all students are stored
BST<Faculty> *masterFaculty = new BST<Faculty>(); //main tree where all faculty are stored


TreeStack<BST<Student>> *rollStudent = new TreeStack<BST<Student>>(5); //stack for storing versions of tree to help with rollback
TreeStack<BST<Faculty>> *rollFaculty = new TreeStack<BST<Faculty>>(5);
ChoiceStack<int> *rollChoice = new ChoiceStack<int>(5); //stack for storing what choice the user made

int main(int argc, char** argv)
{
    bool loop = true;
    int studID;
    int facID;
    int lastChoice; //variable to store the last choice made by user
    Student * stud; //pointer to student
    Faculty * f; //pointer to faculty
    fileReader fr;
    fr.readStudent(); //reads from studentTable and populates tree
    fr.readFaculty(); //reads from facultyTable and populates tree


    cout<<"Welcome to the Chapman Faculty/Student database! Listed below are the 14 commands you may choose from. "<<endl;

    while(loop == true)
    {
        cout<<"\n1. Print all students and their information. \n2. Print all faculty and their information. \n3. Find and display student's information. \n4. Find and display a faculty member's information. \n5. Print the name and info of a student's faculty advisor. \n6. Print all the names and info of a faculty members advisees. \n7. Add a new student. \n8. Delete a student given the ID. \n9. Add a new faculty member. \n10. Delete a faculty member. \n11. Change a student's advisor. \n12. Remove an advisee from a faculty member. \n13. Assign an advisee to a faculty member.\n14. Rollback. \n15. Exit."<<endl;
        int choice;
        cin>>choice;
        switch (choice)
    	{
    		case 1:
    			masterStudent->printStudentTree();
    			break;

    		case 2:
    			masterFaculty->printFacultyTree();
    			break;

    		case 3:
    			cout<<"Please enter the ID of the student you want to find. "<<endl;
                cin>>studID;
                if(masterStudent->search(studID) == NULL) //search returns null if student is not found
                    cout<<"That ID number did not return any students."<<endl;
                else
                {
                    stud = masterStudent->search(studID)->value;//search returns tree node, value is the student stored in tree node
                    cout<<"Name: "<<stud->name<<endl;
                    cout<<"Class: "<<stud->level<<endl;
                    cout<<"Major: "<<stud->major<<endl;
                    cout<<"GPA: "<<stud->gpa<<endl;
                    cout<<"Advisor ID: "<<stud->advisor<<endl;
                }
    			break;

    		case 4:
                cout<<"Please enter the ID of the faculty member you want to find. "<<endl;
                cin>>facID;
                if(masterFaculty->search(facID) == NULL)
                    cout<<"That ID number did not return any faculty members."<<endl;
                else
                {
                    f = masterFaculty->search(facID)->value;
                    cout<<"Name: "<<f->name<<endl;
                    cout<<"Level: "<<f->level<<endl;
                    cout<<"Department: "<<f->department<<endl;
                    cout<<"Advisee IDs: "<<f->getAdvisees()<<endl;
                }
                break;

    		case 5:
                cout<<"Please enter the ID of the student whose faculty advisor you want to find. "<<endl;
                cin>>studID;
                listAdvisor(studID);
    			break;

    	 	case 6:
    			cout<<"Please enter the ID of the faculty member whose student advisees you want to find. "<<endl;
                cin>>facID;
                listAdvisees(facID);
                break;

    		case 7:
                rollPush(); //stores version of tree in stack before altering
    			if(addStudent())
                {
                    cout<<"The student was successfully added to the tree. "<<endl;
                    rollChoice->push(7);
                }
                else
                {
                    cout<<"There was an error in adding the student to the tree. "<<endl;
                    rollPop();
                }
                break;

    		case 8:
                rollPush();
    			cout<<"Enter the ID of the student you want to remove. "<<endl;
                cin>>studID;
                stud = masterStudent->search(studID)->value;
                if(masterStudent->deleteNode(stud))
                {
                    if(masterFaculty->search(stud->advisor)->value->advisees->remove(studID))
                        cout<<"The student was successfully removed. "<<endl;
                    rollChoice->push(8);
                } else {
                    cout<<"There was an error removing the student. "<<endl;
                    rollPop();
                }
    			break;

    		case 9:
                rollPush();
                if(addFaculty())
                {
                    cout<<"The faculty member was successfully added to the tree. "<<endl;
                    rollChoice->push(9);
                }
                else
                {
                    cout<<"There was an error in adding the faculty member to the tree. "<<endl;
                    rollPop();
                }
                break;

    		case 10:
                rollPush();
    			cout<<"Enter the ID of the faculty member you want to remove. "<<endl;
                cin>>facID;
                f = masterFaculty->search(facID)->value;
                if(masterFaculty->deleteNode(f))
                {
                    cout<<"The faculty member was successfully removed. "<<endl;
                    rollChoice->push(10);
                } else {
                    cout<<"There was an error removing the student. "<<endl;
                    rollPop();
                }
                while(!f->advisees->isEmpty()) //while the removed faculty member still has advisees left
                {
                    studID = f->advisees->removeFront(); //stores temp student id
                    masterStudent->search(studID)->value->advisor = 0; //sets the student's advisor id to 0
                }
    			break;

    		case 11:
                rollPush();
                cout<<"Enter the ID of the student whose advisor you want to change. "<<endl;
                cin>>studID;
                if(masterStudent->search(studID) == NULL)
                {
                    cout<<"That ID did not return any students. "<<endl;
                    break;
                }
                else
                {
                    int currAdvisor = masterStudent->search(studID)->value->advisor;
                    cout<<"This students current advisor ID is: "<<currAdvisor<<"\nIf you would still like to change their advisor ID, enter the ID now. If you do not want to change their ID, enter 0."<<endl;
                    cin>>facID;
                    if(facID == 0)
                    {
                        cout<<"The student's advisor was not changed. "<<endl;
                        rollPop();
                    }
                    else
                    {
                        masterStudent->search(studID)->value->advisor = facID;
                        if(masterStudent->search(studID)->value->advisor == facID)
                        {
                            masterFaculty->search(currAdvisor)->value->advisees->remove(studID);
                            masterFaculty->search(facID)->value->advisees->insertFront(studID);
                            cout<<"The student's advisor ID was successfully changed. "<<endl;
                            rollChoice->push(11);
                        }
                        else
                        {
                            cout<<"There was an error in changing the student's advisor ID."<<endl;
                            rollPop();
                        }
                    }
                }
    			break;

    		case 12:
                rollPush();
    			cout<<"Enter the ID of the faculty member whose advisee you want to remove. "<<endl;
                cin>>facID;
                if(masterFaculty->search(facID) == NULL)
                {
                    cout<<"That ID did not return any faculty members. "<<endl;
                    break;
                }
                else
                {
                    cout<<"This faculty members current advisees are: "<<masterFaculty->search(facID)->value->getAdvisees()<<endl;
                    cout<<"Please enter the ID of the advisee you want to remove. If you do not want to remove a student advisee, enter 0. "<<endl;
                    cin>>studID;
                    if(studID == 0)
                    {
                        cout<<"The faculty member's advisees were not changed. "<<endl;
                        rollPop();
                    }
                    else
                    {
                        if(masterFaculty->search(facID)->value->advisees->remove(studID))
                        {
                            masterStudent->search(studID)->value->advisor = 0; //assigns 0 to the advisor value for the student who was removed as an advisee
                            cout<<"The advisee was successfully removed. "<<endl;
                            rollChoice->push(12);
                        }
                        else
                        {
                            cout<<"There was an error removing the advisee. "<<endl;
                            rollPop();
                        }
                    }
                }
        		break;

    		case 13:
                rollPush();
                cout<<"Enter the ID of the faculty member who you want to assign an advisee. "<<endl;
                cin>>facID;
                cout<<"This faculty members current advisees are: "<<masterFaculty->search(facID)->value->getAdvisees()<<endl;
                cout<<"Please enter the ID of the advisee you want to asssign to this faculty member. If you do not want to assign a student advisee, enter 0. "<<endl;
                cin>>studID;
                if(studID == 0)
                {
                    cout<<"The faculty member's advisees were not changed. "<<endl;
                    rollPop();
                    break;
                }
                if(masterStudent->search(studID)->value->advisor != 0)
                {
                    int tempID = studID;
                    cout<<"That student already has an advisor. Enter '1' to change their advisor, or enter '0' if you do not want to change their advisor."<<endl;
                    cin>>studID;
                    if(studID == 1)
                    {
                        studID = tempID;
                    }
                }
                if(studID == 0)
                {
                    cout<<"The faculty member's advisees were not changed. "<<endl;
                    rollPop();
                }

                else
                {
                    masterFaculty->search(facID)->value->advisees->insertBack(studID);//adds student to advisee list
                    masterStudent->search(studID)->value->advisor = facID; //assigns value to student's advisor ID
                    cout<<"The advisee was successfully assigned. "<<endl;
                    rollChoice->push(13);
                }
    			break;

            case 14:
                lastChoice = rollChoice->pop();
                Rollback(lastChoice);
                break;

    		case 15:
    			loop = false;
    			break;
    	 }

     }


    fr.writeStudent(); //writes masterStudent tree out to studentTable
    fr.writeFaculty(); //writes masterFaculty tree out to facultyTable
}

void listAdvisor(int studID)
{
    if(masterStudent->search(studID) == NULL)
        cout<<"That ID number did not return any students."<<endl;
    else
    {
        Student * s1 = masterStudent->search(studID)->value;
        int facID = s1->advisor;
        Faculty * f1 = masterFaculty->search(facID)->value;
        cout<<"ID: "<<f1->getID()<<endl;
        cout<<"Name: "<<f1->name<<endl;
        cout<<"Level: "<<f1->level<<endl;
        cout<<"Department: "<<f1->department<<endl;
        cout<<"Advisee IDs: "<<f1->getAdvisees()<<endl;
    }
}

void listAdvisees(int facID)
{
    if(masterFaculty->search(facID) == NULL)
        cout<<"That ID number did not return any faculty members."<<endl;
    else
    {
        Faculty * f1 = masterFaculty->search(facID)->value;
        string adv_list = f1->getAdvisees();
        int adv_count = 0;
        if(adv_list.size() > 2) //if the list is longer that two, accounting for brackets []
            ++adv_count; //there is at least one ID
        for(int i = 0; i<adv_list.size();++i)
        {
            if(adv_list[i] == ',')
            {
                ++adv_count; //increases count of IDs for every comma
            }
        }
        int a1[adv_count]; //array that stores advisee IDs
        int counter = 1; //skips the open bracket
        for(int i = 0; i<adv_count ; ++i)
        {
            string x = "";
            for(int j = counter ; j<adv_list.size() ; ++j)
            {
                if(adv_list[j] == ',' || adv_list[j] == ']')
                {
                    counter++;
                    break;
                }else{
                    x += adv_list[j];
                    counter++;
                }
            }
            a1[i] = stoi(x);//stores advisee in array
        }

        for(int k = 0; k<adv_count ; ++k)
        {
            Student * s1 = masterStudent->search(a1[k])->value;
            cout<<"ID: "<<a1[k]<<endl;
            cout<<"Name: "<<s1->name<<endl;
            cout<<"Class: "<<s1->level<<endl;
            cout<<"Major: "<<s1->major<<endl;
            cout<<"GPA: "<<s1->gpa<<endl<<endl;
        }
    }
}

bool addStudent()
{
    int studID, adv_id;
    string name, year, major;
    char trash;
    double gradepoint;
    bool advisorCheck = true;


    cout<<"Please enter the ID of the student you want to add. "<<endl;
    cin>>studID;
    cin.get(trash);//clears the '\n'
    cout<<"Please enter the name of the student you want to add. "<<endl;
    getline(cin,name);
    cout<<"Please enter the class level of the student you want to add. "<<endl;
    getline(cin,year);
    cout<<"Please enter the major of the student you want to add. "<<endl;
    getline(cin,major);
    cout<<"Please enter the GPA of the student you want to add. "<<endl;
    cin>>gradepoint;
    cout<<"Please enter the advisor ID of the student you want to add. "<<endl;
    cin>>adv_id;
    while(masterFaculty->search(adv_id) == NULL)
    {
        cout<<"That ID did not return any faculty members. Please enter a valid faculty ID. If you don't have a advisor for this student, enter 0."<<endl;
        cin>>adv_id;
        if(adv_id == 0)
        {
            advisorCheck = false;
            break;
        }
    }
    if(advisorCheck)
    {
        masterFaculty->search(adv_id)->value->advisees->insertBack(studID);
    }


    Student * studly = new Student(studID,name,year,major,gradepoint,adv_id);
    masterStudent->insert(studly);

    if(masterStudent->search(studID)->value == studly)
    {
        return true;
    } else {
        return false;
    }
}




bool addFaculty()
{
    int facID, adv_id;
    string name, level, department;
    char trash;
    int numAdvisees;
    DoublyLinkedList<int> * adv_list = new DoublyLinkedList<int>();
    bool status;


    cout<<"Please enter the ID of the faculty member you want to add. "<<endl;
    cin>>facID;
    cin.get(trash);
    cout<<"Please enter the name of the faculty member you want to add. "<<endl;
    getline(cin,name);
    cout<<name<<endl;
    cout<<"Please enter the level of the faculty member you want to add. "<<endl;
    getline(cin,level);
    cout<<level<<endl;
    cout<<"Please enter the department of the faculty member you want to add. "<<endl;
    getline(cin,department);
    cout<<department<<endl;
    cout<<"Please enter the number of advisees you want to assign to this faculty member. "<<endl;
    cin>>numAdvisees;
    cin.get(trash);
    for(int i = 0; i<numAdvisees; ++i)
    {
        cout<<"Enter the ID of a student you want to assign to "<<name<<" as an advisee. "<<endl;
        cin>>adv_id;
        status = true;
        while(masterStudent->search(adv_id) == NULL)
        {
            cout<<"That ID did not return any students. Please enter a valid student ID. If you don't have a advisee for this faculty member, enter 0."<<endl;
            cin>>adv_id;
            if(adv_id == 0)
            {
                --numAdvisees;
                status = false;
                break;
            }
        }
        if(status)
        {
            adv_list->insertBack(adv_id);
            masterStudent->search(adv_id)->value->advisor = facID;
        }
    }



    Faculty * fac = new Faculty(facID,name,level,department,adv_list);
    masterFaculty->insert(fac);

    if(masterFaculty->search(facID)->value == fac)
    {
        return true;
    } else {
        return false;
    }


}

void Rollback(int lastChoice)
{
    char ans;
    if (lastChoice == -1)
    {
        cout<<"You cannot rollback if you have not made any changes yet. \nRollback cancelled."<<endl;
        return;
    }
    else if (lastChoice == 7)
        cout<<"Are you sure you want to remove the student you just added? Y/N "<<endl;
    else if(lastChoice == 8)
        cout<<"Are you sure you want to restore the student you just removed? Y/N "<<endl;
    else if(lastChoice == 9)
        cout<<"Are you sure you want to remove the faculty member you just added? Y/N "<<endl;
    else if(lastChoice == 10)
        cout<<"Are you sure you want to restore the faculty member you just deleted? Y/N "<<endl;
    else if(lastChoice == 11)
        cout<<"Are you sure you want to undo the advisor change you just made? Y/N "<<endl;
    else if(lastChoice ==12 || lastChoice == 13)
        cout<<"Are you sure you want to undo the advisee change you just made? Y/N "<<endl;
    else
    {
        cout<<"There was an error when trying to rollback. "<<endl;
        return;
    }

    cin>>ans;
    ans = toupper(ans);
    if(ans == 'N')
    {
        cout<<"Rollback cancelled. "<<endl;
        return;
    }
    else if(ans == 'Y')
    {
        cout<<"Rollback completed. "<<endl;
    }
    else
    {
        cout<<"That entry was not a 'Y' or an 'N'. Rollback cancelled."<<endl;
        return;
    }
    masterStudent = new BST<Student>(); //creates an empty tree
    masterFaculty = new BST<Faculty>();

    masterStudent->root = masterStudent->duplicateStudentTree(rollStudent->pop()->root); //assigns root of the new tree to the root returned by the stack
    masterFaculty->root = masterFaculty->duplicateFacultyTree(rollFaculty->pop()->root);

}

void rollPush()
{
    BST<Student>* s_rollTree = new BST<Student>();
    BST<Faculty>* f_rollTree = new BST<Faculty>();
    s_rollTree->root = s_rollTree->duplicateStudentTree(masterStudent->root);
    f_rollTree->root = f_rollTree->duplicateFacultyTree(masterFaculty->root);
    rollStudent->push(s_rollTree);
    rollFaculty->push(f_rollTree);
}

void rollPop()
{
    rollStudent->pop();
    rollFaculty->pop();
}
