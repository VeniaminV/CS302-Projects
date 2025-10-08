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

using namespace std; 


class Festival
{
public:
	Festival();
	~Festival();

	void add_trincket_vendor(const TrinketVendor& vendor); //will use vector to store;
	void add_cuisine_vendor(CuisineVendor * vendor);   //will use LLL
	void add_entertainer(EntertainerVEndor * vendor);   //will use CLL

private:

	vector<TrinketVendor> trinkets;
	CuisineVEndor * cuisine_head;     //For the LLL
	EntertainerVendor * entertainer_tail;    //For the CLL, tail pointer for easy insert

	//Recursion insert functions for LLL and CLL
	void insert_cuisine_recursive(CuisineVEndor *& head, cuisineVendor * vendor);
	void insert_entertainer_recursive(EntertainerVendor *& tail. EntertainerVendor * vendor);

};



class Vendor
{
public: 
	Vendor(const char * name);    //constructor
	Vendor(const Vendor & src);   //copy constructor
	Vendor & operator = (const Vendor & src; //assignment operator
	~Vendor(); 			//destructor

	void display_name() const;
	bool match_name(const char * target) const;
	void set_name(const char * new_name);

private:
	char * name;
};



class TrinketVendor : public Vendor
{
public:
	TrinketVendor(const char * vendorName, const char * signaturItem);  //constructor
	TrinketVendor(const TrinketVendor & src);                           //copy constructor
	TrinketVendor & operator = (const TrinketVendor & src);            //assignment operator
	~TrinketVendor();						//destructor

	void add_item(const string & itemName, float price);
	void list_item() const;
	bool sell_item(const string & itemName);
	
private: 
	char * signature_item;
	struct Item{
		string name;
		float price;
	};
	vector<Item> inventory;

	void set_signature(const char* s);
	void clear_signature();

};



class CuisineVendor : public Vendor 
{
public: 
	CuisineVendor(const char * name, const vector<string> & items);       //constructor
	~CuisineVendor();							//destructor

	void show_menu() const;
	bool has_item(const string & food) const;
	void add_item(const string & food);

	CuisineVendor * next;

private:
	vector<string> menu;
};





class EntertainerVendor : public Vendor 
{
public: 
	EntertainerVendor(const char * name, const string & group, int duration,
				 const string & stageTime); //Constructor
	~EntertainerVendor();   //destructor


	void announce() const;
	int get_duratio() const;
	void change_time(const string & newTime):

	EntertainerVendor * next;

private:
	stging group_name;
	int duration;
	string string stage_time;
};
