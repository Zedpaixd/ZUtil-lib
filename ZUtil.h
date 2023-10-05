#ifndef ZUtil_H_
#define ZUtil_H_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <iostream>


namespace ZUtil{

template<typename T>
struct  Node {
    T data;
    Node *prev, *next;
    Node (char d, Node *p, Node *n): data(d), prev(p), next(n)
    {
        if(p) prev->next = this;
        if(n) next->prev = this;
    }
};

template<typename T>
class Clist
{
    public:
        Clist(T);
        virtual ~Clist();
        Node<T> *head;                                                              // current node that is being pointed to
        int size;                                                                   // number of elements in the circular linked list
        bool isEmpty();                                                             // size > 0
        void addNodeBefore(T, bool debug = false);                                  // inserted before head
        void addNodeAfter(T, bool debug = false);                                   // inserted after head
        void addNodeBeforeData(T, Node<T>*);                                        // (TODO) same as above, inserted before a specific node
        void addNodeAfterData(T, Node<T>*);                                         // (TODO) same as above, inserted after a specific node
        void print(bool);                                                           // prints the list, true starts from beginning, false starts from end
        void setData(T);                                                            // sets data
        void setPrev(Node<T>*);                                                     // sets previous
        void setNext(Node<T>*);                                                     // sets next
        bool findData(T, bool DEBUG_print_count = false);                           // checks if the data exists
        void deleteData(T, bool all_occurrences = true, bool DEBUG = false);        // deletes data       DEFAULT: ALL occurrences
};

template<typename T>
Clist<T>::Clist(T data)
{
    head = new Node<T>(data, NULL, NULL);
    head->next = head->prev = head;
    size = 1;
}

template<typename T>
Clist<T>::~Clist()
{
    Node<T> *tmp = this->head;
    Node<T> *temp;
    while(tmp->prev)
        tmp = tmp->prev;
    while(tmp)
    {

        temp = tmp->next;
        delete tmp;
        tmp = temp;
    }
    tmp = temp = NULL;
}

template<typename T>
bool Clist<T>::isEmpty()
{
    return (this->size == 0);
}

template<typename T>
void Clist<T>::addNodeBefore(T data, bool debug)
{
    Node<T> *n = head;
    Node<T> *p = head->prev;

    Node<T> *temp = new Node<T>(data, p, n);
    size++;

    if(debug)
    std::cout << "added: " << temp->data << "  before: "
         << temp->prev->data << "  after: " << temp->next->data << std::endl;
}

template<typename T>
void Clist<T>::addNodeAfter(T data, bool debug)
{
    Node<T> *n = head->next;
    Node<T> *p = head;

    Node<T> *temp = new Node<T>(data, p, n);
    size++;
    
    if (debug)
    std::cout << "added: " << temp->data << "  before: "
         << temp->prev->data << "  after: " << temp->next->data << std::endl;

}

template<typename T>
void Clist<T>::print(bool dir)   // True to traverse next, false to traverse prev
{
    Node<T> *tmp = head;

    do{
        std::cout << tmp->data << " "; 
        tmp = dir ? tmp->next : tmp->prev;
    }while(tmp != head);
    
    std::cout << std::endl;
}

template<typename T>
void Clist<T>::setData(T Data)
{
    this->head->data = Data;
}

template<typename T>
void Clist<T>::setPrev(Node<T>* Prev)
{
    this->head->prev = Prev;
}

template<typename T>
void Clist<T>::setNext(Node<T>* Next)
{
    this->head->next = Next;
}

template<typename T>
bool Clist<T>::findData(T search, bool DEBUG_print_count)
{
    int counter = 0;
    Node<T> *tmp = head;
    while(tmp->next != head)
    {
        if(tmp->data == search)
            counter++;
        tmp = tmp->next;
    }

    if(DEBUG_print_count) std::cout << "'" << search << "' was found " << counter << " time(s)" << std::endl;
    
    return counter > 0;
}

template<typename T>
void Clist<T>::deleteData(T search, bool all_occurrences, bool DEBUG)
{                                                                                       
    Node<T> *tmp = head;
    int ctr = 0;

    while(tmp && ctr < size)
    {
        if(tmp->data == search)
        {
            if (DEBUG) std::cout << "Deleting " << tmp->data << std::endl;

            // Handle deleting the head node
            if(tmp == head)
            {
                // If there is more than one node, update head and fix links
                if(head->next != head)
                {
                    head = head->next;
                    head->prev = tmp->prev;
                    tmp->prev->next = head;
                }
                else // Only one node, so list becomes empty
                {
                    head = nullptr;
                }
            }
            else // Deleting non-head node
            {
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
            }
            
            Node<T>* toDelete = tmp;
            tmp = tmp->next; // Move to the next node before deleting current
            delete toDelete; // Free the memory
            size--; // Decrease the size of the list

            if (!all_occurrences)
                return;
        }
        else
        {
            tmp = tmp->next; // If not deleting, move to the next node
        }

        ctr++;
    }
}
}

#endif