#ifndef ZUtil_H_
#define ZUtil_H_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

using namespace std;


namespace ZUtil{

struct  Node {
    char data;
    Node *prev, *next;
    Node (char d, Node *p, Node *n): data(d), prev(p), next(n)
    {
        if(p) prev->next = this;
        if(n) next->prev = this;
    }
};

class Clist
{
    public:                                       // TODO: Make generic
        Clist(char);
        virtual ~Clist();
        Node *head;                               // current node that is being pointed to
        int size;                                 // number of elements in the circular linked list
        bool isEmpty();                           // size > 0
        void addNodeBefore(char, bool);           // inserted before head
        void addNodeAfter(char, bool);            // inserted after head
        void addNodeBeforeData(char, Node*);      // (TODO) same as above, inserted before a specific node
        void addNodeAfterData(char, Node*);       // (TODO) same as above, inserted after a specific node
        void print(bool);                         // prints the list, true starts from beginning, false starts from end
        void setData(char);                       // sets data
        void setPrev(Node*);                      // sets previous
        void setNext(Node*);                      // sets next
        bool findData(char, bool);                // checks if the data exists
        void deleteData(char, bool, bool);        // deletes data       DEFAULT: ALL occurrences
};

Clist::Clist(char data)
{
    head = new Node(data, NULL, NULL);
    head->next = head->prev = head;
    size = 1;
}

Clist::~Clist()
{
    Node *tmp = this->head;
    Node *temp;
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

bool Clist::isEmpty()
{
    return (this->size == 0);
}

void Clist::addNodeBefore(char data, bool debug = false)
{
    Node *n = head;
    Node *p = head->prev;

    Node *temp = new Node (data, p, n);
    size++;

    if(debug)
    cout << "added: " << temp->data << "  before: "
         << temp->prev->data << "  after: " << temp->next->data << endl;
}

void Clist::addNodeAfter(char data, bool debug = false)
{
    Node *n = head->next;
    Node *p = head;

    Node *temp = new Node (data, p, n);
    size++;
    
    if (debug)
    cout << "added: " << temp->data << "  before: "
         << temp->prev->data << "  after: " << temp->next->data << endl;

}

void Clist::print(bool dir)   // True to traverse next, false to traverse prev
{
    Node *tmp = head;

    do{
        cout << tmp->data << " "; 
        tmp = dir ? tmp->next : tmp->prev;
    }while(tmp != head);
    
    cout << endl;
}

void Clist::setData(char Data)
{
    this->head->data = Data;
}

void Clist::setPrev(Node* Prev)
{
    this->head->prev = Prev;
}

void Clist::setNext(Node* Next)
{
    this->head->next = Next;
}

bool Clist::findData(char search, bool DEBUG_print_count = false)
{
    int counter = 0;
    Node *tmp = head;
    while(tmp->next != head)
    {
        if(tmp->data == search)
            counter++;
        tmp = tmp->next;
    }

    if(DEBUG_print_count) cout << "'" << search << "' was found " << counter << " time(s)" << endl;
    
    return counter > 0;
}

void Clist::deleteData(char search, bool all_occurrences = true, bool DEBUG = false)     // If true, it will delete all nodes with the same search
{                                                                                        // If false, it will delete the first Node only
    Node *tmp = head;
    int ctr = 0;

    while(tmp)
    {
        if(tmp->data == search)
        {
            if (DEBUG) cout << "Deleting " << tmp->data << endl;

            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            
            if (!all_occurrences)
                return;
        }

        tmp = tmp->next;
        ctr++;

        if (ctr > size)
           return;

    }
}
}

#endif