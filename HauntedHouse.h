//Veniamin Velikoretskikh veniamin@pdx.edu
//CS302  Karla Fant  program#2




// HauntedHouse - manages all levels of the maze
// Each level will have its own doubly linked list

class HauntedHouse
{
public:
    HauntedHouse();                     // Default constructor
    HauntedHouse(const HauntedHouse & src); // Copy constructor
    HauntedHouse & operator=(const HauntedHouse & src); // Assignment operator
    ~HauntedHouse();                     // Destructor

    // Add obstacles to DLLs
    bool add_kid_obstacle(const KidObstacle & obj);
    bool add_teen_obstacle(const TeenObstacle & obj);
    bool add_adult_obstacle(const AdultObstacle & obj);

    bool display_all() const;            // Display all obstacles in the game

    // Retrieve obstacle by name (reads only, no modification)
    const KidObstacle * retrieve_kid(const char * name) const;
    const TeenObstacle * retrieve_teen(const char * name) const;
    const AdultObstacle * retrieve_adult(const char * name) const;

    // Remove obstacle by name
    bool remove_kid(const char * name);
    bool remove_teen(const char * name);
    bool remove_adult(const char * name);

private:
    Node_DLL<KidObstacle> * kid_head;       // DLL head for kid obstacles
    Node_DLL<TeenObstacle> * teen_head;     // DLL head for teen obstacles
    Node_DLL<AdultObstacle> * adult_head;   // DLL head for adult obstacles

    // Helpers for DLL operations
    bool copy_dll(Node_DLL<Obstacle> *& dest, Node_DLL<Obstacle> * src);
    bool clear_dll(Node_DLL<Obstacle> *& head);

    // Recursive helpers for insert, display, remove, retrieve
    bool insert_recursive(Node_DLL<Obstacle> *& head, const Obstacle & obj);
    bool display_recursive(Node_DLL<Obstacle> * head) const;
    bool remove_recursive(Node_DLL<Obstacle> *& head, const char * name);
    const Obstacle * retrieve_recursive(Node_DLL<Obstacle> * head, const char * name) const;
}
