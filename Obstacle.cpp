//Veniamin Velikoretskikh venimain@pdx.edu
//CS302 Fall 2025 Karla Fant

//This file will have the function and operator implementation 
//for the Obsticle.  

// Veniamin Velikoretskikh veniamin@pdx.edu
// CS302 Karla Fant - Program #2
// Implementation for Obstacle classes

#include "Obstacle.h"
#include <iostream>
#include <cstring>
using namespace std;

// Base Class - Obstacle
/******************************************************************************/

Obstacle::Obstacle() : name(nullptr), secret_message(""), movement_effect(0) {}

Obstacle::Obstacle(const char * n, const string & msg, int move)
    : secret_message(msg), movement_effect(move)
{
    set_name(n);
}

Obstacle::Obstacle(const Obstacle & op2)
    : secret_message(op2.secret_message), movement_effect(op2.movement_effect)
{
    set_name(op2.name);
}

Obstacle & Obstacle::operator=(const Obstacle & op2)
{
    if (this != &op2)
    {
        clear_name();
        set_name(op2.name);
        secret_message = op2.secret_message;
        movement_effect = op2.movement_effect;
    }
    return *this;
}

Obstacle::~Obstacle()
{
    clear_name();
}

bool Obstacle::set_name(const char * src)
{
    if (!src) return false;
    name = new char[strlen(src) + 1];
    strcpy(name, src);
    return true;
}

bool Obstacle::clear_name()
{
    if (name)
    {
        delete [] name;
        name = nullptr;
    }
    return true;
}

int Obstacle::display_info() const
{
    cout << "Obstacle: " << (name ? name : "(no name)")
         << ", Move: " << movement_effect
         << ", Message: " << secret_message << endl;
    return movement_effect;
}

int Obstacle::trigger_event() const
{
    cout << secret_message << endl;
    return movement_effect;
}


// Obstacle Operators
/******************************************************************************/

bool Obstacle::operator==(const Obstacle & op2) const
{
    return (strcmp(name, op2.name) == 0);
}

bool Obstacle::operator!=(const Obstacle & op2) const
{
    return !(*this == op2);
}

bool Obstacle::operator<(const Obstacle & op2) const
{
    return (strcmp(name, op2.name) < 0);
}

bool Obstacle::operator<=(const Obstacle & op2) const
{
    return (strcmp(name, op2.name) <= 0);
}

bool Obstacle::operator>(const Obstacle & op2) const
{
    return (strcmp(name, op2.name) > 0);
}

bool Obstacle::operator>=(const Obstacle & op2) const
{
    return (strcmp(name, op2.name) >= 0);
}

Obstacle Obstacle::operator+(const Obstacle & op2) const
{
    return Obstacle(name, secret_message + op2.secret_message,
                    movement_effect + op2.movement_effect);
}

Obstacle & Obstacle::operator+=(const Obstacle & op2)
{
    secret_message += op2.secret_message;
    movement_effect += op2.movement_effect;
    return *this;
}

Obstacle Obstacle::operator-(const Obstacle & op2) const
{
    return Obstacle(name, secret_message, movement_effect - op2.movement_effect);
}

Obstacle & Obstacle::operator-=(const Obstacle & op2)
{
    movement_effect -= op2.movement_effect;
    return *this;
}

ostream & operator<<(ostream & out, const Obstacle & op2)
{
    out << "Obstacle: " << (op2.name ? op2.name : "(no name)")
        << ", Move: " << op2.movement_effect
        << ", Msg: " << op2.secret_message;
    return out;
}

istream & operator>>(istream & in, Obstacle & op2)
{
    char buffer[128];

    cout << "Enter obstacle name: ";
    in.getline(buffer, 128);
    op2.set_name(buffer);

    cout << "Enter secret message: ";
    getline(in, op2.secret_message);

    cout << "Enter movement effect: ";
    in >> op2.movement_effect;
    in.ignore();

    return in;
}


// KidObstacle
/******************************************************************************/

KidObstacle::KidObstacle() : Obstacle(), reward(nullptr) {}

KidObstacle::KidObstacle(const char * n, const string & msg, int move, const char * r)
    : Obstacle(n, msg, move)
{
    set_reward(r);
}

KidObstacle::KidObstacle(const KidObstacle & op2) : Obstacle(op2)
{
    set_reward(op2.reward);
}

