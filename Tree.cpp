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
    if (!current) return false;

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

// Base case: insert at start
    if (index < 0) {
        current->items[0] = racer;
        current->numItems++;
        return true;
    }

    // Insert after current if name >= current item
    if (racer->getName() >= current->items[index]->getName()) {
        current->items[index + 1] = racer;
        current->numItems++;
        return true;
    }

    // Shift current item to the right
    current->items[index + 1] = current->items[index];

    // Recurse to next index
    return insertInLeaf(current, racer, index - 1);
}



// Determine which child to insert into
int Tree::findChildIndex(Node234* current, const string& name) const
{
    if (name < current->items[0]->getName())
        return 0;
    if (current->numItems == 1 || name < current->items[1]->getName())
        return 1;
    if (current->numItems == 2 || name < current->items[2]->getName())
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
bool Tree::display() const
{
    if(!root)
	return false;
    return displayRecursive(root, 0);
}

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
    for (int j = 0; j < indent; ++j) cout << ' ';

    // 3. Display current item
    current->items[index]->display();

    // 4. Display left child and continue recursion
    return displayItems(current, index - 1, indent);
}


//Remove all
//-----------------------------
bool Tree::remove_all()
{
    if(!root)
	return false;

    bool result = deleteAll(root);
    root = nullptr;
    return result;
}

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

//Deletes the chinldren 
bool Tree::deleteChildren(Node234*& current, int index)
{
    if (index >= Node234::MAX_CHILDREN)
        return true;

    deleteAll(current->children[index]);
    return deleteChildren(current, index + 1);
}

//Deletes the items in the node
bool Tree::deleteItems(Node234*& current, int index)
{
    if (index >= current->numItems)
        return true;

    delete current->items[index];
    current->items[index] = nullptr;

    return deleteItems(current, index + 1);
}





//__________________________________________________________________________
//This part will be for the game implementation, so that the user can play it

// Performs one round of the race recursively
bool Tree::raceRound(Node234* current) {
    if (!current) return true;


    // Move all racers in this node
    if (current->numItems > 0)
    {
        if (!current->items[0]->performMove()) current->items[0]->takeBreak();
        // RTTI check
        if (DogRacer* dog = dynamic_cast<DogRacer*>(current->items[0]))
            dog->bark();

        if (current->numItems > 1)
        {
            if (!current->items[1]->performMove()) current->items[1]->takeBreak();
            if (DogRacer* dog = dynamic_cast<DogRacer*>(current->items[1]))
                dog->bark();
        }
        if (current->numItems > 2)
        {
            if (!current->items[2]->performMove()) current->items[2]->takeBreak();
            if (DogRacer* dog = dynamic_cast<DogRacer*>(current->items[2]))
                dog->bark();
        }
    }
    // Recurse through children
    return raceRound(current->children[0]) &&
           raceRound(current->children[1]) &&
           raceRound(current->children[2]) &&
           raceRound(current->children[3]);
}

// Checks if any racer has reached the target
bool Tree::checkWinner(Node234* current, int target, string &winnerName) {
    if (!current) return false;

    if (current->numItems > 0 && current->items[0]->getPosition() >= target) {
        winnerName = current->items[0]->getName();
        return true;
    }
    if (current->numItems > 1 && current->items[1]->getPosition() >= target) {
        winnerName = current->items[1]->getName();
        return true;
    }
    if (current->numItems > 2 && current->items[2]->getPosition() >= target) {
        winnerName = current->items[2]->getName();
        return true;
    }

    return checkWinner(current->children[0], target, winnerName) ||
           checkWinner(current->children[1], target, winnerName) ||
           checkWinner(current->children[2], target, winnerName) ||
           checkWinner(current->children[3], target, winnerName);
}

// Fully recursive race loop
bool Tree::runRaceRecursive(Node234* current, int target, int round) {
    if (!current) return false;

    cout << "\n===== ROUND " << round << " =====\n";
    raceRound(root);          // move all racers
    display();                // display tree recursively

    string winner;
    if (checkWinner(root, target, winner)) {
        cout << "\n*** Winner: " << winner << " reached " << target << " units! ***\n";
        return true;
    }

    // Recurse to next round
    return runRaceRecursive(root, target, round + 1);
}

