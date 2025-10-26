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

    bool display_all() const;
//    bool display_cuisine_recursive() const;
 //   bool display_entertainer_recursive() const;

    //will return a pointer to an object but it cannot modify it
    const CuisineVendor * retrieve_cuisine(const char * name) const;
    EntertainerVendor * retrieve_entertainer(const char * name);
  
    //Removal by name
    bool remove_cuisine(const char * name);
    bool remove_entertainer(const char * name);

    //Rename functions
    bool rename_vendor(const char * old_name, const char * new_name);


private:
    // Containers
    std::vector<TrinketVendor> trinkets;  // Vector storage
    Node_LLL * cuisine_head;              // LLL for Cuisine
    Node_CLL * entertainer_tail;          // CLL for Entertainers

    // Helpers for copy & cleanup
    bool copy_cuisine_list(Node_LLL *& dest, Node_LLL * source);
//    bool copy_entertainer_list(Node_CLL *& dest, Node_CLL * source);
    bool copy_entertainer_list(const Node_CLL * source, Node_CLL *& dest);
    bool copy_entertainer_recursive(const Node_CLL * current, const Node_CLL * source_tail,
                                        Node_CLL * dest_head, Node_CLL *& dest_tail);

    //Delete/ release memory
    bool clear_cuisine_list(Node_LLL *& head);
    bool clear_entertainer_list(Node_CLL *& tail);

    // Recursive insert helpers
    bool insert_cuisine_recursive(Node_LLL *& head, const CuisineVendor & vendor);
    bool insert_entertainer_recursive(Node_CLL *& tail, const EntertainerVendor & vendor);
    bool insert_entertainer_helper(Node_CLL * current, Node_CLL * tail, const EntertainerVendor & new_vendor);

    //Display funcitons
    bool display_trinkets_recursive(size_t index) const;
    bool display_cuisine_recursive(Node_LLL * head) const;
    bool display_entertainer_recursive(Node_CLL * current, Node_CLL * tail) const;

    //recursive removal by name
    bool remove_cuisine_recursive(Node_LLL *& head, const char * name);
    bool remove_entertainer_recursive(Node_CLL *& tail, Node_CLL * current, Node_CLL * prev, const char * name);

    const CuisineVendor * retrieve_cuisine_recursive(Node_LLL * head, const char * name) const;
    EntertainerVendor * retrieve_entertainer_recursive(Node_CLL * current, Node_CLL * tail, const char * name);

    //Rename helpers
    bool rename_cuisine_recursive(Node_LLL * current, const char * old_name, const char * new_name);
    bool rename_entertainer_recursive(Node_CLL * current, Node_CLL * tail, const char * old_name, const char * new_name);

};


