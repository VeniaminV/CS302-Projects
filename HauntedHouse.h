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

    const KidObstacle * retrieve_kid(const char * name) const;
    const TeenObstacle * retrieve_teen(const char * name) const;
    const AdultObstacle * retrieve_adult(const char * name) const;

    bool remove_kid(const char * name);
    bool remove_teen(const char * name);
    bool remove_adult(const char * name);

private:
    Node_DLL<KidObstacle> * kid_head;
    Node_DLL<TeenObstacle> * teen_head;
    Node_DLL<AdultObstacle> * adult_head;

    bool copy_dll(Node_DLL<Obstacle> *& dest, Node_DLL<Obstacle> * src);
    bool clear_dll(Node_DLL<Obstacle> *& head);

    bool insert_recursive(Node_DLL<Obstacle> *& head, const Obstacle & obj);
    bool display_recursive(Node_DLL<Obstacle> * head) const;
    bool remove_recursive(Node_DLL<Obstacle> *& head, const char * name);
    const Obstacle * retrieve_recursive(Node_DLL<Obstacle> * head, const char * name) const;
};

