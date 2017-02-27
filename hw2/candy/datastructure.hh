// Definition of Datastructure class for UDS/Tiraka homework 2 -


#ifndef DATASTRUCTURE_HH
#define DATASTRUCTURE_HH

#include <string>
#include <vector>
#include <iostream>

using namespace std;

const std::string NOT_AVAILABLE = "Product not in warehouse.";
const std::string NOT_ENOUGH_CANDY = "Not enough candy available.";

struct Item
{
    vector<string> data_;
    Item* next_;
    Item* prev_;
};

class LinkedList
{
public:

    LinkedList();
    void add(Item* newItem);
    void remove(Item* candy);
    Item *getItem(string key) const;
    Item *getHead();
    void print(string key);
    ~LinkedList();

private:
    Item* head_;
};


class Datastructure
{
    public:

    Datastructure();

    ~Datastructure();

    // Adds candies to the datastructure (command "A")
    void add(const std::string& ID, const std::string& location,
            unsigned int amount, const std::string& name);
          
    // Removes candies from the datastructure (command "D")
    void substract(const std::string& ID, unsigned int amount);

    // Finds candy and prints its status (command "F")
    void find(const std::string& ID) const;

    // Returns how many different types of candy the datastructure contains (command "C")
    size_t count() const;

    // Empties the datastructure (command "E")
    void empty();
    
    // Copy constructor is forbidden (not important for this assignment)
    Datastructure(const Datastructure&) = delete;
    // Assignment operator is forbidden (not important for this assignment)
    Datastructure& operator=(const Datastructure&) = delete;
    
private:
  
    LinkedList* array_; // Array of linked lists
    int length_; // Size of the array
    int hash(string key) const; // Returns array location for given key

    Item *allocateObject();
    void freeObject(Item* deleted);
    Item* free; // First free object
    size_t count_;
};

#endif
