// Veniamin Velikoretskikh veniamin@pdx.edu
// CS302 Karla Fant - Program #2
// HauntedHouse class manages DLLs for each age level

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

    bool add_kid_obstacle(const KidObstacle & obj);
    bool add_teen_obstacle(const TeenObstacle & obj);
    bool add_adult_obstacle(const AdultObstacle & obj);

    bool display_all() const;

    DLL<KidObstacle>& get_kids() { return kids; }
    DLL<TeenObstacle>& get_teens() { return teens; }
    DLL<AdultObstacle>& get_adults() { return adults; }


private:
    DLL<KidObstacle> kids;
    DLL<TeenObstacle> teens;
    DLL<AdultObstacle> adults;

};

