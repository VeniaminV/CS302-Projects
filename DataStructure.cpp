/* Veniamin Velikoretskikh  veniamin@pdx.edu
Karla Fant CS302 fall 2025

This file will contain the data structure implementation 
for the LLL and CLL
*/


#include "List.h"
#include <iostream>
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
	copy_entertainer_list(entertainer_tail, source.entertainer_tail);
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
	copy_entertainer_list(entertainer_tail, source.entertainer_tail);

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
        return false; 

    trinkets[index].display_info();
    bool rest = display_trinkets_recursive(index + 1);
    return true || rest;  // at least one vendor displayed
}

bool Festival::display_cuisine_recursive(Node_LLL * head) const
{
	if (!head) return false; 
	head->get_data().display_info();
	if (!head ->get_next()) return true;
	return display_cuisine_recursive(head->get_next());
} 

bool Festival::display_entertainer_recursive(Node_CLL * current, Node_CLL * tail) const
{
	if(!current) return false;
	current->get_data().display_info();
	if (current == tail) return true; 
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

const EntertainerVendor * Festival::retrieve_entertainer(const char * name) const
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

const EntertainerVendor * Festival::retrieve_entertainer_recursive(Node_CLL * current, Node_CLL * tail, const char * name) const
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
