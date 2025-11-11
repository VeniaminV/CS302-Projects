//Veniamin Velikoretskikh veniamin@pdx.edu
//CS302 Karla Fant

//Tree.h
/*
This file will contain the Node and prototypes for the 
2-3-4 tree. The Node class has everything that is about the 
node itself and the Tree class works with that node. 
*/

#include "Racers.h"

class Node {
public:
        Node();
        ~Node();

        bool isLeaf() const;
        bool isFull() const;

	//integers for size of the tree
        const int MAX_ITEMS = 3;
        const int MAX_CHILDREN = 4;

        Racer* items[MAX_ITEMS];
        Node* children[MAX_CHILDREN];
        int numItems;
};


class Tree {
public:
        Tree();
        ~Tree();

        bool insert(const Racer & racer);  // clones internally
        bool display() const;
        bool remove_all();
        bool is_empty() const;

private:
        Node* root;

        // Helpers
        bool insertRecursive(Node* current, Racer* racer);
        Racer* cloneRacer(const Racer & racer) const;
        bool displayRecursive(Node* current, int indent) const;
        bool deleteAll(Node*& current);
};

