//Veniamin Velikoretskikh veniamin@pdx.edu
//This is the template implementation


// Constructor
template <typename Type>
DLL<Type>::DLL() : head(nullptr), tail(nullptr) {}

// Copy Constructor
template <typename Type>
DLL<Type>::DLL(const DLL<Type> & src) : head(nullptr), tail(nullptr)
{
    copy_recursive(head, src.head);
}

// Assignment
template <typename Type>
DLL<Type> & DLL<Type>::operator=(const DLL<Type> & src)
{
    if (this != &src)
    {
        clear_list();
        copy_recursive(head, src.head);
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
template <typename Type>
bool DLL<Type>::insert_back(const Type & obj)
{
    return insert_back_recursive(head, obj);
}

template <typename Type>
bool DLL<Type>::insert_back_recursive(Node_DLL<Type> *& node, const Type & obj)
{
    if (!node)
    {
        node = new Node_DLL<Type>(obj);
        if (!tail) tail = node;
        return true;
    }
    return insert_back_recursive(node->next, obj);
}
//-----------------------------------------------------------------------------
template <typename Type>
bool DLL<Type>::display_all() const
{
    return display_recursive(head);
}

template <typename Type>
bool DLL<Type>::display_recursive(Node_DLL<Type> * node) const
{
    if (!node) return false;
    node->data.display_info();
    return display_recursive(node->next);
}
//-----------------------------------------------------------------------------
template <typename Type>
const Type * DLL<Type>::retrieve_by_name(const char * name) const
{
    return retrieve_recursive(head, name);
}

template <typename Type>
const Type * DLL<Type>::retrieve_recursive(Node_DLL<Type> * node, const char * name) const
{
    if (!node) return nullptr;
    if (strcmp(node->data.get_name(), name) == 0)
        return &node->data;
    return retrieve_recursive(node->next, name);
}
//-----------------------------------------------------------------------------
template <typename Type>
bool DLL<Type>::remove_by_name(const char * name)
{
    return remove_recursive(head, name);
}

template <typename Type>
bool DLL<Type>::remove_recursive(Node_DLL<Type> *& node, const char * name)
{
    if (!node) return false;
    if (strcmp(node->data.get_name(), name) == 0)
    {
        Node_DLL<Type> * temp = node;
        node = node->next;
        delete temp;
        return true;
    }
    return remove_recursive(node->next, name);
}
//-----------------------------------------------------------------------------
template <typename Type>
bool DLL<Type>::clear_list()
{
    return clear_recursive(head);
}

template <typename Type>
bool DLL<Type>::clear_recursive(Node_DLL<Type> *& node)
{
    if (!node) return true;
    clear_recursive(node->next);
    delete node;
    node = nullptr;
    return true;
}
//-----------------------------------------------------------------------------
template <typename Type>
bool DLL<Type>::copy_recursive(Node_DLL<Type> *& dest, Node_DLL<Type> * src)
{
    if (!src) return true;
    insert_back(src->data);
    return copy_recursive(dest, src->next);
}


