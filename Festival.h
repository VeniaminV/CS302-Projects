//Veniamin Velikoreskikh  veniamin@pdx.edu
// cs302 fall 2025
// Karla Fant

//This is the .h file for proram 1 about oktoberfest.
//It will contain 5 classes with hierarchy, and the prototypes

#include <cstring>
#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using namespace std; 


class TrinketVendor;
class CuisineVendor;
class EntertainerVendor;



class Vendor
{
public: 
	Vendor(const char * name);    //constructor
	Vendor(const Vendor & src);   //copy constructor
	Vendor & operator = (const Vendor & src); //assignment operator
	~Vendor(); 			//destructor

	bool display_info() const;				//show vendors info
	bool rename_vendor(const char * new_name);	//update vendors name
	bool describe() const;				//explains what the vendor has to offer

private:
	char * name;

	//helper functions
	bool set_name(const char * src);
	bool clear_name();
};



class TrinketVendor : public Vendor
{
public:
	TrinketVendor();
	TrinketVendor(const char * vendorName, const char * signaturItem);  //constructor
	TrinketVendor(const TrinketVendor & src);                           //copy constructor
	TrinketVendor & operator = (const TrinketVendor & src);            //assignment operator
	~TrinketVendor();						//destructor

	bool add_item(const string & itemName, float price);		
	bool list_item() const;
	bool sell_item(const string & itemName);
	
private: 
	char * signature_item;
	vector<pair<string, float>> inventory;    //description and price

	bool set_signature(const char* s);
	bool clear_signature();

};


//This class will have a LLL
class CuisineVendor : public Vendor 
{
public: 
	CuisineVendor(const char * name = " ", const vector<string> & items = {});       //constructor
	~CuisineVendor();							//destructor

	bool show_menu() const;
	bool take_order(const string & food) const;
 	bool recommend_item() const;
	bool restock_item(const string & food);

	CuisineVendor * next;

private:
	vector<string> menu;
	bool take_order_recursive(const string & food, size_t index) const;
};




//This class will have a CLL
class EntertainerVendor : public Vendor 
{
public: 
	EntertainerVendor(const char * name, const string & group, int duration,
				 const string & stageTime); //Constructor
	~EntertainerVendor();   //destructor


	bool announce() const;
//	int get_duratio() const;
	bool perform_and_remove(EntertainerVendor *& tail);
	bool reschedule(const string & newTime);

	EntertainerVendor * next;

private:
	string group_name;
	int duration;
	string stage_time;
};





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
	CuisineVendor:: Node * cuisine_head;     	//For the LLL to store cuisine vendors
	EntertainerVendor:: Node * entertainer_tail;    //For the CLL, tail pointer for easy insert to store Entertainer vendors


   	// Helper functions for deep copies
    	void copy_cuisine_list(cuisine_vendor::Node *& dest, cuisine_vendor::Node * source);
    	void copy_entertainer_list(entertainer_vendor::Node *& dest, entertainer_vendor::Node * source);
    	void clear_cuisine_list(cuisine_vendor::Node *& head);
    	void clear_entertainer_list(entertainer_vendor::Node *& tail);

	//Recursion insert functions for LLL and CLL
	void insert_cuisine_recursive(CuisineVendor *& head, cuisineVendor * vendor);
	void insert_entertainer_recursive(EntertainerVendor *& tail. EntertainerVendor * vendor);

};



