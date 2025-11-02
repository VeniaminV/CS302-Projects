//Veniamin Velikoretskikh veniamin@pdx.edu

//HauntedHouse.h implementation

#include "HauntedHouse.h"

HauntedHouse::HauntedHouse() {}

HauntedHouse::HauntedHouse(const HauntedHouse & src)
    : kids(src.kids), teens(src.teens), adults(src.adults) {}

HauntedHouse & HauntedHouse::operator=(const HauntedHouse & src)
{
    if (this != &src)
    {
        kids = src.kids;
        teens = src.teens;
        adults = src.adults;
    }
    return *this;
}

HauntedHouse::~HauntedHouse() {}

bool HauntedHouse::add_kid_obstacle(const KidObstacle & obj)
{
    return kids.insert_back(obj);
}

bool HauntedHouse::add_teen_obstacle(const TeenObstacle & obj)
{
    return teens.insert_back(obj);
}

bool HauntedHouse::add_adult_obstacle(const AdultObstacle & obj)
{
    return adults.insert_back(obj);
}

bool HauntedHouse::display_all() const
{
    return kids.display_all() && teens.display_all() && adults.display_all();
}