KidObstacle & KidObstacle::operator=(const KidObstacle & op2)
{
    if (this != &op2)
    {
        Obstacle::operator=(op2);
        clear_reward();
        set_reward(op2.reward);
    }
    return *this;
}

KidObstacle::~KidObstacle()
{
    clear_reward();
}

bool KidObstacle::set_reward(const char * src)
{
    if (!src) return false;
    reward = new char[strlen(src) + 1];
    strcpy(reward, src);
    return true;
}

bool KidObstacle::clear_reward()
{
    if (reward)
    {
        delete [] reward;
        reward = nullptr;
    }
    return true;
}

int KidObstacle::display_info() const
{
    Obstacle::display_info();
    cout << "Reward: " << (reward ? reward : "(none)") << endl;
    return movement_effect;
}

int KidObstacle::trigger_event() const
{
    cout << "Reward: " << (reward ? reward : "(none)") << endl;
    return Obstacle::trigger_event();
}

bool KidObstacle::operator==(const KidObstacle & op2) const
{
    return (Obstacle::operator==(op2) && strcmp(reward, op2.reward) == 0);
}

ostream & operator<<(ostream & out, const KidObstacle & op2)
{
    out << static_cast<const Obstacle &>(op2)
        << ", Reward: " << (op2.reward ? op2.reward : "(none)");
    return out;
}

istream & operator>>(istream & in, KidObstacle & op2)
{
    in >> static_cast<Obstacle &>(op2);
    char buffer[128];
    cout << "Enter reward: ";
    in.getline(buffer, 128);
    op2.set_reward(buffer);
    return in;
}


//TeenObstacle
/******************************************************************************/

TeenObstacle::TeenObstacle() : Obstacle(), scare_type("") {}
TeenObstacle::TeenObstacle(const char * n, const string & msg, int move, const string & s)
    : Obstacle(n, msg, move), scare_type(s) {}
TeenObstacle::TeenObstacle(const TeenObstacle & op2)
    : Obstacle(op2), scare_type(op2.scare_type) {}
TeenObstacle & TeenObstacle::operator=(const TeenObstacle & op2)
{
    if (this != &op2)
    {
        Obstacle::operator=(op2);
        scare_type = op2.scare_type;
    }
    return *this;
}
TeenObstacle::~TeenObstacle() {}

int TeenObstacle::display_info() const
{
    Obstacle::display_info();
    cout << "Scare type: " << scare_type << endl;
    return movement_effect;
}

int TeenObstacle::trigger_event() const
{
    cout << "Boo! It's a " << scare_type << "!" << endl;
    return Obstacle::trigger_event();
}

bool TeenObstacle::operator==(const TeenObstacle & op2) const
{
    return (Obstacle::operator==(op2) && scare_type == op2.scare_type);
}

ostream & operator<<(ostream & out, const TeenObstacle & op2)
{
    out << static_cast<const Obstacle &>(op2)
        << ", Scare: " << op2.scare_type;
    return out;
}

istream & operator>>(istream & in, TeenObstacle & op2)
{
    in >> static_cast<Obstacle &>(op2);
    cout << "Enter scare type: ";
    getline(in, op2.scare_type);
    return in;
}


// AdultObstacle
/******************************************************************************/

AdultObstacle::AdultObstacle() : Obstacle(), challenge_text("") {}
AdultObstacle::AdultObstacle(const char * n, const string & msg, int move, const string & c)
    : Obstacle(n, msg, move), challenge_text(c) {}
AdultObstacle::~AdultObstacle() {}

int AdultObstacle::display_info() const
{
    Obstacle::display_info();
    cout << "Challenge: " << challenge_text << endl;
    return movement_effect;
}

int AdultObstacle::trigger_event() const
{
    cout << "Challenge: " << challenge_text << endl;
    return Obstacle::trigger_event();
}

bool AdultObstacle::operator==(const AdultObstacle & op2) const
{
    return (Obstacle::operator==(op2) && challenge_text == op2.challenge_text);
}

ostream & operator<<(ostream & out, const AdultObstacle & op2)
{
    out << static_cast<const Obstacle &>(op2)
        << ", Challenge: " << op2.challenge_text;
    return out;
}

istream & operator>>(istream & in, AdultObstacle & op2)
{
    in >> static_cast<Obstacle &>(op2);
    cout << "Enter challenge text: ";
    getline(in, op2.challenge_text);
    return in;
}

