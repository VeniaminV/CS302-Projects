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
using namespace std;

class Node234 {
public:
    static const int MAX_ITEMS = 3;
    static const int MAX_CHILDREN = 4;

    Node234();
    ~Node234();

    bool isLeaf() const;
    bool isFull() const;

    Racer* items[MAX_ITEMS];
    Node234* children[MAX_CHILDREN];
    int numItems;
};

class Tree {
public:
    Tree();
    ~Tree();

    bool insert(const Racer& racer);
    bool display() const;
    bool remove_all();
    bool is_empty() const;

private:
    Node234* root;

 /*   // Recursive helpers
    bool insertRecursive(Node234*& current, Racer* racer);
    bool split_node(Node234*& node);
    bool displayRecursive(Node234* current, int indent) const;
    bool deleteAll(Node234*& current);
*/
// Recursive helpers used by implementations
    bool insertRecursive(Node234*& current, Racer* racer);
    bool insertInLeaf(Node234*& current, Racer* racer, int index);
    int findChildIndex(Node234* current, const std::string& name) const;
    bool split_child(Node234* parent, int childIndex); // split parent's child at childIndex
    bool displayRecursive(Node234* current, int indent) const;
    bool displayItems(Node234* current, int index, int indent) const;

    // Deletion helpers
    bool deleteAll(Node234*& current);
    bool deleteChildren(Node234*& current, int index);
    bool deleteItems(Node234*& current, int index);
};

