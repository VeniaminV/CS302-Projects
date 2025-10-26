/* Veniamin Velikoretskikh  veniamin@pdx.edu
Karla Fant CS302 fall 2025

This file will contain the data structure implementation 
for the LLL and CLL
*/


#include "List.h"
#include <iostream>

#include <cstring>
using namespace std;

//Festival class
//constructor
Festival::Festival()
	: cuisine_head(nullptr), entertainer_tail(nullptr)
{}

//copy constructor
Festival::Festival(const Festival & source)
	:cuisine_head(nullptr), entertainer_tail(nullptr)
{
//	trinkets = sourse.trinkets;    //Because it's a vector it will handle its own copy
	copy_cuisine_list(cuisine_head, source.cuisine_head);
//	copy_entertainer_list(Node_CLL * source, Node_CLL *& dest);
//	copy_entertainer_list(entertainer_tail, source.entertainer_tail);
	copy_entertainer_list(source.entertainer_tail, entertainer_tail);
}

//Assignment Operator
Festival & Festival::operator=(const Festival & source)
{
	if(this == &source) return *this;

	//clearing the current data
	clear_cuisine_list(cuisine_head);
	clear_entertainer_list(entertainer_tail);
	trinkets.clear();

	//copying the new data
	trinkets = source.trinkets;   
	copy_cuisine_list(cuisine_head, source.cuisine_head);
//	copy_entertainer_list(entertainer_tail, source.entertainer_tail);
	copy_entertainer_list(source.entertainer_tail, entertainer_tail);

	return *this;
}

//destructor
Festival::~Festival()
{
	clear_cuisine_list(cuisine_head);
	clear_entertainer_list(entertainer_tail);
}

//functions that add vendors
//----------------------------------------------------------------------------------------
//This function will add a trinket vendor to a vector
bool Festival::add_trinket_vendor(const TrinketVendor & vendor)
{
	trinkets.push_back(vendor);
	return true;
}

//Will add a cuisine vendor to a LLL 
bool Festival::add_cuisine_vendor(const CuisineVendor & vendor)
{
	return insert_cuisine_recursive(cuisine_head, vendor);
}

//Will add a entertainer to a CLL
bool Festival::add_entertainer(const EntertainerVendor & vendor)
{

	return insert_entertainer_recursive(entertainer_tail, vendor);
}


// insert helper functions 
//----------------------------------------------------------------------------------------
bool Festival::insert_cuisine_recursive(Node_LLL *& head, const CuisineVendor & vendor)
{
	if (!head)
	{
		head = new Node_LLL(vendor);
		return true;
	}
	return insert_cuisine_recursive(head->get_next(), vendor);
}


bool Festival::insert_entertainer_recursive(Node_CLL *& tail, const EntertainerVendor & new_vendor)
{
    if (!tail) {
        tail = new Node_CLL(new_vendor);
        tail->set_next(tail);  // single node ring
        return true;
    }

    // Recursive helper
    return insert_entertainer_helper(tail->get_next(), tail, new_vendor);
}


bool Festival::insert_entertainer_helper(Node_CLL * current, Node_CLL * tail, const EntertainerVendor & new_vendor)
{
    // base case: we came full circle, insert before tail->get_next()
    if (current == tail) {
        Node_CLL * temp = new Node_CLL(new_vendor);
        temp->set_next(tail->get_next());
        tail->set_next(temp);
        tail = temp;  // new tail
        return true;
    }
    return insert_entertainer_helper(current->get_next(), tail, new_vendor);
}
/*
bool Festival::insert_entertainer_recursive(Node_CLL *& tail, const EntertainerVendor & vendor)
{
	if (!tail)
	{
		tail = new Node_CLL(vendor);
		tail->set_next(tail);  //points to itself
		return true;
	}

	Node_CLL * new_node = new Node_CLL(vendor);
	new_node ->set_next(tail->get_next()); //points to the head of the list
	tail->set_next(new_node);		//links to the old tail to the new node
	tail = new_node; 			//updates tail pointer
	return true;
}
*/



