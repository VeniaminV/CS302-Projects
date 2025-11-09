// Veniamin Velikoretskikh veniamin@pdx.edu
// CS302 Karla Fant - Program #2
/*
HauntedHouse class groups three doubly linked lists of obstacles
which are seperated by age category. kids, teens, adults.
The DLL class implements recursive behaivior in the Node.tpp file
*/

#pragma once
#include "Obstacle.h"
#include "Node.h"

class HauntedHouse
{
public:
    HauntedHouse();
    HauntedHouse(const HauntedHouse & src);
    HauntedHouse & operator=(const HauntedHouse & src);
    ~HauntedHouse();

//Adds an obstacle to the end of the corresponding list
    bool add_kid_obstacle(const KidObstacle & obj);
    bool add_teen_obstacle(const TeenObstacle & obj);
    bool add_adult_obstacle(const AdultObstacle & obj);

//Displays all obstacles across the 3 lists
    bool display_all() const;

//Gets access to the lists
    DLL<KidObstacle>& get_kids() { return kids; }
    DLL<TeenObstacle>& get_teens() { return teens; }
    DLL<AdultObstacle>& get_adults() { return adults; }


private:
    DLL<KidObstacle> kids;
    DLL<TeenObstacle> teens;
    DLL<AdultObstacle> adults;

};

