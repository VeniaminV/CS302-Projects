// Veniamin Velikoretskikh veniamin@pdx.edu
// CS302 Karla Fant - Program #2
// Template Node and DLL classes for managing obstacles

/*
We have the Node class that has the data the pointers
We have the DLL class that will manage the DLL's recursevly
All of these functions are in a template so it won't matter which 
object we are working with. 
*/

#include <iostream>
using namespace std;

template <typename Type>
class Node_DLL
{
public:
    Type data;
    Node_DLL<Type>* next;
    Node_DLL<Type>* prev;

    Node_DLL() : data(), next(nullptr), prev(nullptr) {}
    Node_DLL(const Type& obj) : data(obj), next(nullptr), prev(nullptr) {}
};

template <typename Type>
class DLL
{
public:
    DLL();
    DLL(const DLL<Type>& src);
    DLL<Type>& operator=(const DLL<Type>& src);
    ~DLL();
//insert object at end of list
    bool insert_back(const Type& obj);
//remove item by name
    bool remove_by_name(const char* name);
//displays all
    bool display_all() const;
//Returns pointer to the item if found or nullptr if not found
    const Type* retrieve_by_name(const char* name) const;
//clears teh list 
    bool clear_list();

    Node_DLL<Type>* get_head() const { return head; }

private:
    Node_DLL<Type>* head;
    Node_DLL<Type>* tail;

//helper functions for recursion
    bool insert_back_recursive(Node_DLL<Type>*& current, const Type& obj);
    bool remove_recursive(Node_DLL<Type>*& current, const char* name);
    bool display_recursive(Node_DLL<Type>* current) const;
    const Type* retrieve_recursive(Node_DLL<Type>* current, const char* name) const;
    bool copy_recursive(Node_DLL<Type>* src);
    bool clear_recursive(Node_DLL<Type>*& current);
};

#include "Node.tpp"
