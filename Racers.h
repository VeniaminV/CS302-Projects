//Veniamin Velikoretskikh veniain@pdx.edu
//CS302 Karla Fant program 3

//Racers.h
//This file will include all the different types of racers
//This will be done witha  hierarchy and dynamic binding 

#include <strign>
#include <iostream>
using namespace std; 


class Racer 
{
public:
	Racer();
	Racer(const string &name, int position = 0, int stamina = 100);
	Racer(const Racer & src);
	Racer & operator = (const Racer & rhs);
	virtual ~Racer();

	virtual bool performMove();
	virtual bool takeBreak();
	virtual void display() const;

	virtual Racer* copy() const; //copy support

protected: 
	string name;
	int position;
	int stamina;

};

//--------------------- Dog Racer -------------------------
class DogRacer : public Racer
{
public: 
	DogRacer(const string & name);
	DogRacer(const DogRAcer & src);
	DogRacer & operator = (const DogRAcer & rhs);
	~DogRacer();

	bool performMove();
	bool takeBreak();
	bool display() const;	

	bool bark() const;

	Racer* copy() const;

protected:
	int tail_wag;  //How strong the tail is swagging

};

//---------------------Monster Racer ---------------------
class MonsterRacer : public Racer 
{
public: 
	MonsterRacer(const string & name);
	MonsterRacer(const MonsterRacer & src);
	MosnterRacer & operator = (const MonsterRacer & rhs);
	~MonsterRacer();

	bool performMove();
	bool takeBreak();
	bool display() const;	

	Racer* copy() const;

protected: 
	int jump_height;

};

//---------------------Kid Racer --------------------------
class KidRacer : public Racer 
{
public: 
	KidRacer(const string & name);
	KidRacer(const KidRacer & src);
	KidRacer & operator = (const KidRacer & rhs);
	~KidRacer();

	bool performMove();
	bool takeBreak();
	bool display() const;	

	Racer* copy() const;

protected:
	int snack_count;


};





