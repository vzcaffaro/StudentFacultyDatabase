#include <iostream>
//stack used for storing primitives, in this case an int for previous choice
using namespace std;

template <typename T>
class ChoiceStack
{
    public:
    ChoiceStack(); //constructor
    ChoiceStack(int maxSize); //overloaded constructor
    ~ChoiceStack(); //destructor

    void push(T d);
    T pop();
    T peek(); //aka top()

    bool isFull();
    bool isEmpty();

    int size;
    int top;

    T * myArray;


};


template <typename T>
ChoiceStack<T>::ChoiceStack() //default constructor
{
    myArray = new T[128];
    size = 128;
    top = -1;
    for(int i = 0; i<size;++i)
        myArray[i] = -1;
}

template <typename T>
ChoiceStack<T>::ChoiceStack(int maxSize)
{
    myArray = new T[maxSize];
    size = maxSize;
    top = -1;
    for(int i = 0; i<size;++i)
        myArray[i] = -1;
}

template <typename T>
ChoiceStack<T>::~ChoiceStack()
{}

template <typename T>
void ChoiceStack<T>::push(T d)
{
    if(isFull())
    {
        top = -1;
    }
    myArray[++top] = d;

}

template <typename T>
T ChoiceStack<T>::pop()
{
    if(isEmpty())
    {
        cout<<"You can't remove an object from an empty stack. "<<endl;
        return -1;
    }
    else if(top == -1 && myArray[size-1] != -1)
    {
        top = size - 1;
    }
    T temp = myArray[top--];
    myArray[top+1] = -1;
    return temp;

}

template <typename T>
T ChoiceStack<T>::peek()
{
    if(isEmpty())
    {
        cout<<"You can't peek an object from an empty stack. "<<endl;
        return -1;
    }
    else if(top == -1 && myArray[size-1] != -1)
    {
        return myArray[size-1];
    }
    else{
        return myArray[top];
    }
}

template <typename T>
bool ChoiceStack<T>::isFull()
{
    return (top == size-1);
}

template <typename T>
bool ChoiceStack<T>::isEmpty()
{
    return (top == -1 && myArray[size-1] == -1);
}
