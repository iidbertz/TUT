#ifndef DATASTRUCTURE_HH
#define DATASTRUCTURE_HH

#include <string>
#include <vector>
#include <map>
#include <iostream>



using namespace std;

class Datastructure
{
public:
  Datastructure();
  ~Datastructure();

  //
  void setValues(string name, unsigned int brokenNysse,
                 unsigned int sufferingPeople);

  // Add value to the datastructure
  void add(string name, unsigned int brokenNysse,
	   unsigned int sufferingPeople);

  // Returns players' information
  string returnName();
  unsigned int returnNysse();
  unsigned int returnPeople();

  // Returns if the vector is in right order or not
  bool returnSorted();
  bool returnSortedA();

  // Prints leaderboard in descending order
  void printLeaderBoard();
  
  // Prints player data in alphabetical order.
  void printAlphabetically();

  // Print person with lowest score
  void worstPlayer();
  
  // Print person with highest score
  void bestPlayer();

  void findPerson(string searchTerm);
  
  // Empty the datastructure
  void empty();

  // Merge sort for leaderboard
  vector<Datastructure> merge_sort(vector<Datastructure>& vec);
  vector<Datastructure> merge(vector<Datastructure>& left, vector<Datastructure>& right);

  // Merge sort for alphabetical
  vector<Datastructure> Amerge_sort(vector<Datastructure>& vec);
  vector<Datastructure> Amerge(vector<Datastructure>& left, vector<Datastructure>& right);

  // Copy constructor is forbidden
  //Datastructre(const Datastructure&) = delete;
  // Assignment operator is forbidden
  //Datastructure& operator=(const Datastructure&) = delete;
  
private:
    string name_;
    unsigned int nysse_;
    unsigned int people_;
    vector<Datastructure> player_;
    bool sorted_;
    bool sortedA_;

};

#endif
