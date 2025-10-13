//Veniamin Velikoretskikh veniamin@pdx.edu


#include "Festival.h" 


/*
//namespace CuisineVendorList
{
	//Node for CuisineVendor LLL
	class Node_LLL : public CuisineVendor
	{
		public:
			Node_LLL(const CuisineVendor & source)
				: CuisineVendor(source), next(nullptr) {}
		
			void set_next(Node_LLL *& next) {next = new_next; } 
			Node_LLL *& get_next() {return next; }
		private:
			CuisineVendor data;	
			Node_LLL * next;
	}

}



//namespace EntertainerVendorList
{
	//Node for EntertainerVendor CLL
	class Node_CLL : public EntertainerVendor
	{
		public:
			Node(const EntertainerVendor & source) 
				: EntertainerVendor(source), next(nullptr) {}
		
			void set_next(Node *& next) {next = new_next; }
			Node *& get_next() {return next;}
		private:
			Node * next;
	}
} 
*/
// Node.h
// Veniamin Velikoretskikh veniamin@pdx.edu
// CS302 Fall 2025 - Oktoberfest Program

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


