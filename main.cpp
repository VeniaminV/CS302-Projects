//veniamin velikoretskikh veniamin@pdx.edu
//CS302 program 2

//This will be the game interface

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "HauntedHouse.h"

using namespace std;

int main()
{
    srand(time(nullptr));
    HauntedHouse house;

    //Adds obstacles
    house.add_kid_obstacle(KidObstacle("CandyGhost", "You found tasty candy!", 1, "Lollipop"));
    house.add_kid_obstacle(KidObstacle("PumpkinPal", "A friendly pumpkin!", 1, "Gold Star"));
    house.add_kid_obstacle(KidObstacle("BunnyBuddy", "Cute spooky bunny!", 1, "Stuffed Toy"));
    house.add_kid_obstacle(KidObstacle("MagicCauldron", "You get a magic treat!", 1, "Magic Potion"));
    house.add_kid_obstacle(KidObstacle("FriendlyBat", "A bat brings snacks!", 1, "Chocolate Bar"));

    house.add_teen_obstacle(TeenObstacle("ShadowHands", "Creepy whispers appear!", 0, "Shadow scare"));
    house.add_teen_obstacle(TeenObstacle("DarkCloak", "Something moves fast!", 0, "Cloak Jump"));
    house.add_teen_obstacle(TeenObstacle("GhoulEyes", "Eyes watch you!", 0, "Eye Flash"));
    house.add_teen_obstacle(TeenObstacle("CreepyDoll", "A doll laughs!", 0, "Doll Scare"));
    house.add_teen_obstacle(TeenObstacle("HallwaySpirit", "A ghost floats by!", 0, "Spirit Scream"));

    house.add_adult_obstacle(AdultObstacle("VampireLord", "A vampire challenges you!", 0, "Answer my riddle!"));
    house.add_adult_obstacle(AdultObstacle("BatSwarm", "Solve fast or retreat!", 0, "Count the wings!"));
    house.add_adult_obstacle(AdultObstacle("ZombieScholar", "Brainless? Let's see!", 0, "Solve math quickly!"));
    house.add_adult_obstacle(AdultObstacle("RiddleSpider", "It weaves numbers...", 0, "Answer correctly!"));
    house.add_adult_obstacle(AdultObstacle("MummyMaster", "Mystery wrapped tight!", 0, "Don't stumble!"));

    //Select teh difficulty
    cout << "Welcome to the Haunted House Game!\n";
    cout << "Choose difficulty:\n1 - Kids\n2 - Teens\n3 - Adults\nEnter choice: ";

    int choice;
    cin >> choice;
    cin.ignore();

    DLL<KidObstacle>* klist = nullptr;
    DLL<TeenObstacle>* tlist = nullptr;
    DLL<AdultObstacle>* alist = nullptr;

    if (choice == 1) klist = &house.get_kids();
    else if (choice == 2) tlist = &house.get_teens();
    else if (choice == 3) alist = &house.get_adults();
    else { cout << "Invalid choice. Exiting.\n"; return 0; }

    cout << "\nThere are 5 obstacles ahead!\n\n";

    int position = 0;
    const int GOAL = 5;

    // ---------------- Main Game Loop ----------------
    while (position < GOAL)
    {
        Node_DLL<KidObstacle>* kptr = nullptr;
        Node_DLL<TeenObstacle>* tptr = nullptr;
        Node_DLL<AdultObstacle>* aptr = nullptr;

        if (klist) kptr = klist->get_head();
        if (tlist) tptr = tlist->get_head();
        if (alist) aptr = alist->get_head();

        for (int i = 0; i < position; ++i) {
            if (kptr) kptr = kptr->next;
            if (tptr) tptr = tptr->next;
            if (aptr) aptr = aptr->next;
        }

        cout << "\n";

        // ---------------- KIDS MODE ----------------
        if (klist) {
            cout << "You encounter: " << kptr->data.get_name() << "!\n";
            kptr->data.trigger_event();
            cout << "Reward earned!\n";
            position++;
        }

        // ---------------- TEENS MODE ----------------
        else if (tlist) {
            cout << "You encounter: " << tptr->data.get_name() << "!\n";
            tptr->data.trigger_event();

            char scared;
            do {
                cout << "Did you get scared? (y/n): ";
                cin >> scared;
                cin.ignore();
            } while (scared != 'y' && scared != 'n');

            if (scared == 'y') {
                cout << "You jump back!\n";
                position--;
                if (position < 0) position = 0;
            } else {
                cout << "You move forward bravely.\n";
                position++;
            }
        }

        // ---------------- ADULTS MODE ----------------
        else if (alist) {
            cout << "A challenge obstacle appears: " << aptr->data.get_name() << "!\n";

            int action = rand() % 3;

            if (action == 0) {
                int a = rand() % 10;
                int b = rand() % 10;
                int answer;

                cout << "Solve: " << a << " + " << b << " = ? ";
                cin >> answer;
                cin.ignore();

                if (answer == a + b) {
                    cout << "Correct! Move forward 2.\n";
                    position += 2;
                } else {
                    cout << "Wrong! Go back 1.\n";
                    position--;
                    if (position < 0) position = 0;
                }
            } else if (action == 1) {
                cout << "You carefully pass forward.\n";
                position++;
            } else {
                cout << "Surprise scare pushes you back!\n";
                position--;
                if (position < 0) position = 0;
            }
        }

        cout << "You are now on obstacle #" << (position + 1) << " / " << GOAL << endl;
        cout << "Press ENTER to continue...";
        cin.ignore();
    }

    cout << "\nYOU MADE IT THROUGH THE HAUNTED HOUSE!\n";
    return 1;
}

