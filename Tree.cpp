// Veniamin Velikoretskikh veniamin@pdx.edu
// CS302 - Program #4
// Implementation of 2-3-4 Tree that stores Racer objects
// Fully recursive — no loops used
// Each function returns bool or int, never void
// Includes exception handling for invalid memory or insertion errors

#include "Tree.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Node234 implementation
//-------------------------------------------------------------------
Node234::Node234() : numItems(0) 
{
        for (int i = 0; i < MAX_ITEMS; ++i)
            items[i] = nullptr;	//Each item pointer starts empty
        for (int i = 0; i < MAX_CHILDREN; ++i)
            children[i] = nullptr;	//Each child pointer starts empty
}

//deletes all Racer objects stored in this node
Node234::~Node234() 
{
        for (int i = 0; i < numItems; ++i) {
            delete items[i];
            items[i] = nullptr;
        }
}

//Checks if the node is a leaf
bool Node234::isLeaf() const 
{
        return children[0] == nullptr;
}

//Check if node is full (if it has 3 items)
bool Node234::isFull() const 
{
        return numItems >= MAX_ITEMS;
}

// Tree implementation
//-------------------------------------------------------------------
Tree::Tree() : root(nullptr) {}

Tree::~Tree() 
{
        remove_all();
}

bool Tree::is_empty() const 
{
        return root == nullptr;
}
/*
// Insert
//---------------------------
//makes a deep copy of RAcer and inserts it
bool Tree::insert(const Racer& racer) 
{
    try {
	//clone reacer with virtual copy()
        Racer* newRacer = racer.copy();
        if (!newRacer) throw runtime_error("Failed to clone Racer");
	
	//If the tree is empty, will create root
        if (!root) {
            root = new Node234();
            root->items[0] = newRacer;
            root->numItems = 1;
            return true;
        }

        return insertRecursive(root, newRacer);
    }
    catch (const exception& e) {
        cerr << "Insert failed: " << e.what() << endl;
        return false;
    }
}

// Recursive insert
//---------------------------
//Inserts a RAcer into the correct leaf node recursively
bool Tree::insertRecursive(Node234*& current, Racer* racer) 
{
    if (!current) return false;

    //Case 1. Leaf node, place RAcer directly into items[]
    if (current->isLeaf())
    {
        if (!current->isFull()) {
            // Insert in the correct place, sorted order by name
            int i = current->numItems - 1;
            while (i >= 0 && racer->getName() < current->items[i]->getName()) {
                current->items[i + 1] = current->items[i];
                --i;
            }
            current->items[i + 1] = racer;
            current->numItems++;
            return true;
        } 
        else {
	    //The node is full, and we need to split before inserting
            split_node(current);
            return insertRecursive(current, racer);
        }
    }

    //Case 2. Internal node, we need to determine which child to traverse to
    if (racer->getName() < current->items[0]->getName())
        return insertRecursive(current->children[0], racer);
    else if (current->numItems == 1 || (current->numItems >= 2 && racer->getName() < current->items[1]->getName()))
        return insertRecursive(current->children[1], racer);
    else if (current->numItems == 2 || (current->numItems == 3 && racer->getName() < current->items[2]->getName()))
        return insertRecursive(current->children[2], racer);
    else
        return insertRecursive(current->children[3], racer);
}
*/
// Insert
//---------------------------
// Makes a deep copy of Racer and inserts it into the correct position
bool Tree::insert(const Racer& racer)
{
    try {
        // Create a polymorphic deep copy using virtual copy()
        Racer* newRacer = racer.copy();
        if (!newRacer)
            throw std::runtime_error("Failed to clone Racer");

        // Case 1: Tree is empty — create a root node
        if (!root) {
            root = new Node234();
            root->items[0] = newRacer;
            root->numItems = 1;
            return true;
        }

        // Case 2: Root is full — split it before insertion
        if (root->isFull()) {
            Node234* newRoot = new Node234();
            newRoot->children[0] = root;
            root = newRoot;
            split_node(root->children[0]);
        }

        // Recursive insertion into the proper child
        return insertRecursive(root, newRacer);
    }
    catch (const std::exception& e) {
        std::cerr << "Insert failed: " << e.what() << std::endl;
        return false;
    }
}

// Recursive insert
//---------------------------
// Inserts a Racer into the correct leaf node recursively
bool Tree::insertRecursive(Node234*& current, Racer* racer)
{
    if (!current) 
        return false;

    // Case 1: Leaf node
    if (current->isLeaf()) {
        // If not full, insert Racer in sorted order
        if (!current->isFull()) {
            return insertInLeaf(current, racer, current->numItems - 1);
        } 
        else {
            // Node full — split and retry recursively
            split_node(current);
            return insertRecursive(current, racer);
        }
    }

    // Case 2: Internal node — determine correct child recursively
    int childIndex = findChildIndex(current, racer->getName());
    if (current->children[childIndex] && current->children[childIndex]->isFull())
        split_node(current->children[childIndex]);

    return insertRecursive(current->children[childIndex], racer);
}


