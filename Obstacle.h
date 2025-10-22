//Veniamin Velikoretskikh veniamin@pdx.edu
//CS302 Karla Fant  program #2


/*
This file contains the class prototypes for the Obstacle base class,
its three derived classes (KidObstacle, TeenObstacle, AdultObstacle),
*/

/*
Veniamin Velikoreskikh  veniamin@pdx.edu
CS302 Fall 2025 - Program 2: Haunted House Maze
Karla Fant

This file contains the class prototypes for the Obstacle base class,
its three derived classes (KidObstacle, TeenObstacle, AdultObstacle),
and the HauntedHouse class that manages the game’s data structures.
All obstacle levels are now stored in doubly linked lists (DLL).
*/

#include <cstring>
#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

class KidObstacle;
class TeenObstacle;
class AdultObstacle;



// Base class for all obstacles
class Obstacle
{
public:
    Obstacle();                                         // Default constructor
    Obstacle(const char * name, const string & msg, int move); // Constructor
    Obstacle(const Obstacle & src);                     // Copy constructor
    Obstacle & operator=(const Obstacle & src);         // Assignment operator
    ~Obstacle();                                        // Destructor

    int display_info() const;                          // Show info about the obstacle
    bool trigger_event();                               // Apply obstacle effect (move forward/backward)
    const char * get_name() const { return name; }     // Getter for obstacle name

    // Operator overloads
    bool operator==(const Obstacle& rhs) const;   // equality
    bool operator!=(const Obstacle& rhs) const;   // inequality
    bool operator<(const Obstacle& rhs) const;    // less than
    bool operator<=(const Obstacle& rhs) const;   // less than or equal
    bool operator>(const Obstacle& rhs) const;    // greater than
    bool operator>=(const Obstacle& rhs) const;   // greater than or equal

    //add movement effects
    Obstacle operator+(const Obstacle& rhs) const;  
    Obstacle& operator+=(const Obstacle& rhs);      


    friend ostream & operator<<(ostream & out, const Obstacle & src); // Print obstacle
    friend istream & operator>>(istream & in, Obstacle & src);        // Read obstacle

private:
    char * name;               // Dynamically allocated name
    string secret_message;     // Message shown to player when triggered
    int movement_effect;       // Number of steps to move forward/backward

    // Helper functions for dynamic memory
    bool set_name(const char * src);  // Allocates & sets name
    bool clear_name();                // Frees name memory
};


//---------------------------------------------------------------------------------------------
// KidObstacle 
class KidObstacle : public Obstacl
{
public:
    KidObstacle(); // Default constructor
    KidObstacle(const char * name, const string & msg, int move, const char * reward); // constructor
    KidObstacle(const KidObstacle & src);           // Copy constructor
    KidObstacle & operator=(const KidObstacle & src); // Assignment operator
    ~KidObstacle();                                 // Destructor

    int display_info() const;                      // Show info about this kid obstacle
    bool trigger_event();                           // Apply effect and display reward

    const char * get_reward() const { return reward; } // Get reward name

    bool operator==(const KidObstacle & src) const;    // Compare two kid obstacles
    friend ostream & operator<<(ostream & out, const KidObstacle & src); // Print obstacle
    friend istream & operator>>(istream & in, KidObstacle & src);        // Read obstacle

private:
    char * reward; // Dynamically allocated reward string

    bool set_reward(const char * src); // Allocate & set reward
    bool clear_reward();               // Free reward memory
};


//---------------------------------------------------------------------------------------------
// TeenObstacle
class TeenObstacle : public Obstacle
{
public:
    TeenObstacle(); // Default constructor
    TeenObstacle(const char * name, const string & msg, int move, const string & scareType); //constructor
    ~TeenObstacle();                                 // Destructor

    int display_info() const;                      // Show obstacle info
    bool trigger_event();                           // Apply effect

    const string & get_scare() const { return scare_type; } // Get scare type

    bool operator==(const TeenObstacle & src) const;       // Compare obstacles
    friend ostream & operator<<(ostream & out, const TeenObstacle & src); // Print
    friend istream & operator>>(istream & in, TeenObstacle & src);        // Read

private:
    string scare_type; // Type of scary object: ghost, spider, skeleton
};


//---------------------------------------------------------------------------------------------
// AdultObstacle 
class AdultObstacle : public Obstacle
{
public:
    AdultObstacle(); // Default constructor
    AdultObstacle(const char * name, const string & msg, int move, const string & challenge); // Constructor
    ~AdultObstacle();                                 // Destructor

    int display_info() const;                        // Show obstacle info
    bool trigger_event();                             // Apply effect

    const string & get_challenge() const { return challenge_text; } // Get riddle/puzzle

    bool operator==(const AdultObstacle & src) const;       // Compare obstacles
    friend ostream & operator<<(ostream & out, const AdultObstacle & src); // Print
    friend istream & operator>>(istream & in, AdultObstacle & src);        // Read

private:
    string challenge_text; // Text of puzzle or riddle
};

