//Veniamin Velikoretskikh veniamin@pdx.edu

/*
Implemntation of HauntedHouse.h that manages 3 DLL
These functions will add objects to the end of DLL
Also displays all 3 lists
*/

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
    if (!kids.insert_back(obj)) {
        cerr << "Error: Failed to insert Kid obstacle.\n";
        return false;
    }
    return true;
}

bool HauntedHouse::add_teen_obstacle(const TeenObstacle & obj)
{
    if (!teens.insert_back(obj)) {
        cerr << "Error: Failed to insert Teens obstacle.\n";
        return false;
    }
    return true;
}

bool HauntedHouse::add_adult_obstacle(const AdultObstacle & obj)
{
    if (!adults.insert_back(obj)) {
        cerr << "Error: Failed to insert Adults obstacle.\n";
        return false;
    }
    return true;
}

bool HauntedHouse::display_all() const
{
    bool k = kids.display_all();
    bool t = teens.display_all();
    bool a = adults.display_all();

    if(!k && !t && !a)
    {
	cerr << "NO obstacles to display!\n";
	return false;
    }

    return true;
}
