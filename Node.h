// Veniamin Velikoretskikh veniamin@pdx.edu
// CS302 Karla Fant - Program #2
// Template Node and DLL classes for managing obstacles

#include <iostream>
using namespace std;

template <typename Type>
class Node_DLL
{
public:
    Type data;
    Node_DLL<Type> * next;
    Node_DLL<Type> * prev;

    Node_DLL(const Type & obj) : data(obj), next(nullptr), prev(nullptr) {}
};

template <typename Type>
class DLL
{
public:
    DLL();
    DLL(const DLL<Type> & src);
    DLL<Type> & operator=(const DLL<Type> & src);
    ~DLL();

    bool insert_back(const Type & obj);
    bool remove_by_name(const char * name);
    bool display_all() const;
    const Type * retrieve_by_name(const char * name) const;
    bool clear_list();

private:
    Node_DLL<Type> * head;
    Node_DLL<Type> * tail;

    bool insert_back_recursive(Node_DLL<Type> *& node, const Type & obj);
    bool remove_recursive(Node_DLL<Type> *& node, const char * name);
    bool display_recursive(Node_DLL<Type> * node) const;
    const Type * retrieve_recursive(Node_DLL<Type> * node, const char * name) const;
    bool copy_recursive(Node_DLL<Type> *& dest, Node_DLL<Type> * src);
    bool clear_recursive(Node_DLL<Type> *& node);
};

