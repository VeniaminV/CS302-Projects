//Veniamin Velikoretskikh veniamin@pdx.edu
//CS302 Karla Fant

//main.cpp
/*

*/

#include "Tree.h"
#include <iostream>
using namespace std; 

int main()
{
        Tree raceTree;
	
        DogRacer d1("Buddy");
        MonsterRacer m1("Zorg");
        KidRacer k1("Alice");

        raceTree.insert(d1);
        raceTree.insert(m1);
        raceTree.insert(k1);

        cout << "\nDisplaying all racers in tree:\n";
        raceTree.display();

        raceTree.remove_all();
        return 0;


return 0;
}
