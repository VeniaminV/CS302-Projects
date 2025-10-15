/*
Veniamin Veniamin veniamin@pdx.edu
 CS302 Fall 2025 - Oktoberfest Program

This file will have the festival class. This class will manage the 
data structures of class vendors 
*/


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


