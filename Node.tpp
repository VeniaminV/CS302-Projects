//Veniamin Velikoretskikh veniamin@pdx.edu


/*
This is the template implementation for the DLL rucusive operations
These function will work independent of the variable type. I't won't matter
if we work with an adult or teen or kids object it will treat it the same. 

We will insert, display, retrive, remove , clear, copy

*/


// Constructor
template <typename Type>
DLL<Type>::DLL() : head(nullptr), tail(nullptr) {}

// Copy Constructor
template <typename Type>
DLL<Type>::DLL(const DLL<Type> & src) : head(nullptr), tail(nullptr)
{
    copy_recursive(src.head);
}

// Assignment
template <typename Type>
DLL<Type> & DLL<Type>::operator=(const DLL<Type> & src)
{
    if (this != &src)
    {
        clear_list();
        copy_recursive(src.head);
    }
    return *this;
}

// Destructor
template <typename Type>
DLL<Type>::~DLL()
{
    clear_list();
}
//-----------------------------------------------------------------------------
// Insert back (public)
template <typename Type>
bool DLL<Type>::insert_back(const Type & obj)
{
    return insert_back_recursive(head, obj);
}

// Recursive insert_back
template <typename Type>
bool DLL<Type>::insert_back_recursive(Node_DLL<Type> *& current, const Type & obj)
{
    if (!current)
    {
        current = new Node_DLL<Type>(obj);
        if (!head) head = current;
        tail = current;
        return true;
    }
    return insert_back_recursive(current->next, obj);
}
//-----------------------------------------------------------------------------
// Display all (public)
template <typename Type>
bool DLL<Type>::display_all() const
{
    return display_recursive(head);
}

// Recursive display
template <typename Type>
bool DLL<Type>::display_recursive(Node_DLL<Type> * current) const
{
    if (!current) return false;
    current->data.display_info();
    display_recursive(current->next);
    return true;
}
//-----------------------------------------------------------------------------
// Retrieve by name (public)
template <typename Type>
const Type * DLL<Type>::retrieve_by_name(const char * name) const
{
    return retrieve_recursive(head, name);
}

// Recursive retrieve
template <typename Type>
const Type * DLL<Type>::retrieve_recursive(Node_DLL<Type> * current, const char * name) const
{
    if (!current) return nullptr;
    const char * n = current->data.get_name();
    if (n && name && strcmp(n, name) == 0)
        return &current->data;
    return retrieve_recursive(current->next, name);
}
//-----------------------------------------------------------------------------
// Remove by name (public)
template <typename Type>
bool DLL<Type>::remove_by_name(const char * name)
{
    return remove_recursive(head, name);
}

// Recursive remove
template <typename Type>
bool DLL<Type>::remove_recursive(Node_DLL<Type> *& current, const char * name)
{
    if (!current) return false;

    if (strcmp(current->data.get_name(), name) == 0)
    {
        Node_DLL<Type>* temp = current;
        current = current->next;
        delete temp;
        if (!current) tail = nullptr;
        return true;
    }
    return remove_recursive(current->next, name);
}
//-----------------------------------------------------------------------------
// Clear list (public)
template <typename Type>
bool DLL<Type>::clear_list()
{
    return clear_recursive(head);
}

// Recursive clear
template <typename Type>
bool DLL<Type>::clear_recursive(Node_DLL<Type> *& current)
{
    if (!current) return true;
    clear_recursive(current->next);
    delete current;
    current = nullptr;
    tail = nullptr;
    return true;
}
//-----------------------------------------------------------------------------
// Copy recursive helper
template <typename Type>
bool DLL<Type>::copy_recursive(Node_DLL<Type> * src)
{
    if (!src) return true;
    insert_back(src->data);
    return copy_recursive(src->next);
}

