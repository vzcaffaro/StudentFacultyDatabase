#include <iostream>
#include <string>
#include <iostream>

template <typename T>
class DoublyNode
{

public:
    T data;
    DoublyNode<T> *next;
    DoublyNode<T> *prev;

    DoublyNode();
    DoublyNode(T d);
    ~DoublyNode();
};




template <typename T>
DoublyNode<T>::DoublyNode()
{
    data = NULL;
    next = NULL;
    prev = NULL;
}
template <typename T>
DoublyNode<T>::DoublyNode(T d)
{
    data = d;
    next = NULL;
    prev = NULL;
}
template <typename T>
DoublyNode<T>::~DoublyNode()
{
    next = NULL;
    prev = NULL;
}
