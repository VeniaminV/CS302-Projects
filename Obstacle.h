//Veniamin Velikoretskikh veniamin@pdx.edu
//CS302 Karla Fant  program #2


/*
This file contains the class prototypes for the Obstacle base class,
its three derived classes (KidObstacle, TeenObstacle, AdultObstacle),
and the HauntedHouse class that manages the game’s data structures.
All obstacle levels are now stored in doubly linked lists (DLL).
*/


#include <iostream>
#include <cstring>
#include <string>

using namespace std;

//------------------ Base Class: Obstacle ------------------

class Obstacle
{
public:
    Obstacle();
    Obstacle(const char * name, const string & msg, int move);
    Obstacle(const Obstacle & op2);
    Obstacle & operator=(const Obstacle & op2);
    ~Obstacle();

    int display_info() const;
    int trigger_event() const;

    const char * get_name() const { return name; }

    // Operator overloads
    bool operator==(const Obstacle & op2) const;
    bool operator!=(const Obstacle & op2) const;
    bool operator<(const Obstacle & op2) const;
    bool operator<=(const Obstacle & op2) const;
    bool operator>(const Obstacle & op2) const;
    bool operator>=(const Obstacle & op2) const;

    Obstacle operator+(const Obstacle & op2) const;
    Obstacle & operator+=(const Obstacle & op2);
    Obstacle operator-(const Obstacle & op2) const;
    Obstacle & operator-=(const Obstacle & op2);

    friend ostream & operator<<(ostream & out, const Obstacle & op2);
    friend istream & operator>>(istream & in, Obstacle & op2);

protected:
    char * name;
    string secret_message;
    int movement_effect;

    bool set_name(const char * src);
    bool clear_name();
};

//------------------ Derived Class: KidObstacle ------------------

class KidObstacle : public Obstacle
{
public:
    KidObstacle();
    KidObstacle(const char * name, const string & msg, int move, const char * reward);
    KidObstacle(const KidObstacle & op2);
    KidObstacle & operator=(const KidObstacle & op2);
    ~KidObstacle();

    int display_info() const;
    int trigger_event() const;

    bool operator==(const KidObstacle & op2) const;

    friend ostream & operator<<(ostream & out, const KidObstacle & op2);
    friend istream & operator>>(istream & in, KidObstacle & op2);

private:
    char * reward;

    bool set_reward(const char * src);
    bool clear_reward();
};

//------------------ Derived Class: TeenObstacle ------------------

class TeenObstacle : public Obstacle
{
public:
    TeenObstacle();
    TeenObstacle(const char * name, const string & msg, int move, const string & scare);
    TeenObstacle(const TeenObstacle & op2);
    TeenObstacle & operator=(const TeenObstacle & op2);
    ~TeenObstacle();

    int display_info() const;
    int trigger_event() const;

    bool operator==(const TeenObstacle & op2) const;

    friend ostream & operator<<(ostream & out, const TeenObstacle & op2);
    friend istream & operator>>(istream & in, TeenObstacle & op2);

private:
    string scare_type;
};

//------------------ Derived Class: AdultObstacle ------------------

class AdultObstacle : public Obstacle
{
public:
    AdultObstacle();
    AdultObstacle(const char * name, const string & msg, int move, const string & challenge);
    AdultObstacle(const AdultObstacle & op2);
    AdultObstacle & operator=(const AdultObstacle & op2);
    ~AdultObstacle();

    int display_info() const;
    int trigger_event() const;

    bool operator==(const AdultObstacle & op2) const;

    friend ostream & operator<<(ostream & out, const AdultObstacle & op2);
    friend istream & operator>>(istream & in, AdultObstacle & op2);

private:
    string challenge_text;
};
