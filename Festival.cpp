/*
Veniamin Velikoretskikh veniamin@pdx.edu
Karla Fant cs302 fall 2025 programing assingment 1. 

This file will contain the implementations for the constructor, copy constructor,
assignment operator, destructor and the needed function in the prototypes,
 for the Vendor class and its 3 derived classes. 
*/

#include "Festival.h"
#include <cstring>
#include <iostream>
using namespace std;

// Vendor
//---------------------------------------------------------------------------------------------
Vendor::Vendor(const char * name) : name(nullptr)
{
    set_name(name);
}

Vendor::Vendor(const Vendor & src) : name(nullptr)
{
    set_name(src.name);
}

Vendor & Vendor::operator=(const Vendor & src)
{
    if (this == &src) return *this;
    clear_name();
    set_name(src.name);
    return *this;
}

Vendor::~Vendor()
{
    clear_name();
}

// Private helpers
//Safely updates vendors name, because it's dynamically allocated. 
bool Vendor::set_name(const char * src)
{
    if (!src) return false;
    name = new char[strlen(src) + 1];
    strcpy(name, src);
    return true;
}
//deletes name and sets it to nullptr
bool Vendor::clear_name()
{
    delete [] name;
    name = nullptr;
    return true;
}



// TrinketVendor
//---------------------------------------------------------------------------------------------
TrinketVendor::TrinketVendor() : Vendor(""), signature_item(nullptr)
{}

TrinketVendor::TrinketVendor(const char * vendorName, const char * sigItem)
    : Vendor(vendorName), signature_item(nullptr)
{
    set_signature(sigItem);
}

TrinketVendor::TrinketVendor(const TrinketVendor & src)
    : Vendor(src), signature_item(nullptr), inventory(src.inventory)
{
    set_signature(src.signature_item);
}

TrinketVendor & TrinketVendor::operator=(const TrinketVendor & src)
{
    if (this == &src) return *this;
    Vendor::operator=(src);
    clear_signature();
    set_signature(src.signature_item);
    inventory = src.inventory;
    return *this;
}

TrinketVendor::~TrinketVendor()
{
    clear_signature();
}

// Private helpers
//Safely updates signature item, because it's dynamically allocated. 
bool TrinketVendor::set_signature(const char * s)
{
    if (!s) return false;
    signature_item = new char[strlen(s) + 1];
    strcpy(signature_item, s);
    return true;
}
//Deletes signature item and sets it to nullptr.
bool TrinketVendor::clear_signature()
{
    delete [] signature_item;
    signature_item = nullptr;
    return true;
}

//adds trinket vendors
bool TrinketVendor::add_item(const string & itemName, float price)
{
    inventory.push_back(make_pair(itemName, price));
    return true;
}

bool TrinketVendor::list_item() const
{
    return list_item_recursive(0);
}

bool TrinketVendor::list_item_recursive(size_t index) const
{
    if (index >= inventory.size()) return false;
    cout << " - " << inventory[index].first << " ($" << inventory[index].second << ")\n";
    return list_item_recursive(index + 1) || true;
}

bool TrinketVendor::sell_item(const string & itemName)
{
    return sell_item_recursive(itemName, 0);
}

bool TrinketVendor::sell_item_recursive(const string & itemName, size_t index)
{
    if (index >= inventory.size()) return false;
    if (inventory[index].first == itemName)
    {
        inventory.erase(inventory.begin() + index);
        return true;
    }
    return sell_item_recursive(itemName, index + 1);
}



// CuisineVendor
//------------------------------------------------------------------------------------------------
CuisineVendor::CuisineVendor(const char * name, const vector<string> & items)
    : Vendor(name)//, menu(items)
{}

CuisineVendor::~CuisineVendor()
{}

bool CuisineVendor::show_menu() const
{
    if (menu.empty()) 
    {
        cout << "No menu items available." << endl;
        return false;
    }

    cout << "Menu for " << get_name() << ":" << endl;
    for (size_t i = 0; i < menu.size(); ++i)
        cout << " - " << menu[i] << endl;

    return true;
}

// Take an order recursively
bool CuisineVendor::take_order(const string & food) const
{
    return take_order_recursive(food, 0);
}

bool CuisineVendor::take_order_recursive(const string & food, size_t index) const
{
    if (index >= menu.size())
    {
        cout << "Sorry, " << food << " is not on the menu." << endl;
        return false;
    }

    if (menu[index] == food)
    {
        cout << "Order placed for " << food << "!" << endl;
        return true;
    }

    return take_order_recursive(food, index + 1);
}

// Recommend the first item on the menu
bool CuisineVendor::recommend_item() const
{
    if (menu.empty())
    {
        cout << "No items to recommend." << endl;
        return false;
    }

    cout << "Chef recommends: " << menu[0] << endl;
    return true;
}

// Restock (add) a menu item recursively
bool CuisineVendor::restock_item(const string & food)
{
    menu.push_back(food);
    cout << "Restocked: " << food << endl;
    return true;
}

