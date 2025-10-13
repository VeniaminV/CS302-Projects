//Veniamin Veniamin veniamin@pdx.edu

/*
#include "Node.h"

class Festival
{
public:
	Festival();
 	Festival(const Festival & source);               // copy constructor
        Festival & operator=(const Festival & source);   // assignment operator
	~Festival();

	bool add_trincket_vendor(const TrinketVendor & vendor); //will use vector to store;
	bool add_cuisine_vendor(const CuisineVendor & vendor);   //will use LLL
	bool add_entertainer(const EntertainerVendor & vendor);   //will use CLL

private:

	vector<TrinketVendor> trinkets;			//Vector to store trinkets
	CuisineVendor:: Node_LLL * cuisine_head;     	//For the LLL to store cuisine vendors
	EntertainerVendor:: Node_CLL * entertainer_tail;    //For the CLL, tail pointer for easy insert to store Entertainer vendors

   	// Helper functions for deep copies
    	bool copy_cuisine_list(CuisineVendor::Node_LLL *& dest, cuisine_vendor::Node_LLL * source);
    	bool copy_entertainer_list(entertainer_vendor::Node_CLL *& dest, entertainer_vendor::Node_CLL * source);
    	bool clear_cuisine_list(cuisine_vendor::Node_LLL *& head);
    	bool clear_entertainer_list(entertainer_vendor::Node_CLL *& tail);

	//Recursion insert functions for LLL and CLL
	bool insert_cuisine_recursive(CuisineVendor *& head, cuisineVendor * vendor);
	bool insert_entertainer_recursive(EntertainerVendor *& tail. EntertainerVendor * vendor);
};


*/

// List.h
// Veniamin Velikoretskikh veniamin@pdx.edu
// CS302 Fall 2025 - Oktoberfest Program


#include "Festival.h"
#include "Node.h"
#include <vector>

class Festival
{
public:
    Festival();
    Festival(const Festival & source);
    Festival & operator=(const Festival & source);
    ~Festival();

    bool add_trinket_vendor(const TrinketVendor & vendor);
    bool add_cuisine_vendor(const CuisineVendor & vendor);
    bool add_entertainer(const EntertainerVendor & vendor);

private:
    // Containers
    std::vector<TrinketVendor> trinkets;  // Vector storage
    Node_LLL * cuisine_head;              // LLL for Cuisine
    Node_CLL * entertainer_tail;          // CLL for Entertainers

    // Helpers for copy & cleanup
    bool copy_cuisine_list(Node_LLL *& dest, Node_LLL * source);
    bool copy_entertainer_list(Node_CLL *& dest, Node_CLL * source);
    bool clear_cuisine_list(Node_LLL *& head);
    bool clear_entertainer_list(Node_CLL *& tail);

    // Recursive insert helpers
    bool insert_cuisine_recursive(Node_LLL *& head, const CuisineVendor & vendor);
    bool insert_entertainer_recursive(Node_CLL *& tail, const EntertainerVendor & vendor);
};


