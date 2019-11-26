#include <iostream>

using namespace std;

template<class T>
class TreeNode
{
public:
    TreeNode();
    TreeNode(int id , T * object); //id = key
    ~TreeNode(); //when creating a template class, desctructor must be virtual

    int key;
    T * value; //pointer to the object the node holds (Student/Faculty)
    TreeNode *left;
    TreeNode *right;
};



template<class T>
TreeNode<T>::TreeNode()
{
    key = 0;
    left = NULL;
    right = NULL;
}

template<class T>
TreeNode<T>::TreeNode(int id , T * object)
{
    key = id;
    value = object;
    left = NULL;
    right = NULL;
}

template<class T>
TreeNode<T>::~TreeNode()
{
    delete left;
    delete right;
    delete key;
}
