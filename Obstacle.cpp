//Veniamin Velikoretskikh venimain@pdx.edu
//CS302 Fall 2025 Karla Fant

//This file will have the function and operator implementation 
//for the Obsticle.  


#include "Obstacle.h"
#include <iostream>
#include <cstring>

using namespace std;

//------------------ Obstacle ------------------

// default constructor, constructor, copy constructor, assignment operator
Obstacle::Obstacle() : name(nullptr), secret_message(""), movement_effect(0) {}

Obstacle::Obstacle(const char* n, const string& msg, int move) : secret_message(msg), movement_effect(move) {
    set_name(n);
}

Obstacle::Obstacle(const Obstacle& src) : secret_message(src.secret_message), movement_effect(src.movement_effect) {
    set_name(src.name);
}

Obstacle& Obstacle::operator=(const Obstacle& src) {
    if (this != &src) {
        clear_name();
        set_name(src.name);
        secret_message = src.secret_message;
        movement_effect = src.movement_effect;
    }
    return *this;
}

Obstacle::~Obstacle() {
    clear_name();
}

//Sets the name
bool Obstacle::set_name(const char* src) {
    if (!src) return false;
    name = new char[strlen(src)+1];
    strcpy(name, src);
    return true;
}

//clears the dynamic memory
bool Obstacle::clear_name() {
    if (name) {
        delete[] name;
        name = nullptr;
    }
    return true;
}


int Obstacle::display_info() const {
    cout << "Obstacle: ";
    if (name)
        cout << name;
    else
        cout << "(no name)";
    
    cout << ", Move: " << movement_effect
         << ", Message: " << secret_message << endl;
    
    return movement_effect;
}


int Obstacle::trigger_event() const {
    cout << secret_message << endl;
    return movement_effect;
}

// Operator overloads
bool Obstacle::operator==(const Obstacle& rhs) const { return strcmp(name, rhs.name) == 0; }
bool Obstacle::operator!=(const Obstacle& rhs) const { return !(*this == rhs); }
bool Obstacle::operator<(const Obstacle& rhs) const { return strcmp(name, rhs.name) < 0; }
bool Obstacle::operator<=(const Obstacle& rhs) const { return strcmp(name, rhs.name) <= 0; }
bool Obstacle::operator>(const Obstacle& rhs) const { return strcmp(name, rhs.name) > 0; }
bool Obstacle::operator>=(const Obstacle& rhs) const { return strcmp(name, rhs.name) >= 0; }

Obstacle Obstacle::operator+(const Obstacle& rhs) const {
    return Obstacle(name, secret_message + rhs.secret_message, movement_effect + rhs.movement_effect);
}

Obstacle& Obstacle::operator+=(const Obstacle& rhs) {
    secret_message += rhs.secret_message;
    movement_effect += rhs.movement_effect;
    return *this;
}

Obstacle Obstacle::operator-(const Obstacle& rhs) const {
    return Obstacle(name, secret_message, movement_effect - rhs.movement_effect);
}

Obstacle& Obstacle::operator-=(const Obstacle& rhs) {
    movement_effect -= rhs.movement_effect;
    return *this;
}

// I/O
ostream& operator<<(ostream& out, const Obstacle& src) {
    out << "Obstacle: " << (src.name ? src.name : "") << ", Move: " << src.movement_effect
        << ", Msg: " << src.secret_message;
    return out;
}

istream& operator>>(istream& in, Obstacle& src) {
    string temp;
    char buffer[128];
    cout << "Enter obstacle name: ";
    in.getline(buffer, 128);
    src.set_name(buffer);

    cout << "Enter secret message: ";
    getline(in, src.secret_message);

    cout << "Enter movement effect: ";
    in >> src.movement_effect;
    in.ignore();
    return in;
}

//------------------ KidObstacle ------------------
KidObstacle::KidObstacle() : Obstacle(), reward(nullptr) {}
KidObstacle::KidObstacle(const char* n, const string& msg, int move, const char* r) : Obstacle(n,msg,move) {
    set_reward(r);
}
KidObstacle::KidObstacle(const KidObstacle& src) : Obstacle(src) { set_reward(src.reward); }
KidObstacle& KidObstacle::operator=(const KidObstacle& src) {
    if (this != &src) {
        Obstacle::operator=(src);
        clear_reward();
        set_reward(src.reward);
    }
    return *this;
}
KidObstacle::~KidObstacle() { clear_reward(); }

