#include <iostream>
#include <string.h>
#include "ZUtil.h"  // "..." -> local lib

using namespace std;
using namespace ZUtil;
/*
        int size;
        bool isEmpty();
        void addNodeBefore(char, int);           // inserted before head
        void addNodeAfter(char, int);            // inserted after head
        void addNodeBeforeData(char, Node*);     // Same as above, inserted before/after a specific node
        void addNodeAfterData(char, Node*);      // 
        void print(bool);                          // Prints the list, true starts from beginning, false starts from end
        void setData(char);
        void setPrev(Node*);
        void setNext(Node*);
        bool findData(char);    // Searches through the list to find the char
        void deleteData(char, bool);
*/


int main(int argc, char* argv[]){
    
    char s[] = "abcdecfgchc";

    Clist *list;
    Node *curr;
    list = new Clist(s[0]);

    for(size_t i=1; i < strlen(s); i++) // create the rest of the linked list
        list->addNodeBefore(s[i]);

    list->print(true);
    // list->findData('c', true);
    // cout<< list->size;
    // list->deleteData('c');
    list->print(true);


    return 0;
}