// Inserts a Racer into a leaf node in sorted order (fully recursive)
bool Tree::insertInLeaf(Node234*& current, Racer* racer, int index)
{
    if (index < 0 || racer->getName() >= current->items[index]->getName()) {
        current->items[index + 1] = racer;
        current->numItems++;
        return true;
    }

    // Shift item right and continue recursively
    current->items[index + 1] = current->items[index];
    return insertInLeaf(current, racer, index - 1);
}


// Determines which child to descend into (recursive-friendly helper)
int Tree::findChildIndex(Node234* current, const string& name) const
{
    if (current->numItems == 0)
        return 0;

    if (name < current->items[0]->getName())
        return 0;
    if (current->numItems == 1 || (current->numItems >= 2 && name < current->items[1]->getName()))
        return 1;
    if (current->numItems == 2 || (current->numItems == 3 && name < current->items[2]->getName()))
        return 2;
    return 3;
}


// Split node
//---------------------------
//Splits a full 3 itme node into two nodes and promotes the middle
bool Tree::split_node(Node234*& node) 
{
    if (!node || node->numItems < 3) return false;

    try {
	//creates a new right sibling node
        Node234* right = new Node234();

	//Move the last rightmost item to the new node
        right->items[0] = node->items[2];
        right->numItems = 1;

	//Clear moved itme from the left node
        node->items[2] = nullptr;
        node->numItems = 2;

	//REassingm children to the right node
        right->children[0] = node->children[2];
        right->children[1] = node->children[3];
        node->children[2] = node->children[3] = nullptr;

	//If splitting the root, we create a new root
        if (node == root) {
            Node234* newRoot = new Node234();
	
    	    //Middle item becomes root's only item
            newRoot->items[0] = node->items[1];
            newRoot->numItems = 1;

	    //Clear moved itme from old node
            node->items[1] = nullptr;
            node->numItems = 1;

	    //Connect children
            newRoot->children[0] = node;
            newRoot->children[1] = right;

	    //Update root ptr
            root = newRoot;
        }

        return true;
    }
    catch (const bad_alloc&) {
        cerr << "Split failed: memory allocation error\n";
        return false;
    }
}


// Display
//---------------------------
//Displays from right to left
bool Tree::displayRecursive(Node234* current, int indent) const
{
    if (!current) 
        return false;

    // Start recursive display with last item index
    return displayItems(current, current->numItems - 1, indent);
}

bool Tree::displayItems(Node234* current, int index, int indent) const
{
    if (!current) 
        return false;

    // Base case: no more items
    if (index < 0) 
        return true;

    // 1. Display right child
    displayRecursive(current->children[index + 1], indent + 4);

    // 2. Indentation for clarity
    for (int j = 0; j < indent; ++j)
        std::cout << ' ';

    // 3. Display current item
    current->items[index]->display();

    // 4. Display left child and continue recursion
    return displayItems(current, index - 1, indent);
}

// Display
//---------------------------
//Displays from right to left
/*bool Tree::display() const 
{
    if (!root) return false;
    return displayRecursive(root, 0);
}

bool Tree::displayRecursive(Node234* current, int indent) const 
{
    if (!current) return false;

    // Display rightmost children first
    for (int i = current->numItems; i >= 0; --i)
        displayRecursive(current->children[i], indent + 4);

    // Display items
    for (int i = 0; i < current->numItems; ++i)
        current->items[i]->display();

    return true;
}
*/
//---------------------------
// Remove all
//---------------------------
/*
bool Tree::remove_all() 
{
    if (!root) return false;
    bool result = deleteAll(root);
    root = nullptr;
    return result;
}

bool Tree::deleteAll(Node234*& current) 
{
    if (!current) return false;

    for (int i = 0; i < Node234::MAX_CHILDREN; ++i)
        deleteAll(current->children[i]);

    for (int i = 0; i < current->numItems; ++i) {
        delete current->items[i];
        current->items[i] = nullptr;
    }

    delete current;
    current = nullptr;
    return true;
}
*/

//Remove all
//-----------------------------
bool Tree::deleteAll(Node234*& current)
{
    if (!current) 
        return false;

    // Delete all children recursively
    deleteChildren(current, 0);

    // Delete all items recursively
    deleteItems(current, 0);

    delete current;
    current = nullptr;
    return true;
}

bool Tree::deleteChildren(Node234*& current, int index)
{
    if (!current) 
        return false;

    if (index >= Node234::MAX_CHILDREN) 
        return true;

    deleteAll(current->children[index]);
    return deleteChildren(current, index + 1);
}

bool Tree::deleteItems(Node234*& current, int index)
{
    if (!current) 
        return false;

    if (index >= current->numItems) 
        return true;

    delete current->items[index];
    current->items[index] = nullptr;

    return deleteItems(current, index + 1);
}

