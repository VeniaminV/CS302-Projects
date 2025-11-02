//veniamin velikoretskikh


#include <iostream>
#include <cstring>      
#include <string>      
//#include "Obstacle.h"   
#include "HauntedHouse.h"

using namespace std;
int main()
{

    HauntedHouse house;

    house.add_kid_obstacle(KidObstacle("CandyGhost", "You get candy!", 3, "Candy Bag"));
    house.add_teen_obstacle(TeenObstacle("JumpScare", "You scream!", -1, "Loud Noise"));
    house.add_adult_obstacle(AdultObstacle("VampireLord", "Solve my riddle!", -2, 
                                           "Count the bats in this hall!"));

    cout << "\n--- Display All Obstacles ---\n";
    house.display_all();



return 0;
}
