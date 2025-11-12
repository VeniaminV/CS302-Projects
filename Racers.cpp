//Veniamin Velikoretskikh veniamin@pdx.edu
//CS302 Karla Fant 

//Racers.cpp
/*
This file will contain for each class of the racer the implementation of the 
constructors, copy constructors, assignment operators. It will also have the 
implementation for the virtual functions all are upcasting except the bark 
function in DogRacer which will be donwcasting. 
*/

#include "Racers.h"

//------------------Racer class ---------------------------------
//Dosen't need virtual function implementation, each derived class 
//will have it's own implementation
Racer::Racer() : name("Unknown"), position(0), stamina(100) {}

Racer::Racer(const string & name, int position, int stamina)
	: name(name), position(position), stamina(stamina) {}

Racer::Racer(const Racer & src)
	: name(src.name), position(src.position), stamina(src.stamina)  {}

Racer & Racer :: operator = (const Racer & rhs) 
{
	if(this != &rhs)
	{
		name = rhs.name;
		position = rhs.position;
		stamina = rhs.stamina;
	}
	return *this;
}

Racer::~Racer() {}



//------------------DogRacer------------------------------------
DogRacer::DogRacer(const string & name)
        : Racer(name, 0, 120), tail_wag(5) {}

DogRacer::DogRacer(const DogRacer & src)
        : Racer(src), tail_wag(src.tail_wag) {}

DogRacer & DogRacer::operator=(const DogRacer & rhs) 
{
        if (this != &rhs) 
   	{
            Racer::operator=(rhs);
            tail_wag = rhs.tail_wag;
        }
        return *this;
}

DogRacer::~DogRacer() {}


bool DogRacer:: performMove()
{
	if(stamina <= 0) return false;
	position += 3 + tail_wag;
	stamina -= 10;
	return true;
}


bool DogRacer:: takeBreak()
{
	stamina += 15;
	if(stamina > 120) stamina = 120;
	return true;
}


bool DogRacer::display()
{
	cout << "Dog Racer " << name
	<< ", Position: " <<position
	<<", Stamina: " <<stamina
	<<", Tail Wag: " <<tail_wag
	<< endl;
	return true;
}


bool DogRacer::bark()
{
	cout << name << " says: Woof! Woof!" <<endl;
	return true;
}

Racer * DogRacer::copy() const 
{
	return new DogRacer(*this);
}


//------------------------MonsterRacer--------------------------
MonsterRacer::MonsterRacer(const string & name)
        : Racer(name, 0, 140), jump_height(4) {}

MonsterRacer::MonsterRacer(const MonsterRacer & src)
        : Racer(src), jump_height(src.jump_height) {}

MonsterRacer & MonsterRacer::operator=(const MonsterRacer & rhs) 
{
        if (this != &rhs) {
            Racer::operator=(rhs);
            jump_height = rhs.jump_height;
        }
        return *this;
}

MonsterRacer::~MonsterRacer() {}


bool MonsterRacer::performMove()
{
	if(stamina <= 0) return false;
	position += 5 * jump_height;
	stamina -= 20;
	return true;
}

bool MonsterRacer::takeBreak()
{
	stamina += 20;
	if(stamina > 140) stamina = 140;
	return true;
}

bool MonsterRacer::display()
{
	cout << "Monster Racer " << name
	<< ", Position: " << position 
	<< ", Stamina: " <<stamina
	<< ", Jump Height: " <<jump_height
	<< endl;
	return true;
}

Racer * MonsterRacer::copy() const 
{
	return new MonsterRacer(*this);
}


//-----------------------KidsRacer-------------------------------
KidRacer::KidRacer(const string & name)
       : Racer(name, 0, 80), snack_count(3) {}

KidRacer::KidRacer(const KidRacer & src)
       : Racer(src), snack_count(src.snack_count) {}

KidRacer & KidRacer::operator=(const KidRacer & rhs) 
{
       if (this != &rhs) {
           Racer::operator=(rhs);
           snack_count = rhs.snack_count;
       }
       return *this;
}

KidRacer::~KidRacer() {}

bool KidRacer::performMove() 
{
       if (stamina <= 0) return false;
       position += 4;
       stamina -= 15;
       return true;
}

bool KidRacer::takeBreak() 
{
       if (snack_count > 0) 
       {
           stamina += 25;
           snack_count--;
       }
       if (stamina > 100) stamina = 100;
       return true;
}

bool KidRacer::display()
{
       cout << "Kid Racer " << name
            << ", Position: " << position
            << ", Stamina: " << stamina
            << ", Snacks Left: " << snack_count
            << endl;
	return true;
}

Racer* KidRacer::copy() const 
{
       return new KidRacer(*this);
}


