#include <iostream>
#include "TreeNode.h"
#include "Student.h"
#include "Faculty.h"

using namespace std;


template <class T>
class BST
{
public:
    BST();
    ~BST();

    TreeNode<T> *root;

    TreeNode<T> * search(int value);
    void insert(T * object);
    bool deleteNode(T * object);

    //helper functions
    TreeNode<T> * getSuccessor(TreeNode<T> *d);
    TreeNode<T> * duplicateStudentTree(TreeNode<T> *copied);
    TreeNode<T> * duplicateFacultyTree(TreeNode<T> *copied);
    bool isEmpty();
    TreeNode<T> * getMin();
    TreeNode<T> * getMax();
    void printStudentTree();
    void printFacultyTree();
    void recStudentPrint(TreeNode<T> *node);
    void recFacultyPrint(TreeNode<T> *node);


};








template <class T>
BST<T>::BST()
{
    root = NULL; //empty tree
}



template <class T>
BST<T>::~BST()
{
    delete root;
}




template <class T>
TreeNode<T>* BST<T>::duplicateStudentTree(TreeNode<T> *copied) //recursive method used to create deep copies of trees for rollback
{
    TreeNode<T> * copyto;
    if(copied == NULL)
        copyto = NULL;
    else
    {
        copyto = new TreeNode<T>(copied->key, copied->value);
        copyto->left = duplicateStudentTree(copied->left);
        copyto->right = duplicateStudentTree(copied->right);
    }
    return copyto;
}

template <class T>
TreeNode<T>* BST<T>::duplicateFacultyTree(TreeNode<T> *copied) //recursive method used to create deep copies of trees
{
    TreeNode<T> * copyto;
    if(copied == NULL)
        copyto = NULL;
    else
    {
        copyto = new TreeNode<T>(copied->key, copied->value);
        DoublyLinkedList<int> * advisees = copied->value->advisees;
        DoublyNode<int> * curr = advisees->front;
        copyto->value->advisees = new DoublyLinkedList<int>();
        while(curr != NULL)
        {
            copyto->value->advisees->insertFront(curr->data);
            curr = curr->next;
        }
        copyto->left = duplicateFacultyTree(copied->left);
        copyto->right = duplicateFacultyTree(copied->right);
    }
    return copyto;
}


template <class T>
void BST<T>::recStudentPrint(TreeNode<T> *node)
{
    if(node==NULL)
        return;

    recStudentPrint(node->left);
    cout<< "ID:" << node->key <<endl;
    cout<<"Name: "<<node->value->name<<endl;
    cout<<"Class: "<<node->value->level<<endl;
    cout<<"Major: "<<node->value->major<<endl;
    cout<<"GPA: "<<node->value->gpa<<endl;
    cout<<"Advisor ID: "<<node->value->advisor<<endl<<endl;

    recStudentPrint(node->right);
}


template <class T>
void BST<T>::recFacultyPrint(TreeNode<T> *node)
{
    if(node==NULL)
        return;


    recFacultyPrint(node->left);

    cout<< "ID:" << node->key <<endl;
    cout<<"Name: "<<node->value->name<<endl;
    cout<<"Level: "<<node->value->level<<endl;
    cout<<"Department: "<<node->value->department<<endl;
    cout<<"Advisee IDs: "<<node->value->getAdvisees()<<endl<<endl;

    recFacultyPrint(node->right);
}




template <class T>
void BST<T>::printStudentTree()
{
    if(root == NULL)
    {
        cout<<"The tree is empty, so no information could be printed"<<endl;
        return;
    }
    recStudentPrint(root);
}

template <class T>
void BST<T>::printFacultyTree()
{
    if(root == NULL)
    {
        cout<<"The tree is empty, so no information could be printed"<<endl;
        return;
    }
    recFacultyPrint(root);
}

template <class T>
TreeNode<T> * BST<T>::getMax()
{
    TreeNode<T> *current = root;

    if(current==NULL)
        return NULL;

    while(current->right != NULL)
    {
        current = current -> right;
    }

    return current;

}

template <class T>
TreeNode<T> * BST<T>::getMin()
{
    TreeNode<T> *current = root;

    if(current==NULL)
        return NULL;

    while(current->left != NULL)
    {
        current = current -> left;
    }

    return current;

}

template <class T>
void BST<T>::insert(T * object)
{
    int value = object->getID();
    TreeNode<T> *node = new TreeNode<T>(value , object);


    if(root==NULL)
    {
        root = node;
    }
    else
    {
        TreeNode<T> *current = root;
        TreeNode<T> *parent = NULL;

        while(true)
        {
            parent = current;

            if(value < current->key)
            {
                current = current->left;
                if(current==NULL)
                {
                    parent->left = node;
                    break;
                }
            }
            if(value > current->key)
            {
                current = current->right;
                if(current==NULL)
                {
                    parent->right = node;
                    break;
                }
            }
        }
    }
}

template <class T>
TreeNode<T> * BST<T>::search(int value)
{
    TreeNode<T> *current = root;

    if(root==NULL)
        return NULL;
    else
    {
        while(current->key != value) //while we havent found the node
        {
            if(value < current->key)
                current = current->left; //go left is value is smaller
            else if(value > current -> key)
                current = current ->right; //go right if value is greater

            if(current == NULL)
                return NULL;

        }
    }
    return current;
}

template <class T>
bool BST<T>::deleteNode(T * object)
{
    int value = object->getID();

    if(root==NULL)
        return false;

    TreeNode<T> *current = root;
    TreeNode<T> *parent = root;
    bool isLeft = true;


    while(current->key != value)
    {
        parent = current;
        if(value < current->key)
        {
            isLeft=true;
            current = current->left;
        }
        else if(value > current -> key)
        {
            isLeft=false;
            current = current ->right;
        }

        if(current == NULL)
            return false;

    }
    //we found the node
    //check if it's a leaf
    if(current->left==NULL && current->right==NULL)
    {
        if (current == root)
            root=NULL;
        else if(isLeft)
            parent->left=NULL;
        else
            parent->right=NULL;
    }

    //deleting exterior nodes, check whether child is left or right

    else if(current->right == NULL)
    {
        if(current==root)
            root = current->left;
        else if(isLeft)
            parent->left = current->left;
        else
            parent->right = current->left;
    }
    else if(current->left == NULL)
    {
        if(current==root)
            root = current->right;
        else if(isLeft)
            parent->left = current->right;
        else
            parent->right = current->right;
    }

    else //node is an interior node
    {
        TreeNode<T> *successor = getSuccessor(current);

        if(current==root)
            root=successor;
        else if(isLeft)
            parent->left = successor;
        else
            parent->right = successor;

        successor->left = current->left;

    }
    return true;


}

template <class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d) //d is node to be deleted
{
    TreeNode<T> *sp = d; //successor's parent is at d
    TreeNode<T> *successor = d;
    TreeNode<T> *current = d->right;

    while(current != NULL)
    {
        sp = successor;
        successor=current;
        current=current->left;
    }

    if(successor != d->right)
    {
        sp->left = successor->right;
        successor->right=d->right;
    }
    return successor;

}
