//Veniamin Velikoretskikh veniamin@pdx.edu
//Karla Fant cs302 fall 2025 programing assingment 1. 

#include "Festival.h"
#include <cstring>
#include <iostream>
using namespace std;

// Vendor
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
bool Vendor::set_name(const char * src)
{
    if (!src) return false;
    name = new char[strlen(src) + 1];
    strcpy(name, src);
    return true;
}

bool Vendor::clear_name()
{
    delete [] name;
    name = nullptr;
    return true;
}



// TrinketVendor
TrinketVendor::TrinketVendor() : Vendor(""), signature_item(nullptr)
{
}

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
bool TrinketVendor::set_signature(const char * s)
{
    if (!s) return false;
    signature_item = new char[strlen(s) + 1];
    strcpy(signature_item, s);
    return true;
}

bool TrinketVendor::clear_signature()
{
    delete [] signature_item;
    signature_item = nullptr;
    return true;
}




// CuisineVendor
CuisineVendor::CuisineVendor(const char * name, const vector<string> & items)
    : Vendor(name), menu(items)
{
}

CuisineVendor::~CuisineVendor()
{
    // Nothing dynamic to free in this version
}




// EntertainerVendor
EntertainerVendor::EntertainerVendor(const char * name, const string & group, int dur, const string & stageTime)
    : Vendor(name), next(nullptr), group_name(group), duration(dur), stage_time(stageTime)
{
}

EntertainerVendor::~EntertainerVendor()
{
    next = nullptr; // just to be safe; nothing dynamically allocated here
}




// Optional: copy constructor and assignment operator for EntertainerVendor
EntertainerVendor::EntertainerVendor(const EntertainerVendor & src)
    : Vendor(src), group_name(src.group_name), duration(src.duration), stage_time(src.stage_time), next(nullptr)
{
}

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

