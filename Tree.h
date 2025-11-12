//Veniamin Velikoretskikh veniamin@pdx.edu
//CS302 Karla Fant

//Tree.h
/*
This file will contain the Node and prototypes for the 
2-3-4 tree. The Node class has everything that is about the 
node itself and the Tree class works with that node. 
*/
#include "Racers.h"
#include <iostream>

class Node234 {
public:
        Node234();
        ~Node234();

        bool isLeaf() const;
        bool isFull() const;
    
        static const int MAX_ITEMS = 3;
        static const int MAX_CHILDREN = 4;

        Racer* items[MAX_ITEMS];
        Node234* children[MAX_CHILDREN];
        int numItems;
};

class Tree {
public:
        Tree();
        ~Tree();

        bool insert(const Racer & racer);
        bool display() const;
        bool remove_all();
        bool is_empty() const;

	bool split_node(Node* & node);

private:
        Node234* root;

        // Recursive helpers
        bool insertRecursive(Node234*& current, Racer* racer);
        Racer* cloneRacer(const Racer & racer) const;
        bool displayRecursive(Node234* current, int indent) const;
        bool deleteAll(Node234*& current);
};


