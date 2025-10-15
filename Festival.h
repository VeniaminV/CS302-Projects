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

	bool display_info() const;				//show vendors info
	bool rename_vendor(const char * new_name);	//update vendors name
	bool describe() const;				//explains what the vendor has to offer

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
	
private: 
	char * signature_item;
	vector<pair<string, float>> inventory;    //description and price

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

/*
	//Node for CuisineVendor LLL
	class Node_LLL
	{
		public:
			Node(const CuisineVendor & source)
				: CuisineVendor(source), next(nullptr) {}
		
			bool set_next(Node_LLL *& new_next) {next = new_next; } 
			Node_LLL *& get_next() {return next; }
			CuisineVEndor & get_data() const {return data; }
		private:
			Node_LLL * next;
			CuisineVendor data;
	};
*/
private:
	vector<string> menu;
	bool take_order_recursive(const string & food, size_t index) const;
};




//---------------------------------------------------------------------------------------------
//This class will have a CLL
class EntertainerVendor : public Vendor 
{
public: 
	EntertainerVendor(const char * name, const string & group, int duration,
				 const string & stageTime); //Constructor
//	EntertainerVendor(const EntertainerVendor & src);       // COPY CONSTRUCTOR
//    	EntertainerVendor & operator=(const EntertainerVendor & src); // ASSIGNMENT
	~EntertainerVendor();   //destructor


	bool announce() const;
//	int get_duratio() const;
	bool perform_and_remove(EntertainerVendor *& tail);
	bool reschedule(const string & newTime);

	EntertainerVendor * next;


/*
	class Node_CLL
    	{
    	public:
        	Node_CLL(const EntertainerVendor & source) : data(source), next(nullptr) {}
        	void set_next(Node_CLL * new_next) { next = new_next; }
        	Node_CLL *& get_next() { return next; }
        	EntertainerVendor & get_data() { return data; }
        	const EntertainerVendor & get_data() const { return data; }
    	private:
        	EntertainerVendor data;
        	Node_CLL * next;
    	};
*/

private:
	string group_name;
	int duration;
	string stage_time;
};



