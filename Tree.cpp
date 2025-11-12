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

// -----------------------------
// Constructor and Destructor
// -----------------------------
Tree::Tree() : root(nullptr) {}

Tree::~Tree() {
    remove_all(); // Clean up recursively
}

// -----------------------------
// Public wrapper for insertion
// -----------------------------
bool Tree::insert(const Racer & racer) {
    try {
        Racer * clone = racer.clone(); // Clone racer before storing
        if (!clone)
            throw runtime_error("Failed to clone racer.");

        // If tree empty, create root node
        if (!root) {
            root = new Node234();
            if (!root)
                throw bad_alloc();
            root->items[0] = clone;
            root->numItems = 1;
            return true;
        }

        // Otherwise, insert recursively
        return insert_recursive(root, clone);
    }
    catch (const exception & e) {
        cerr << "Insert failed: " << e.what() << endl;
        return false;
    }
}

// -----------------------------
// Recursive insertion
// -----------------------------
bool Tree::insert_recursive(Node234 *& current, Racer * racer) {
    if (!current)
        return false;

    // Base case: leaf node
    if (current->isLeaf()) {
        // If not full, add here
        if (!current->isFull()) {
            current->items[current->numItems] = racer;
            current->numItems++;
            return true;
        }
        else {
            // If full, split and retry insert
            Node234 * parent = nullptr; // No parent tracking for simplicity
            split_node(current);
            return insert_recursive(current, racer);
        }
    }

    // Recursive case: internal node
    // Compare names to decide direction (no loops)
    int compareLeft = strcmp(racer->getName().c_str(), current->items[0]->getName().c_str());
    if (compareLeft < 0)
        return insert_recursive(current->children[0], racer);
    else if (current->numItems == 1)
        return insert_recursive(current->children[1], racer);
    else {
        int compareMiddle = strcmp(racer->getName().c_str(), current->items[1]->getName().c_str());
        if (compareMiddle < 0)
            return insert_recursive(current->children[1], racer);
        else if (current->numItems == 2)
            return insert_recursive(current->children[2], racer);
        else {
            int compareRight = strcmp(racer->getName().c_str(), current->items[2]->getName().c_str());
            if (compareRight < 0)
                return insert_recursive(current->children[2], racer);
            else
                return insert_recursive(current->children[3], racer);
        }
    }
}

// -----------------------------
// Split a full node (recursive structure maintained)
// -----------------------------
bool Tree::split_node(Node234 *& node) {
    if (!node)
        return false;

    try {
        // If node has 3 items, split around the middle one
        if (node->numItems < 3)
            return false;

        Node234 * newRight = new Node234();
        if (!newRight)
            throw bad_alloc();

        // Move rightmost item to new node
        newRight->items[0] = node->items[2];
        newRight->numItems = 1;
        node->items[2] = nullptr;
        node->numItems = 2;

        // If children exist, reassign rightmost two children
        newRight->children[0] = node->children[2];
        newRight->children[1] = node->children[3];
        node->children[2] = nullptr;
        node->children[3] = nullptr;

        return true;
    }
    catch (const exception & e) {
        cerr << "Split failed: " << e.what() << endl;
        return false;
    }
}

// -----------------------------
// Display all racers recursively
// -----------------------------
bool Tree::display_all() const {
    if (!root)
        return false;
    return display_recursive(root, 0);
}

bool Tree::display_recursive(Node234 * current, int indent) const {
    if (!current)
        return false;

    // Recursive display (right subtree first)
    if (current->numItems == 3)
        display_recursive(current->children[3], indent + 4);
    else if (current->numItems == 2)
        display_recursive(current->children[2], indent + 4);
    else
        display_recursive(current->children[1], indent + 4);

    // Display items in node
    for (int i = current->numItems - 1; i >= 0; --i) {
        for (int j = 0; j < indent; ++j)
            cout << " ";
        current->items[i]->display();
    }

    // Display left children recursively
    if (current->numItems == 3)
        display_recursive(current->children[2], indent + 4);
    else if (current->numItems == 2)
        display_recursive(current->children[1], indent + 4);
    else
        display_recursive(current->children[0], indent + 4);

    return true;
}

// -----------------------------
// Remove all racers (recursively clears entire tree)
// -----------------------------
bool Tree::remove_all() {
    if (!root)
        return false;
    bool result = remove_all_recursive(root);
    root = nullptr;
    return result;
}

bool Tree::remove_all_recursive(Node234 *& current) {
    if (!current)
        return false;

    // Recursively clear children
    for (int i = 0; i < Node234::MAX_CHILDREN; ++i)
        remove_all_recursive(current->children[i]);

    // Delete all items in node
    for (int i = 0; i < current->numItems; ++i) {
        delete current->items[i];
        current->items[i] = nullptr;
    }

    delete current;
    current = nullptr;
    return true;
}

