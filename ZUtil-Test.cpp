#include <iostream>
#include <string.h>
#include "ZUtil.h"  // "..." -> local lib

using namespace std;
using namespace ZUtil;
/*
        int size;
        bool isEmpty();
        void addNodeEnd(char, int);           // inserted before head
        void addNodeAfterHead(char, int);            // inserted after head
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

    Clist<char> *list;
    Node<char> *curr;
    list = new Clist<char>(s[0]);

    for(size_t i=1; i < strlen(s); i++) // create the rest of the linked list
        list->addNodeEnd(s[i]);

    // list->print(true);
    // list->findData('c', true);
    // cout<< list->size << endl;
    // list->deleteData('a');
    list->print(true);

    list->addNodeEnd('z',list->head->next);
    list->print(true);

    // Clist<int> *listB;
    // Node<int> *currB;
    // listB = new Clist<int>(0);

    // for(size_t i=1; i < 25; i++) // create the rest of the linked list
    //     listB->addNodeEnd(i%5);

    // listB->print(true);
    // listB->findData(1, true);
    // cout<< listB->size << endl;
    // listB->deleteData(1);
    // listB->print(true);

    BinarySearchTree<int> *bst;
    bst = new BinarySearchTree<int>();
    bst->insert(1);
    bst->insert(9);
    bst->insert(5);
    bst->insert(2);
    bst->insert(7);
    cout<<bst->findMax();

    return 0;
}