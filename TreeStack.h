#include <iostream>
//stack used for storing objects, in this case instances of trees

using namespace std;

template <class T>
class TreeStack
{
    public:
    TreeStack(); //constructor
    TreeStack(int maxSize); //overloaded constructor
    ~TreeStack(); //destructor

    void push(T * d);
    T * pop();
    T * peek(); //aka top()

    bool isFull();
    bool isEmpty();

    int size;
    int top;

    T ** myArray;


};


template <class T>
TreeStack<T>::TreeStack() //default constructor
{
    myArray = new T*[128];
    size = 128;
    top = -1;
    for(int i = 0; i<size;++i)
        myArray[i] = NULL;
}

template <class T>
TreeStack<T>::TreeStack(int maxSize)
{
    myArray = new T*[maxSize];
    size = maxSize;
    top = -1;
    for(int i = 0; i<size;++i)
        myArray[i] = NULL;
}

template <class T>
TreeStack<T>::~TreeStack()
{}

template <class T>
void TreeStack<T>::push(T * d)
{
    if(isFull())
    {
        top = -1;
    }
    myArray[++top] = d;

}

template <class T>
T * TreeStack<T>::pop()
{
    if(isEmpty())
    {
        cout<<"You can't remove an object from an empty stack. "<<endl;
        return NULL;
    }
    else if(top == -1 && myArray[size-1] != NULL)
    {
        top = size - 1;
    }
    T * temp = myArray[top--];
    myArray[top+1] = NULL;
    return temp;

}

template <class T>
T * TreeStack<T>::peek()
{
    if(isEmpty())
    {
        cout<<"You can't peek an object from an empty stack. "<<endl;
        return NULL;
    }
    else if(top == -1 && myArray[size-1] != NULL)
    {
        return myArray[size-1];
    }
    else{
        return myArray[top];
    }
}

template <class T>
bool TreeStack<T>::isFull()
{
    return (top == size-1);
}

template <class T>
bool TreeStack<T>::isEmpty()
{
    return (top == -1 && myArray[size-1] == NULL);
}
