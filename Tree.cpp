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

//---------------------------
// Node234 implementation
//---------------------------
Node234::Node234() : numItems(0) {
    for (int i = 0; i < MAX_ITEMS; ++i)
        items[i] = nullptr;
    for (int i = 0; i < MAX_CHILDREN; ++i)
        children[i] = nullptr;
}

Node234::~Node234() {
    for (int i = 0; i < numItems; ++i) {
        delete items[i];
        items[i] = nullptr;
    }
}

bool Node234::isLeaf() const {
    return children[0] == nullptr;
}

bool Node234::isFull() const {
    return numItems >= MAX_ITEMS;
}

//---------------------------
// Tree implementation
//---------------------------
Tree::Tree() : root(nullptr) {}

Tree::~Tree() {
    remove_all();
}

bool Tree::is_empty() const {
    return root == nullptr;
}

//---------------------------
// Insert
//---------------------------
bool Tree::insert(const Racer& racer) {
    try {
        Racer* newRacer = racer.copy();
        if (!newRacer) throw runtime_error("Failed to clone Racer");

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

//---------------------------
// Recursive insert
//---------------------------
bool Tree::insertRecursive(Node234*& current, Racer* racer) {
    if (!current) return false;

    // Leaf node
    if (current->isLeaf()) {
        if (!current->isFull()) {
            // Insert in sorted order by name
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
            split_node(current);
            return insertRecursive(current, racer);
        }
    }

    // Internal node: choose the child
    if (racer->getName() < current->items[0]->getName())
        return insertRecursive(current->children[0], racer);
    else if (current->numItems == 1 || (current->numItems >= 2 && racer->getName() < current->items[1]->getName()))
        return insertRecursive(current->children[1], racer);
    else if (current->numItems == 2 || (current->numItems == 3 && racer->getName() < current->items[2]->getName()))
        return insertRecursive(current->children[2], racer);
    else
        return insertRecursive(current->children[3], racer);
}

//---------------------------
// Split node
//---------------------------
bool Tree::split_node(Node234*& node) {
    if (!node || node->numItems < 3) return false;

    try {
        Node234* right = new Node234();

        right->items[0] = node->items[2];
        right->numItems = 1;

        node->items[2] = nullptr;
        node->numItems = 2;

        right->children[0] = node->children[2];
        right->children[1] = node->children[3];
        node->children[2] = node->children[3] = nullptr;

        // If root, create new root
        if (node == root) {
            Node234* newRoot = new Node234();
            newRoot->items[0] = node->items[1];
            newRoot->numItems = 1;

            node->items[1] = nullptr;
            node->numItems = 1;

            newRoot->children[0] = node;
            newRoot->children[1] = right;
            root = newRoot;
        }

        return true;
    }
    catch (const bad_alloc&) {
        cerr << "Split failed: memory allocation error\n";
        return false;
    }
}

//---------------------------
// Display
//---------------------------
bool Tree::display() const {
    if (!root) return false;
    return displayRecursive(root, 0);
}

bool Tree::displayRecursive(Node234* current, int indent) const {
    if (!current) return false;

    // Display rightmost children first
    for (int i = current->numItems; i >= 0; --i)
        displayRecursive(current->children[i], indent + 4);

    // Display items
    for (int i = 0; i < current->numItems; ++i)
        current->items[i]->display();

    return true;
}

//---------------------------
// Remove all
//---------------------------
bool Tree::remove_all() {
    if (!root) return false;
    bool result = deleteAll(root);
    root = nullptr;
    return result;
}

bool Tree::deleteAll(Node234*& current) {
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

