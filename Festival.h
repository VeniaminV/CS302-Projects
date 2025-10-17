/*
Veniamin Velikoreskikh  veniamin@pdx.edu
cs302 fall 2025
Karla Fant assignment 1

This file will contain the class prototypes for the Vendor and 
the 3 derived classes from it. 
*/

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



//---------------------------------------------------------------------------------------------
class Vendor
{
public: 
	Vendor(const char * name);    //constructor
	Vendor(const Vendor & src);   //copy constructor
	Vendor & operator = (const Vendor & src); //assignment operator
	~Vendor(); 			//destructor

//	bool display_info() const;				//show vendors info
	bool rename_vendor(const char * new_name);	//update vendors name
//	bool describe() const;				//explains what the vendor has to offer

	const char * get_name() const {return name;}

private:
	char * name;

	//helper functions
	bool set_name(const char * src);
	bool clear_name();
};



//---------------------------------------------------------------------------------------------
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

	const char* get_signature() const { return signature_item; }
        const vector<pair<string, float>>& get_inventory() const { return inventory; }

	//TrinketVendor* retrieve_trinket(const char * name);

// 	bool display_info() const;            
 //   	bool describe() const;    
	
private: 
	char * signature_item;
	vector<pair<string, float>> inventory;    //description and price

	bool list_item_recursive(size_t index) const;
	bool sell_item_recursive(const string & itemName, size_t index);

	bool set_signature(const char* s);		//sets the signature item 
	bool clear_signature();


};


//---------------------------------------------------------------------------------------------
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

	const vector<string>& get_menu() const { return menu; }

	bool rename_vendor(const char* oldName, const char* newName);

//	bool display_info() const;
 //   	bool describe() const;
	
private:
	vector<string> menu;
	bool take_order_recursive(const string & food, size_t index) const;

//	 bool rename_cuisine_recursive(Node_LLL* node, const char* oldName, const char* newName);
};




//---------------------------------------------------------------------------------------------
//This class will have a CLL
class EntertainerVendor : public Vendor 
{
public: 
	EntertainerVendor(const char * name, const string & group, int duration,
				 const string & stageTime); //Constructor
	~EntertainerVendor();   //destructor


	bool announce() const;
//	bool perform_and_remove(EntertainerVendor *& tail);
	bool reschedule(const string & newTime);

	const string& get_group_name() const { return group_name; }
    	int get_duration() const { return duration; }
        const string& get_stage_time() const { return stage_time; }

 //	bool display_info() const;
   // 	bool describe() const;

private:
	string group_name;
	int duration;
	string stage_time;
};



