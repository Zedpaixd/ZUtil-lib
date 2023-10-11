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
        Clist(T data)
        {
            head = new Node<T>(data, NULL, NULL);
            head->next = head->prev = head;
            size = 1;
        }
        virtual ~Clist() 
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
        
        Node<T> *head;                                                              // current node that is being pointed to
        int size;                                                                   // number of elements in the circular linked list
        bool isEmpty()                                                              // size > 0
        {
            return (this->size == 0);
        }                                                             
        void addNodeEnd(T data, bool debug = false)                                      // inserted node before head / at end
        {
            Node<T> *n = head;
            Node<T> *p = head->prev;

            Node<T> *temp = new Node<T>(data, p, n);
            size++;

            if(debug)
            std::cout << "added: " << temp->data << "  before: "
                << temp->prev->data << "  after: " << temp->next->data << std::endl;
        }
        void addNodeAfterHead(T data, bool debug = false)                                // inserted after head
        {
            Node<T> *n = head->next;
            Node<T> *p = head;

            Node<T> *temp = new Node<T>(data, p, n);
            size++;
            
            if (debug)
            std::cout << "added: " << temp->data << "  before: "
                << temp->prev->data << "  after: " << temp->next->data << std::endl;

        }
        void addNodeBeforeData(T data, Node<T> *node)                                         // (BROKEN) same as above, inserted before a specific node
        {
            
            if(!node) {
                std::cerr << "Provided node is null!" << std::endl;
                return;
            }

            Node<T>* newNode = new Node<T>(data, node->prev, node);


            if(node->prev) {
                node->prev->next = newNode;
            }
            else {
                head = newNode;
            }

            node->prev = newNode;
            
            size++; 
        }
        void addNodeAfterData(T data, Node<T> *node)                                          // same as above, inserted after a specific node
        {

            if(!node) {
                std::cerr << "Provided node is null!" << std::endl;
                return;
            }

            Node<T>* newNode = new Node<T>(data, node, node->next);

            if(node->next) {
                node->next->prev = newNode;
            }
            
            node->next = newNode;
            
            size++;
        }
        void print(bool dir)                                                            // prints the list, true starts from beginning, false starts from end
        {
            if(!head) return;  // If the list is empty

            Node<T>* current = head;
            do {
                std::cout << current->data << " ";
                current = current->next;
            } while(current && current != head);  // Break loop if back to head
            std::cout << std::endl;
        }
        void setData(T Data)                                                             // sets data
        {
            this->head->data = Data;
        }
        void setPrev(Node<T> *Prev)                                                      // sets previous
        {
            this->head->prev = Prev;
        }
        void setNext(Node<T> *Next)                                                      // sets next
        {
            this->head->next = Next;
        }
        bool findData(T search, bool DEBUG_print_count = false)                            // checks if the data exists
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
        void deleteData(T search, bool all_occurrences = true, bool DEBUG = false)         // deletes data       DEFAULT: ALL occurrences
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
};

template<typename T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(T val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, const T& data) 
    {
        if (node == nullptr) {
            node = new Node(data);
        } else if (data < node->data) {
            insert(node->left, data);
        } else {
            insert(node->right, data);
        }
    }

    Node* search(Node* node, const T& data) const 
    {
        if (node == nullptr || node->data == data) {
            return node;
        }
        if (data < node->data) {
            return search(node->left, data);
        }
        return search(node->right, data);
    }

    Node* findMin(Node* node) const 
    {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* findMax(Node* node) const 
    {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    Node* deleteNode(Node*& node, const T& data) 
    {
        if (node == nullptr) return node;

        if (data < node->data) {
            node->left = deleteNode(node->left, data);
        } else if (data > node->data) {
            node->right = deleteNode(node->right, data);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

    // Additional traversal helper methods
    void inOrder(Node* node) const 
    {
        if (node != nullptr) {
            inOrder(node->left);
            std::cout << node->data << " ";
            inOrder(node->right);
        }
    }

    void preOrder(Node* node) const 
    {
        if (node != nullptr) {
            std::cout << node->data << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void postOrder(Node* node) const 
    {
        if (node != nullptr) {
            postOrder(node->left);
            postOrder(node->right);
            std::cout << node->data << " ";
        }
    }

    // Cleanup memory
    void deleteTree(Node* node) 
    {
        if (node == nullptr) return;

        deleteTree(node->left);
        deleteTree(node->right);

        delete node;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    virtual ~BinarySearchTree() 
    {
        deleteTree(root);
    }

    void insert(const T& data) 
    {
        insert(root, data);
    }

    bool search(const T& data) const 
    {
        return search(root, data) != nullptr;
    }

    void deleteNode(const T& data) 
    {
        root = deleteNode(root, data);
    }

    T findMin() const 
    {
        Node* node = findMin(root);
        if (node == nullptr) throw std::runtime_error("Tree is empty");
        return node->data;
    }

    T findMax() const 
    {
        Node* node = findMax(root);
        if (node == nullptr) throw std::runtime_error("Tree is empty");
        return node->data;
    }

    // Public traversal methods
    void inOrder() const { inOrder(root); }
    void preOrder() const { preOrder(root); }
    void postOrder() const { postOrder(root); }

    // Note: Implementing `findNext` and `findPrevious` may require additional methods or data structures (e.g., parent pointer, stack, etc.)
};


}
#endif