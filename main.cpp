//Veniamin Velikoretskikh veniamin@pdx.edu
//CS302 Karla Fant

//main.cpp
/*
This file will contain the implementations for the race. I will have display menu funciton to have 
options for user to pick from. Also the add_racer function will determine what type of racer to add. 
The main will call functions and make the program run. 
*/
#include "Tree.h"
#include <iostream>
#include <string>
using namespace std;


//This function will display the menu in which the user can pick what he wants to do
int display_menu() {
    int choice;
    cout << "\n---- RACER MENU ----\n";
    cout << "1. Add Racer\n2. Display All Racers\n3. Delete All Racers\n4. Run Race\n5. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();
    return choice;
}

//This function will determine which racer to add
bool add_racer(Tree &raceTree) {
    cout << "\nSelect Racer Type:\n1. Dog Racer\n2. Monster Racer\n3. Kid Racer\nChoice: ";
    int type; cin >> type; cin.ignore();

    cout << "Enter Racer Name: ";
    string name; getline(cin, name);

    Racer* newRacer = nullptr;
    switch (type) {
        case 1: newRacer = new DogRacer(name); break;
        case 2: newRacer = new MonsterRacer(name); break;
        case 3: newRacer = new KidRacer(name); break;
        default: cout << "Invalid type!\n"; return false;
    }

    if (!raceTree.insert(*newRacer)) {
        cerr << "Failed to insert racer!\n";
        delete newRacer;
        return false;
    }

    cout << "Racer added successfully!\n";
    return true;
}


//This is the main interface
int main() {
    Tree raceTree;
    bool running = true;

    if (raceTree.is_empty()) cout << "Race tree initialized.\n";

    while (running) {
        int choice = display_menu();
        switch (choice) {
            case 1: add_racer(raceTree); break;
            case 2: 
                if (!raceTree.display()) cout << "No racers in tree.\n"; 
                break;
            case 3:
                if (raceTree.remove_all()) cout << "All racers deleted.\n"; 
                else cout << "Tree is empty.\n"; 
                break;
            case 4: raceTree.runRace(); break; // fully recursive race
            case 5: running = false; break;
            default: cout << "Invalid choice.\n";
        }
    }

    raceTree.remove_all();
    cout << "Exiting program.\n";
    return 0;
}

