//veniamin velikoretskikh
/*

#include <iostream>
#include <cstring>      
#include <string>      
//#include "Obstacle.h"   
#include "HauntedHouse.h"

using namespace std;
int main()
{
    srand(time(nullptr)); // seed random number generator
    int move = rand() % 5 - 2; // random movement effect from -2 to +2

    HauntedHouse house;

    house.add_kid_obstacle(KidObstacle("CandyGhost", "You get candy!", 3, "Candy Bag"));
    house.add_teen_obstacle(TeenObstacle("JumpScare", "You scream!", -1, "Loud Noise"));
    house.add_adult_obstacle(AdultObstacle("VampireLord", "Solve my riddle!", -2, 
                                           "Count the bats in this hall!"));

    cout << "\n--- Display All Obstacles ---\n";
    house.display_all();

return 0;
}
*/
#include <iostream>
#include <string>
#include "HauntedHouse.h"

using namespace std;

// Create a simple random addition problem and return correct answer
int generate_riddle()
{
    int a = rand() % 5 + 1;
    int b = rand() % 5 + 1;

    cout << "\n🧛 RIDDLE: " << a << " + " << b << " = ?" << endl;
    return a + b;
}


// Recursive play function for DLL
template <typename Type>
bool play_recursive(DLL<Type>& list, Node_DLL<Type>* current)
{
    if (!current)
    {
        cout << "\n🎉 You made it through the haunted house!\n";
        return true;
    }

    cout << "\n====================================\n";
    int move = current->data.trigger_event();

    if (node->data.get_level() == "Adult")
{
    int correct_answer = generate_riddle();
    int guess;
    cin >> guess;

    if (guess == correct_answer)
    {
        cout << "✅ Correct! The vampire lets you move forward." << endl;
        move = 2;
    }
    else
    {
        cout << "❌ Incorrect! The vampire pushes you back!" << endl;
        move = -1;
    }
}

    cout << "Movement effect: " << move << endl;

    // Remove current obstacle AFTER event
    const char* name = current->data.get_name();
    list.remove_by_name(name);

    // Move to next or previous node based on movement
    Node_DLL<Type>* next = current;
    if (move > 0)
    {
        while (move-- && next) next = next->next;
    }
    else if (move < 0)
    {
        while (move++ && next) next = next->prev;
    }

    if (!next)
        next = list.get_head(); // Teleport to start if fall off list

    // Ask if player continues
    cout << "\nContinue? (y/n): ";
    string cont;
    cin >> cont;
    if (cont != "y")
    {
        cout << "\n👻 You fled the haunted house early...\n";
        return false;
    }

    return play_recursive(list, next);
}

// Choose level and start
bool play_game(HauntedHouse& house)
{
    int choice;
    cout << "\nChoose a level to begin:\n"
         << " 1 - Monster Candy Trail (Kids)\n"
         << " 2 - Screamer Alley (Teens)\n"
         << " 3 - Vampire Dungeon (Adults)\n"
         << "Choice: ";
    cin >> choice;

    if (choice == 1 && house.get_kids().get_head())
        return play_recursive(house.get_kids(), house.get_kids().get_head());

    if (choice == 2 && house.get_teens().get_head())
        return play_recursive(house.get_teens(), house.get_teens().get_head());

    if (choice == 3 && house.get_adults().get_head())
        return play_recursive(house.get_adults(), house.get_adults().get_head());

    cout << "Invalid choice or no obstacles in this level.\n";
    return false;
}

// MAIN
int main()
{
    srand(time(nullptr));

    HauntedHouse house;

    house.add_kid_obstacle(KidObstacle("CandyGhost", "You get candy!", 3, "Candy Bag"));
    house.add_kid_obstacle(KidObstacle("PumpkinPuff", "You find pumpkin treats!", 1, "Pumpkin Pie"));

    house.add_teen_obstacle(TeenObstacle("JumpScare", "You scream!", -1, "Loud Noise"));
    house.add_teen_obstacle(TeenObstacle("CreepyCrawler", "Something touches your leg!", -1, "Spider Brush"));

    house.add_adult_obstacle(AdultObstacle("VampireLord", "Solve my riddle!", -1,
                                           "Count the bats in this hall!"));
    house.add_adult_obstacle(AdultObstacle("BloodKnight", "Answer or suffer!", -1,
                                           "How many coffins are there?"));

    cout << "\n--- Haunted House Contents ---\n";
    house.display_all();

    cout << "\n--- Start Your Adventure ---\n";
    play_game(house);

    cout << "\n--- Game Over ---\n";
    return 0;
}