/*
// Recursively delete all nodes
void CuisineVendor::delete_all(Node_LLL * & head)
{
    if (!head) return;
    delete_all(head->get_next());
    delete head;
    head = nullptr;
}

// Recursively display the full menu
bool CuisineVendor::show_menu() const
{
    if (!head)
    {
        cout << "No menu items available." << endl;
        return false;
    }

    cout << "Menu for " << get_name() << ":" << endl;
    return show_menu_recursive(head);
}

bool CuisineVendor::show_menu_recursive(Node_LLL * current) const
{
    if (!current)
        return true; // base case

    cout << " - " << current->get_data().get_name() << endl;
    return show_menu_recursive(current->get_next());
}


// Recursively search for a food item
bool CuisineVendor::take_order(const string & food) const
{
    if (!head)
    {
        cout << "No items to take an order from." << endl;
        return false;
    }
    return take_order_recursive(food, head);
}

bool CuisineVendor::take_order_recursive(const string & food, Node_LLL * current) const
{
    if (!current)
    {
        cout << "Sorry, " << food << " is not on the menu." << endl;
        return false;
    }

    if (current->get_data().get_name() == food)
    {
        cout << "Order placed for " << food << "!" << endl;
        return true;
    }

    return take_order_recursive(food, current->get_next());
}


// Recommend the first item (head of LLL)
bool CuisineVendor::recommend_item() const
{
    if (!head)
    {
        cout << "No items to recommend." << endl;
        return false;
    }

    cout << "Chef recommends: " << head->get_data().get_name() << endl;
    return true;
}

// Recursively add a new food item to the LLL
bool CuisineVendor::restock_item(const string & food)
{
    Node_LLL * new_node = new Node_LLL(CuisineVendor(food.c_str()));
    return restock_recursive(head, new_node);
}

bool CuisineVendor::restock_recursive(Node_LLL * & head, Node_LLL * new_node)
{
    if (!head)
    {
        head = new_node;
        cout << "Restocked: " << new_node->get_data().get_name() << endl;
        return true;
    }

    return restock_recursive(head->get_next(), new_node);
}
*/



// EntertainerVendor
//-----------------------------------------------------------------------------------------------
EntertainerVendor::EntertainerVendor(const char * name, const string & group, int dur, const string & stageTime)
    : Vendor(name), group_name(group), duration(dur), stage_time(stageTime)
{}
EntertainerVendor::~EntertainerVendor()
{}

// Announce performance
// Announce the entertainer's performance
bool EntertainerVendor::announce() const
{
    cout << "Attention! " << get_name()
         << " from group " << group_name
         << " will perform for " << duration
         << " minutes at " << stage_time << "." << endl;
    return true;
}

// Reschedule the entertainer's stage time
bool EntertainerVendor::reschedule(const string & newTime)
{
    stage_time = newTime;
    cout << get_name() << "'s performance has been rescheduled to " << stage_time << "." << endl;
    return true;
}
// Remove self from CLL
/*bool EntertainerVendor::perform_and_remove(EntertainerVendor *& tail)
{
    if (!tail) return false;

    Node_CLL * head = tail->get_next();

    if (head == tail) // only one entertainer
    {
        delete head;
        tail = nullptr;
        return true;
    }

    Node_CLL * to_remove = head;
    tail->set_next(head->get_next());
    delete to_remove;
    return true;
}

*/









/*


//display and describ efunction for all of the classes
//-------------------------------------------------------------------------------------------

bool Vendor::display_info() const
{
    if (!name) return false;
    cout << "Vendor Name: " << name << endl;
    describe();  // calls derived class’s describe if overridden
    return true;
}

bool Vendor::describe() const
{
    // Base behavior: common to all vendors
    cout << "This vendor offers goods or services specific to its type." << endl;
    return true;
}

//-------------------------------------------------------------------------------------------------
bool TrinketVendor::display_info() const
{
    cout << "Trinket Vendor: " << get_name() << endl;
    describe();
    return true;
}

bool TrinketVendor::describe() const
{
    cout << "Signature item: ";
    if (signature_item) cout << signature_item;
    cout << "." << endl;

    // Recursive display of inventory
    auto display_inventory_recursive = [this](size_t index, const auto& self) -> void {
        if (index >= inventory.size()) return;
        cout << " - " << inventory[index].first << " ($" << inventory[index].second << ")\n";
        self(index + 1, self);
    };
    display_inventory_recursive(0, display_inventory_recursive);
    return true;
}
//--------------------------------------------------------------------------------------------------
bool CuisineVendor::display_info() const
{
    cout << "Cuisine Vendor: " << get_name() << endl;
    describe();
    return true;
}

bool CuisineVendor::describe() const
{
    cout << "Menu items: ";
    
    auto display_menu_recursive = [this](size_t index, const auto& self) -> void {
        if (index >= menu.size()) return;
        cout << menu[index];
        if (index < menu.size() - 1) cout << ", ";
        self(index + 1, self);
    };
    
    display_menu_recursive(0, display_menu_recursive);
    cout << "." << endl;
    return true;
}
//--------------------------------------------------------------------------------------------------
bool EntertainerVendor::display_info() const
{
    cout << "Entertainer: " << get_name() << endl;
    describe();
    return true;
}

bool EntertainerVendor::describe() const
{
    cout << "Performs live entertainment with group " << group_name 
         << " for " << duration << " minutes at " << stage_time << "." << endl;
    return true;
}

//--------------------------------------------------------------------------------------------------
*/