//Display helpers
//---------------------------------------------------------------------------------------
bool Festival::display_all() const
{
    bool any = false;

    cout << "\n=== Trinket Vendors ===\n";
    if (display_trinkets_recursive(0))
        any = true;

    cout << "\n=== Cuisine Vendors ===\n";
    if (display_cuisine_recursive(cuisine_head))
        any = true;

    cout << "\n=== Entertainers ===\n";
    if (entertainer_tail && display_entertainer_recursive(entertainer_tail->get_next(), entertainer_tail))
        any = true;

    return any;
}
bool Festival::display_trinkets_recursive(size_t index) const
{
    if (index >= trinkets.size())
        return true;

    const TrinketVendor & vendor = trinkets[index];
    cout << "\nTrinket Vendor: " << vendor.get_name() << endl;

    if (vendor.get_signature())
        cout << "Signature Item: " << vendor.get_signature() << endl;

    const vector<pair<string, float>> & items = vendor.get_inventory();
    for (size_t i = 0; i < items.size(); ++i)
        cout << " - " << items[i].first << " ($" << items[i].second << ")\n";

    return display_trinkets_recursive(index + 1);
}


bool Festival::display_cuisine_recursive(Node_LLL * head) const
{
    if (!head)
        return true;

    const CuisineVendor & vendor = head->get_data();
    cout << "\nCuisine Vendor: " << vendor.get_name() << endl;

    const vector<string> & menu = vendor.get_menu();
    for (size_t i = 0; i < menu.size(); ++i)
        cout << " - " << menu[i] << endl;

    return display_cuisine_recursive(head->get_next());
} 

bool Festival::display_entertainer_recursive(Node_CLL * current, Node_CLL * tail) const
{
    if (!current)
        return false;

    const EntertainerVendor & vendor = current->get_data();
    cout << "\nEntertainer: " << vendor.get_name() << endl;
    cout << "  Group: " << vendor.get_group_name() << endl;
    cout << "  Duration: " << vendor.get_duration() << " mins" << endl;
    cout << "  Stage Time: " << vendor.get_stage_time() << endl;

    if (current == tail)
        return true;

    return display_entertainer_recursive(current->get_next(), tail);
}




//Copy helper functions 
//----------------------------------------------------------------------------------------
bool Festival::copy_cuisine_list(Node_LLL *& dest, Node_LLL * source)
{
	if (!source)
	{
		dest = nullptr;
		return true;	
	}
	dest = new Node_LLL(source -> get_data());
	return copy_cuisine_list(dest->get_next(), source ->get_next());
}

/*
bool Festival::copy_entertainer_list(Node_CLL *& dest, Node_CLL * source)
{
	if (!source)
	{
		dest = nullptr;
		return true;
	}
	
	//creates the first dest node	
	if(!dest)
	{
		dest = new Node_CLL(source->get_data());
		dest ->set_next(dest);
		if(source->get_next() == source) return true;

		return copy_entertainer_list(dest->get_next(), source->get_next());
	}
	//if were back to the source head, then we stop
	if(source->get_next() == source)
	{
		dest->set_next(dest);
		return true;
	}
	
	Node_CLL * new_node = new Node_CLL(source ->get_next() -> get_data());
	dest->set_next(new_node);
	
	return copy_entertainer_list(dest ->get_next(), source->get_next());
}
*/

bool Festival::copy_entertainer_list(const Node_CLL * source, Node_CLL *& dest)
{
    if (!source) {
        dest = nullptr;
        return true;
    }

    Node_CLL * dest_head = new Node_CLL(source->get_data());
    Node_CLL * dest_tail = dest_head;
    return copy_entertainer_recursive(source->get_next(), source, dest_head, dest_tail);
}

bool Festival::copy_entertainer_recursive(const Node_CLL * current, const Node_CLL * source_tail,
                                           Node_CLL * dest_head, Node_CLL *& dest_tail)
{
    if (current == source_tail) {
        dest_tail->set_next(dest_head);  // close ring
        return true;
    }

    Node_CLL * new_node = new Node_CLL(current->get_data());
    dest_tail->set_next(new_node);
    dest_tail = new_node;
    return copy_entertainer_recursive(current->get_next(), source_tail, dest_head, dest_tail);
}


//Helpers to delete/ release the memory
//----------------------------------------------------------------------------------------
bool Festival::clear_cuisine_list(Node_LLL *& head)
{
	if (!head) return true;
	
	Node_LLL * temp = head -> get_next();
	delete head;
	head = nullptr;
	return clear_cuisine_list(temp);	
}


bool Festival::clear_entertainer_list(Node_CLL *& tail)
{
	if(!tail) return false;

	//base case if only one node
	if(tail->get_next() == tail)
	{
		delete tail;
		tail = nullptr;
		return true;
	}

	//deleting the node after the tail
	Node_CLL * head = tail->get_next();
	Node_CLL * second = head->get_next();
	delete head;

	//updates the tail to skip the deleted node
	tail->set_next(second);

	//clear all the rest of the nodes
	return clear_entertainer_list(tail);
}



