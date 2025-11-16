//Veniamin Velikoretskikh veniamin@pdx.edu
//CS302 Karla Fant

//main.cpp
/*

*/
/*
#include "Tree.h"
#include <iostream>
using namespace std; 

int main()
{
        Tree raceTree;
	
        DogRacer d1("Buddy");
        MonsterRacer m1("Zorg");
        KidRacer k1("Alice");

        raceTree.insert(d1);
        raceTree.insert(m1);
        raceTree.insert(k1);

        cout << "\nDisplaying all racers in tree:\n";
        raceTree.display();

        raceTree.remove_all();
        return 0;


return 0;
}
*/

// Veniamin Velikoretskikh veniamin@pdx.edu
// CS302 – Program #3
// main.cpp
//
// This driver demonstrates dynamic binding, exception handling, RTTI, and a race
// simulation using a 2-3-4 tree to store polymorphic Racer objects.  
// The race continues until all racers run out of stamina.  
// One downcast occurs: if a DogRacer is stored, we call its bark() method.

#include "Tree.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// -----------------------------------------------------------
// Simulate a full race until all racers run out of stamina.
// Tree traversal is recursive (handled by Tree::display).
// -----------------------------------------------------------
void simulateRace(Tree & raceTree, Racer* racers[], int racerCount)
{
    bool anyActive = true;
    int round = 1;

    while (anyActive)
    {
        cout << "\n==============================\n";
        cout << "        ROUND " << round++ << "\n";
        cout << "==============================\n";

        anyActive = false;

        for (int i = 0; i < racerCount; ++i)
        {
            try {
                if (racers[i]->performMove())
                {
                    anyActive = true;

                    // RTTI requirement: dynamic_cast to DogRacer for bark()
                    if (DogRacer* dog = dynamic_cast<DogRacer*>(racers[i])) 
                    {
                        dog->bark(); // only works on dogs
                    }
                }
                else {
                    racers[i]->takeBreak();
                }
            }
            catch (const exception & e) {
                cerr << "Error during race action: " << e.what() << endl;
            }
        }

        cout << "\nCurrent standings (in tree):\n";
        raceTree.display();
    }

    cout << "\n==============================\n";
    cout << "        RACE FINISHED!\n";
    cout << "==============================\n";
}

// -----------------------------------------------------------
// Determine the winner (highest position).
// -----------------------------------------------------------
Racer* findWinner(Racer* racers[], int racerCount)
{
    Racer* winner = racers[0];

    for (int i = 1; i < racerCount; ++i)
    {
        if (racers[i]->getPosition() > winner->getPosition())
            winner = racers[i];
    }

    return winner;
}

// -----------------------------------------------------------
// MAIN PROGRAM
// -----------------------------------------------------------
int main()
{
    try {
        Tree raceTree;

        // Create racers dynamically so no slicing occurs
        Racer* r1 = new DogRacer("Buddy");
        Racer* r2 = new MonsterRacer("Zorg");
        Racer* r3 = new KidRacer("Alice");

        Racer* allRacers[] = { r1, r2, r3 };
        int racerCount = 3;

        // Insert into the recursive tree using deep copies
        for (int i = 0; i < racerCount; ++i)
        {
            if (!raceTree.insert(*allRacers[i]))
                throw runtime_error("Failed inserting racer into tree.");
        }

        cout << "\nInitial contestants in tree:\n";
        raceTree.display();

        // Perform the full race simulation
        simulateRace(raceTree, allRacers, racerCount);

        // Determine and display the winner
        Racer* winner = findWinner(allRacers, racerCount);

        cout << "\n🏁 WINNER: " << winner->getName()
             << " with position = " << winner->getPosition() << "!\n";

        // Cleanup
        raceTree.remove_all();
        for (int i = 0; i < racerCount; ++i)
            delete allRacers[i];
    }
    catch (const exception& e) {
        cerr << "\nFatal error: " << e.what() << endl;
    }

    return 0;
}

