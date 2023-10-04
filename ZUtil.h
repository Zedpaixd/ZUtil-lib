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
    public:
        Clist(char);
        virtual ~Clist();
        Node *head;     // current node that is being pointed to
        int size;
        bool isEmpty();
        void addNodeBefore(char, int);           // inserted before head
        void addNodeAfter(char, int);            // inserted after head
        void addNodeBeforeData(char, Node*);// Same as above, inserted before/after a specific node
        void addNodeAfterData(char, Node*);
        void out(bool);     // Prints the list, true starts from beginning, false starts from end
        void setData(char);
        void setPrev(Node*);
        void setNext(Node*);
        bool findData(char);    // Searches through the list to find the char
        void deleteData(char, bool);

};

Clist::Clist(char d)
{
    head = new Node(d, NULL, NULL);
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
{   return (this->size == 0);}

void Clist::addNodeBefore(char d, int debug = 0)
{
    Node *n = head;
    Node *p = head->prev;

    Node *temp = new Node (d, p, n);
    size++;

    if(debug)
    cout << "added: " << temp->data << "  before: "
          << temp->prev->data << "  after: " << temp->next->data << endl;

}
void Clist::addNodeAfter(char d, int debug = 0)
{
    Node *n = head->next;
    Node *p = head;

    Node *temp = new Node (d, p, n);
    size++;
    
    if (debug)
    cout << "added: " << temp->data << "  before: "
         << temp->prev->data << "  after: " << temp->next->data << endl;

}
void Clist::out(bool dir)   // True to traverse next, false to traverse prev
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
bool Clist::findData(char search)
{
    int counter = 0;
    Node *tmp = head;
    while(tmp->next != head)
    {
        if(tmp->data == search)
            counter++;
        tmp = tmp->next;
    }

    if (counter > 0)
    {
        cout << "'" << search << "' was found " << counter << " time(s)" << endl;
        return true;
    }else
    {
        cout << "'" << search << "' was not found" << endl;
        return false;
    }
}

void Clist::deleteData(char search, bool all)   // If true, it will delete all nodes with the same search
{                                               // If false, it will delete the first Node only
    Node *tmp = head;
    while(tmp)
    {
        if(tmp->data == search)
        {
            cout << "Deleting " << search << endl;
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            if (false)
                return;
        }
        tmp = tmp->next;

    }
}
}

#endif