//Recursive Retrieval
//-----------------------------------------------------------------------------------------
// Public wrappers
const CuisineVendor * Festival::retrieve_cuisine(const char * name) const
{
    return retrieve_cuisine_recursive(cuisine_head, name);
}

EntertainerVendor * Festival::retrieve_entertainer(const char * name)
{
    if (!entertainer_tail) return nullptr;
    return retrieve_entertainer_recursive(entertainer_tail->get_next(), entertainer_tail, name);
}

// Private recursive helpers
const CuisineVendor * Festival::retrieve_cuisine_recursive(Node_LLL * head, const char * name) const
{
    if (!head) return nullptr;

    if (strcmp(head->get_data().get_name(), name) == 0)
        return &head->get_data();

    return retrieve_cuisine_recursive(head->get_next(), name);
}

EntertainerVendor * Festival::retrieve_entertainer_recursive(Node_CLL * current, Node_CLL * tail, const char * name)
{
    if (!current) return nullptr;

    if (strcmp(current->get_data().get_name(), name) == 0)
        return &current->get_data();

    if (current == tail)
        return nullptr; // base case for circular list

    return retrieve_entertainer_recursive(current->get_next(), tail, name);
}



//Remove vendor by name
//_________________________________________________________________________________________
// Public wrappers
bool Festival::remove_cuisine(const char * name)
{
    return remove_cuisine_recursive(cuisine_head, name);
}

bool Festival::remove_entertainer(const char * name)
{
    if (!entertainer_tail) return false;
    return remove_entertainer_recursive(entertainer_tail, entertainer_tail->get_next(), entertainer_tail, name);
}

// Private recursive helpers

bool Festival::remove_cuisine_recursive(Node_LLL *& head, const char * name)
{
    if (!head) return false;

    if (strcmp(head->get_data().get_name(), name) == 0)
    {
        Node_LLL * temp = head;
        head = head->get_next();
        delete temp;
        return true;
    }
    return remove_cuisine_recursive(head->get_next(), name);
}


bool Festival::remove_entertainer_recursive(Node_CLL *& tail, Node_CLL * current, Node_CLL * prev, const char * name)
{
    if (!current) return false;

    if (strcmp(current->get_data().get_name(), name) == 0)
    {
        // only one node in list
        if (current == tail && current->get_next() == tail)
        {
            delete current;
            tail = nullptr;
            return true;
        }

        prev->set_next(current->get_next());
        if (current == tail)
            tail = prev;

        delete current;
        return true;
    }

    if (current == tail)
        return false;

    return remove_entertainer_recursive(tail, current->get_next(), current, name);
}


//Rename fucnunction
//_____________________________________________________________________________________________
bool Festival::rename_vendor(const char * old_name, const char * new_name)
{
    if (!old_name || !new_name) return false;
    bool renamed = false;

    // Try Cuisine Vendors (LLL)
    renamed = rename_cuisine_recursive(cuisine_head, old_name, new_name);
    if (renamed) return true;

    // Try Entertainers (CLL)
    if (entertainer_tail)
        renamed = rename_entertainer_recursive(entertainer_tail->get_next(), entertainer_tail, old_name, new_name);
    if (renamed) return true;

    // Try Trinket Vendors
    if (trinket_vendor && strcmp(trinket_vendor->get_name(), old_name) == 0) {
        trinket_vendor->rename_vendor(new_name);
        return true;
    }

    return false; // nothing found
}




bool Festival::rename_cuisine_recursive(Node_LLL * current, const char * old_name, const char * new_name)
{
    if (!current) return false;

    CuisineVendor & vendor = current->get_data();
    if (strcmp(vendor.get_name(), old_name) == 0) {
        vendor.rename_vendor(new_name);
        return true;
    }
    return rename_cuisine_recursive(current->get_next(), old_name, new_name);
}



bool Festival::rename_entertainer_recursive(Node_CLL * current, Node_CLL * tail, const char * old_name, const char * new_name)
{
    if (!current) return false;

    EntertainerVendor & vendor = current->get_data();
    if (strcmp(vendor.get_name(), old_name) == 0) {
        vendor.rename_vendor(new_name);
        return true;
    }

    // Base case: stop after we’ve looped around the ring
    if (current == tail)
        return false;

    return rename_entertainer_recursive(current->get_next(), tail, old_name, new_name);
}


bool Vendor::rename_vendor(const char * new_name)
{
    if (!new_name || !*new_name) return false;

    clear_name();
    set_name(new_name);
    return true;
}

