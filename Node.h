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
    Node_LLL(const CuisineVendor & source)
        : data(source), next(nullptr) {}

    void set_next(Node_LLL * new_next) { next = new_next; }
    Node_LLL *& get_next() { return next; }

    CuisineVendor & get_data() { return data; }
    const CuisineVendor & get_data() const { return data; }

private:
    CuisineVendor data;
    Node_LLL * next;
};


// Node for EntertainerVendor CLL
class Node_CLL
{
public:
    Node_CLL(const EntertainerVendor & source)
        : data(source), next(nullptr) {}

    void set_next(Node_CLL * new_next) { next = new_next; }
    Node_CLL *& get_next() { return next; }

    EntertainerVendor & get_data() { return data; }
    const EntertainerVendor & get_data() const { return data; }

private:
    EntertainerVendor data;
    Node_CLL * next;
};


