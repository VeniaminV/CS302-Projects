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

// Recursive play function for DLL
template <typename Type>
bool play_recursive(DLL<Type>& list, Node_DLL<Type>* current)
{
    if (!current) return false;

    int move = current->data.trigger_event();
    cout << "You move " << move << " steps.\n";

    // Ask if player wants to continue
    string cont;
    cout << "Continue to next obstacle? (y/n): ";
    cin >> cont;

    if (cont != "y") return true;

    // Remove this obstacle
    list.remove_by_name(current->data.get_name());

    // Recurse on next
    return play_recursive(list, list.get_head());
}

// Start playing the game
bool play_game(HauntedHouse& house)
{
    int choice;
    cout << "Choose a level to play:\n1 - Kids\n2 - Teens\n3 - Adults\nChoice: ";
    cin >> choice;

    if (choice == 1 && house.get_kids().get_head())
        return play_recursive(house.get_kids(), house.get_kids().get_head());
    else if (choice == 2 && house.get_teens().get_head())
        return play_recursive(house.get_teens(), house.get_teens().get_head());
    else if (choice == 3 && house.get_adults().get_head())
        return play_recursive(house.get_adults(), house.get_adults().get_head());

    cout << "Invalid choice or no obstacles available.\n";
    return false;
}

int main()
{
    srand(time(nullptr));

    HauntedHouse house;

    house.add_kid_obstacle(KidObstacle("CandyGhost", "You get candy!", 3, "Candy Bag"));
    house.add_teen_obstacle(TeenObstacle("JumpScare", "You scream!", -1, "Loud Noise"));
    house.add_adult_obstacle(AdultObstacle("VampireLord", "Solve my riddle!", -2, 
                                           "Count the bats in this hall!"));

    cout << "\n--- All Obstacles ---\n";
    house.display_all();

    cout << "\n--- Start Playing ---\n";
    play_game(house);

    cout << "\n--- Game Over ---\n";
    return 0;
}

