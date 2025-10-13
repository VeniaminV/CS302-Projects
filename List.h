//Veniamin Veniamin veniamin@pdx.edu


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

/*
	// Deep copy helpers
    	void copy_cuisine_list(CuisineVendorList::Node *&dest, CuisineVendorList::Node *source);
    	void copy_entertainer_list(EntertainerVendorList::Node *&dest, EntertainerVendorList::Node *source);

    	// Cleanup helpers
    	void clear_cuisine_list(CuisineVendorList::Node *&head);
    	void clear_entertainer_list(EntertainerVendorList::Node *&tail);

    	// Recursive insert helpers
    	void insert_cuisine_recursive(CuisineVendorList::Node *&head, const CuisineVendor &vendor);
    	void insert_entertainer_recursive(EntertainerVendorList::Node *&tail, const EntertainerVendor &vendor);
*/
   	// Helper functions for deep copies
    	bool copy_cuisine_list(CuisineVendor::Node_LLL *& dest, cuisine_vendor::Node_LLL * source);
    	bool copy_entertainer_list(entertainer_vendor::Node_CLL *& dest, entertainer_vendor::Node_CLL * source);
    	bool clear_cuisine_list(cuisine_vendor::Node_LLL *& head);
    	bool clear_entertainer_list(entertainer_vendor::Node_CLL *& tail);

	//Recursion insert functions for LLL and CLL
	bool insert_cuisine_recursive(CuisineVendor *& head, cuisineVendor * vendor);
	bool insert_entertainer_recursive(EntertainerVendor *& tail. EntertainerVendor * vendor);
};



