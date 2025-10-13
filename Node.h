//Veniamin Velikoretskikh veniamin@pdx.edu


#include "Festival.h" 



namespace CuisineVendorList
{
	//Node for CuisineVendor LLL
	class Node : public CuisineVendor
	{
		public:
			Node(const CuisineVendor & source)
				: CuisineVendor(source), next(nullptr) {}
		
			void set_next(Node *& next) {next = new_next; } 
			Node *& get_next() {return next; }
		private:
			Node * next;
	}

}



namespace EntertainerVendorList
{
	//Node for EntertainerVendor CLL
	class Node : public EntertainerVendor
	{
		publice:
			Node(const EntertainerVendor & source) 
				: EntertainerVendor(source), next(nullptr) {}
		
			void set_next(Node *& next) {next = new_next; }
			Node *& get_next() {return next;}
		private:
			Node * next;
	}
} 