bool KidObstacle::set_reward(const char* src) {
    if (!src) return false;
    reward = new char[strlen(src)+1];
    strcpy(reward, src);
    return true;
}
bool KidObstacle::clear_reward() { if (reward) { delete[] reward; reward=nullptr;} return true; }

int KidObstacle::display_info() const {
    Obstacle::display_info();
    cout << "Reward: " << (reward ? reward : "") << endl;
    return movement_effect;
}
int KidObstacle::trigger_event() const {
    cout << "Reward: " << (reward ? reward : "") << endl;
    return Obstacle::trigger_event();
}

bool KidObstacle::operator==(const KidObstacle& rhs) const { return Obstacle::operator==(rhs) && strcmp(reward,rhs.reward)==0; }

ostream& operator<<(ostream& out, const KidObstacle& src) {
    out << static_cast<const Obstacle&>(src) << ", Reward: " << (src.reward?src.reward:"");
    return out;
}

istream& operator>>(istream& in, KidObstacle& src) {
    in >> static_cast<Obstacle&>(src);
    char buffer[128];
    cout << "Enter reward: ";
    in.getline(buffer,128);
    src.set_reward(buffer);
    return in;
}

//------------------ TeenObstacle ------------------
TeenObstacle::TeenObstacle() : Obstacle(), scare_type("") {}
TeenObstacle::TeenObstacle(const char* n, const string& msg, int move, const string& s) : Obstacle(n,msg,move), scare_type(s) {}
TeenObstacle::TeenObstacle(const TeenObstacle& src) : Obstacle(src), scare_type(src.scare_type) {}
TeenObstacle& TeenObstacle::operator=(const TeenObstacle& src) {
    if (this!=&src) {
        Obstacle::operator=(src);
        scare_type = src.scare_type;
    }
    return *this;
}
TeenObstacle::~TeenObstacle() {}

int TeenObstacle::display_info() const {
    Obstacle::display_info();
    cout << "Scare type: " << scare_type << endl;
    return movement_effect;
}
int TeenObstacle::trigger_event() const {
    cout << "Boo! It's a " << scare_type << "!" << endl;
    return Obstacle::trigger_event();
}
bool TeenObstacle::operator==(const TeenObstacle& rhs) const { return Obstacle::operator==(rhs) && scare_type==rhs.scare_type; }

ostream& operator<<(ostream& out, const TeenObstacle& src) {
    out << static_cast<const Obstacle&>(src) << ", Scare: " << src.scare_type;
    return out;
}
istream& operator>>(istream& in, TeenObstacle& src) {
    in >> static_cast<Obstacle&>(src);
    cout << "Enter scare type: ";
    getline(in, src.scare_type);
    return in;
}

//------------------ AdultObstacle ------------------
AdultObstacle::AdultObstacle() : Obstacle(), challenge_text("") {}
AdultObstacle::AdultObstacle(const char* n, const string& msg, int move, const string& c) : Obstacle(n,msg,move), challenge_text(c) {}
AdultObstacle::AdultObstacle(const AdultObstacle& src) : Obstacle(src), challenge_text(src.challenge_text) {}
AdultObstacle& AdultObstacle::operator=(const AdultObstacle& src) {
    if (this!=&src) {
        Obstacle::operator=(src);
        challenge_text = src.challenge_text;
    }
    return *this;
}
AdultObstacle::~AdultObstacle() {}

int AdultObstacle::display_info() const {
    Obstacle::display_info();
    cout << "Challenge: " << challenge_text << endl;
    return movement_effect;
}
int AdultObstacle::trigger_event() const {
    cout << "Challenge: " << challenge_text << endl;
    return Obstacle::trigger_event();
}
bool AdultObstacle::operator==(const AdultObstacle& rhs) const { return Obstacle::operator==(rhs) && challenge_text==rhs.challenge_text; }

ostream& operator<<(ostream& out, const AdultObstacle& src) {
    out << static_cast<const Obstacle&>(src) << ", Challenge: " << src.challenge_text;
    return out;
}
istream& operator>>(istream& in, AdultObstacle& src) {
    in >> static_cast<Obstacle&>(src);
    cout << "Enter challenge text: ";
    getline(in, src.challenge_text);
    return in;
}

