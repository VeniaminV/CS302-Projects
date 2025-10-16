/* Veniamin Velikoretskikh  veniamin@pdx.edu
Karla Fant CS302 fall 2025

This file will contain the data structure implementation 
for the LLL and CLL
*/


#include "LIst.h"
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
	trinkets = sourse.trinkets;    //Because it's a vector it will handle its own copy
	copy_cuisine_list(Cuisine_head, source.cousine_head);
	copy_entertainer_list(entertainer_tail, source.entertainer_tail;
}

//Assignment Operator
Festival::Festival & operator=(const Festival & source)
{
	if(this == &source) return *this;

	//clearing the current data
	clear_cuisine_list(cuisine_head);
	clear_entertainer_list(entertainer_tail):
	trinkets.clear();

	//copying the new data
	trinkets = sourse.trinkets;   
	copy_cuisine_list(Cuisine_head, source.cousine_head);
	copy_entertainer_list(entertainer_tail, source.entertainer_tail;

	return *this;
}

//destructor
Festival::~Festival()
{
	clear_cuisine_list(cuisine_head);
	clear_entertainer_list(entertainer_tail);
}


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
	return insert_entertainer__recursive(entertainer_tail, vendor);
}

// Helpers for copy & cleanup
bool Festival::insert_cuisine_recursive(Node_LLL *& head, const CuisineVendor & vendor);
{
	if (!head)
	{
		head = new Node_LLL(vendor);
		return true;
	}
	return insect_cuisine_recursive(head->get_next(), vendor);
}


bool Festival::insert_entertainer_recursive(Node_CLL *& tail, const EntertainerVendor & vendor);
{
	if (!tail)
	{
		tail = new Node_CLL(vendor);
		tail->set_next(tail);  //points to itself
		return true;
	}

	Node_CLL * new_node = new Node_Cll(vendor);
	new_node ->set_next(tail->get_next()); //points to the head of the list
	tail->set_next(new_node);		//links to the old tail to the new node
	tail = new_node; 			//updates tail pointer
	return true;
}



//Copy helper functions 
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
	
	Node_CLL * new_node = new Node_CLL(Source ->get_next() -> get_data());
	dest->set_next(new_node);
	
	return copy_entertainer_list(dest ->get_next(), source->get_next());
}


//Helpers to delete/ release the memory
bool Festival::clear_cuisine_list(Node_LLL *& head)
{
	if (!head) retunr true;
	
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

