//Veniamin Velikoretskikh veniamin@pdx.edu
//Karla Fant cs302 fall 2025 programing assingment 1. 

#include "List.h"
#include <iostream>
using namespace std;

Festival::Festival()
{
    cuisine_head = nullptr;
    entertainer_tail = nullptr;
}

Festival::~Festival()
{
    clear_cuisine_list(cuisine_head);
    clear_entertainer_list(entertainer_tail);
}

bool Festival::add_trinket_vendor(const TrinketVendor & vendor)
{
    trinkets.push_back(vendor);
    return true;
}

bool Festival::add_cuisine_vendor(const CuisineVendor & vendor)
{
    return insert_cuisine_recursive(cuisine_head, vendor);
}

bool Festival::add_entertainer(const EntertainerVendor & vendor)
{
    return insert_entertainer_recursive(entertainer_tail, vendor);
}

