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



// CuisineVendor
//------------------------------------------------------------------------------------------------
CuisineVendor::CuisineVendor(const char * name, const vector<string> & items)
    : Vendor(name), menu(items)
{}

CuisineVendor::~CuisineVendor()
{}




// EntertainerVendor
//-----------------------------------------------------------------------------------------------
EntertainerVendor::EntertainerVendor(const char * name, const string & group, int dur, const string & stageTime)
    : Vendor(name), next(nullptr), group_name(group), duration(dur), stage_time(stageTime)
{}

EntertainerVendor::~EntertainerVendor()
{
    next = nullptr; 
}


/*   
This is not really needed because i don't have any dynamically allocated data in Entertiner vendor
I'll keep it commented out for now. 

EntertainerVendor::EntertainerVendor(const EntertainerVendor & src)
    : Vendor(src), next(nullptr), group_name(src.group_name), duration(src.duration), stage_time(src.stage_time)
{}

EntertainerVendor & EntertainerVendor::operator=(const EntertainerVendor & src)
{
    if (this == &src) return *this;
    Vendor::operator=(src);
    group_name = src.group_name;
    duration = src.duration;
    stage_time = src.stage_time;
    next = nullptr;
    return *this;
}
*/


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

