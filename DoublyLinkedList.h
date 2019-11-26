#include "DoublyNode.h"
#include <string>
#include <iostream>
#include <unistd.h>

using namespace std;

template <typename T>
class DoublyLinkedList
{
public:
        DoublyNode<T> *front;
        DoublyNode<T> *back;
        unsigned int size;

        DoublyLinkedList();
        ~DoublyLinkedList();

        void insertBack(T d);
        void insertFront(T d);
        T removeFront();
        bool remove(T id);
        bool isEmpty();
        T peek();

};


template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
    size=0;
    front=NULL;
    back=NULL;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    DoublyNode<T> *curr = front;
	while (curr != NULL)
	{
		DoublyNode<T> *garbage = curr;
		curr = curr->next;
		curr->prev = NULL;
		delete garbage;
	}
	curr = NULL;
	delete front;
	delete back;

    cout << "object deleted" << endl;
}


template <typename T>
T DoublyLinkedList<T>::removeFront()
{
    if(size==0)
    {
        cout<<"Cannot remove from an empty list"<<endl;
        throw -1;
    }

    DoublyNode<T> *ft = front;

    if(front == back)
    {
        back = NULL;
    } else {
        front->next->prev = NULL;
    }
    T temp = front->data;
    front = front->next;
    ft->next = NULL;
    delete ft;
    size--;

    return temp;

}



template <typename T>
bool DoublyLinkedList<T>::remove(T id)
{
    if(size==0)
    {
        cout<<"Cannot remove from an empty list"<<endl;
        throw -1;
    }

    DoublyNode<T> *curr = front;


    while(curr->data != id)
    {
        if(curr==NULL)
        {
            return false;
        }
        curr=curr->next;
    }

    if(curr == front)
    {
        front = curr -> next;
        front->prev = NULL;
    }
    else if (curr == back)
    {
        back = curr -> prev;
        back->next = NULL;
    }
    else
    {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }

    curr->next=NULL;
    curr->prev=NULL;
    size--;
    //delete curr;

    return true;

}

template <typename T>
T DoublyLinkedList<T>::peek()
{
    return front->data;
}

template <typename T>
void DoublyLinkedList<T>::insertBack(T d)
{
    DoublyNode<T> *node = new DoublyNode<T>(d);
    if(size==0)
    {
        front = node;
    } else {
        node->prev=back;
        back->next=node;
    }
    back=node;
    ++size;

}

template <typename T>
void DoublyLinkedList<T>::insertFront(T d)
{
    DoublyNode<T> *node = new DoublyNode<T>(d);
    if(size==0)
    {
        back = node;
    } else {
        node->next=front;
        front->prev=node;
    }
    front=node;
    ++size;

}


template <typename T>
bool DoublyLinkedList<T>::isEmpty()
{
    if(size==0)
        return true;
    else
        return false;
}
