/*
Veniamin Velikoretskikh veniamin@pdx.edu
CS302 Fall 2025 - Oktoberfest Program

This file will include the Nodes for  the data structures

*/
#include "Festival.h"

// Node for CuisineVendor LLL
class Node_LLL
{
public:
    Node_LLL(const CuisineVendor & source)		//Constructor
        : data(source), next(nullptr) {}

    bool set_next(Node_LLL * new_next) { next = new_next; return true; }	//Setter, will connect the nodes
					//because pointers are private and to maintain encapsulation

    Node_LLL *& get_next() { return next; }	//Getter, gives access to this node's next pointer
					//This is for the functions that need to modify the list

    CuisineVendor & get_data() { return data; }		//Gives access to the data stored in this node
					//Because data is private and other functions can't touch it

    const CuisineVendor & get_data() const { return data; } //Same function but const for functions that
							    //don't accidentaly modify it.

private:
    CuisineVendor data;
    Node_LLL * next;
};


// Node for EntertainerVendor CLL
class Node_CLL
{
public:
    Node_CLL(const EntertainerVendor & source)		//Constructor
        : data(source), next(nullptr) {}

    bool set_next(Node_CLL * new_next) { next = new_next; return true; }	//Connects the node in CLL
					//because pointers are private and to maintain encapsulation

    Node_CLL *& get_next() { return next; } 	//gives access to this node's next pointer

    EntertainerVendor & get_data() { return data; }	//gives the data stored inside the node
    const EntertainerVendor & get_data() const { return data; } //for functions that don't need to modify the data

private:
    EntertainerVendor data;
    Node_CLL * next;
};


