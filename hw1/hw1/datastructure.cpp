#include "datastructure.hh"


Datastructure::Datastructure()
{
    sortedA_ = false;
    sorted_ = false;
}

Datastructure::~Datastructure()
{
}

void Datastructure::setValues(string name, unsigned int brokenNysse, unsigned int sufferingPeople)
{
    name_ = name;
    nysse_ = brokenNysse;
    people_ = sufferingPeople;
}

// Placeholders for functions


// Adds new player
void Datastructure::add(string name, unsigned int brokenNysse,
            unsigned int sufferingPeople)
{
    Datastructure data;
    data.setValues(name, brokenNysse, sufferingPeople);
    player_.push_back(data);
    sorted_ = false;
    sortedA_ = false;
}

string Datastructure::returnName()
{
    return name_;
}

unsigned int Datastructure::returnNysse()
{
    return nysse_;
}

unsigned int Datastructure::returnPeople()
{
    return people_;
}

bool Datastructure::returnSorted()
{
    return sorted_;
}

bool Datastructure::returnSortedA()
{
    return sortedA_;
}


// Finds player with key stored in term
void Datastructure::findPerson(string term)
{
    if (player_.size() != 0) {
        vector<Datastructure> leaderboard;
        Datastructure data;

        // If the players are in wrong order, sort them
        if (returnSorted() == false) {
            player_ = merge_sort(player_);
            sorted_ = true;
            sortedA_ = false;
        }

        leaderboard = player_;

        vector<Datastructure>::iterator iter;
        iter = leaderboard.begin();
        int i = 0;

        while(iter != leaderboard.end()) {
            data = *iter;
            if (data.returnName() == term) {
                cout << i+1 << ". " << data.returnName() << ": " << data.returnNysse() <<
                    " buses, " << data.returnPeople() << " passengers" << endl;
                return;
            }
            iter++;
            i++;
        }
    }
    cout << "Player " << term << " was not found." << endl;
}

// Print leaderboard. Sorts only if necessary
void Datastructure::printLeaderBoard()
{
    if (player_.size() != 0) {
        vector<Datastructure> leaderboard;
        Datastructure data;

        // If the players are in wrong order, sort them
        if (returnSorted() == false) {
            player_ = merge_sort(player_);
            sorted_ = true;
            sortedA_ = false;
        }

        leaderboard = player_;

        vector<Datastructure>::iterator iter;
        iter = leaderboard.begin();
        int i = 0;

        while(iter != leaderboard.end()) {
            data = *iter;
            cout << i+1 << ". " << data.returnName() << ": " << data.returnNysse() <<
                    " buses, " << data.returnPeople() << " passengers" << endl;

            iter++;
            i++;
        }
    }
}

// Prints players alphabetically
void Datastructure::printAlphabetically()
{
    if (player_.size() != 0) {
        vector<Datastructure> alphabetical;
        Datastructure data;

        // If the players are in wrong order, sort them
        if (returnSortedA() == false) {
            player_ = Amerge_sort(player_);
            sorted_ = false;
            sortedA_ = true;
        }

        alphabetical = player_;

        vector<Datastructure>::iterator iter;
        iter = alphabetical.begin();
        int i = 0;

        while(iter != alphabetical.end()) {
            data = *iter;
            cout << data.returnName() << ": " << data.returnNysse() <<
                    " buses, " << data.returnPeople() << " passengers" << endl;

            iter++;
            i++;
        }
    }
}

// Prints worst player stats
void Datastructure::worstPlayer()
{
    if (player_.size() != 0) {
        Datastructure data;

        // If the players are in wrong order, sort them
        if (returnSorted() == false) {
            player_ = merge_sort(player_);
            sorted_ = true;
            sortedA_ = false;
        }

        data = player_.back();
        cout << player_.size() << ". " << data.returnName() << ": " <<
                data.returnNysse() << " buses, " << data.returnPeople() <<
                " passengers" << endl;
    }
}

// Prints best player stats
void Datastructure::bestPlayer()
{
    if (player_.size() != 0) {
        Datastructure data;

        // If the players are in wrong order, sort them
        if (returnSorted() == false) {
            player_ = merge_sort(player_);
            sorted_ = true;
            sortedA_ = false;
        }

        data = player_.front();
        cout << "1. " << data.returnName() << ": " << data.returnNysse() <<
                " buses, " << data.returnPeople() << " passengers" << endl;
    }
}

// Empties the datastructure
void Datastructure::empty()
{
    player_.clear();
    sortedA_ = false;
    sorted_ = false;
}

// Merge sort by player's points
vector<Datastructure> Datastructure::merge_sort(vector<Datastructure> &vec)
{
    // If the vector only has one item, there is nothing to sort
    if(vec.size() == 1) {
        return vec;
    }

    // Middle point of the vector
    vector<Datastructure>::iterator middle = vec.begin() + (vec.size() / 2);

    // Separate the vector in half
    vector<Datastructure> left(vec.begin(), middle);
    vector<Datastructure> right(middle, vec.end());

    // Recursively call the merge sort method
    left = merge_sort(left);
    right = merge_sort(right);

    // Merge the left and right part together in merge-method
    return merge(left, right);
}

vector<Datastructure> Datastructure::merge(vector<Datastructure> &left, vector<Datastructure> &right)
{
    vector<Datastructure> result; // Merged vector
    Datastructure dataLeft; // Item in the left vector
    Datastructure dataRight; // Item in the right vector
    unsigned left_i = 0, right_i = 0; // Indexes set to 0

    // While there are some items in both vectors left to compare
    while(left_i < left.size() && right_i < right.size()) {
        dataLeft = left[left_i];
        dataRight = right[right_i];

        // If the number of Nysses in the left data is larger, it goes first
        if (dataLeft.returnNysse() > dataRight.returnNysse()) {
            result.push_back(dataLeft);
            left_i++;
        }
        else if (dataLeft.returnNysse() == dataRight.returnNysse()) {
            // If the number of Nysses is the same,
            // the one with more people goes first
            if (dataLeft.returnPeople() > dataRight.returnPeople()) {
                result.push_back(dataLeft);
                left_i++;
            }
            else {
                result.push_back(dataRight);
                right_i++;
            }
        }
        else {
            result.push_back(dataRight);
            right_i++;
        }
    }

    // When there's no more items in BOTH vectors,
    // the remaining items are added on the end of the result vector

    while(left_i < left.size()) {
        result.push_back(left[left_i]);
        left_i++;
    }

    while(right_i < right.size()) {
        result.push_back(right[right_i]);
        right_i++;
    }

    // The two vectors are merged
    return result;
}

// Merge sort alphabetically, otherwise same as the previous merge sort
vector<Datastructure> Datastructure::Amerge_sort(vector<Datastructure> &vec)
{
    if(vec.size() == 1) {
        return vec;
    }

    vector<Datastructure>::iterator middle = vec.begin() + (vec.size() / 2);

    vector<Datastructure> left(vec.begin(), middle);
    vector<Datastructure> right(middle, vec.end());

    left = Amerge_sort(left);
    right = Amerge_sort(right);

    return Amerge(left, right);
}

vector<Datastructure> Datastructure::Amerge(vector<Datastructure> &left, vector<Datastructure> &right)
{
    vector<Datastructure> result;
    Datastructure dataLeft;
    Datastructure dataRight;
    unsigned left_i = 0, right_i = 0;
    string leftName, rightName;

    while(left_i < left.size() && right_i < right.size()) {
        dataLeft = left[left_i];
        dataRight = right[right_i];
        leftName = dataLeft.returnName();
        rightName = dataRight.returnName();
        unsigned int i = 0;

        // Examine names char by char
        while(i < leftName.size() && i < rightName.size()) {
            if (leftName[i] < rightName[i]) {
                result.push_back(dataLeft);
                left_i++;
                break;
            }
            else if (leftName[i] > rightName[i]) {
                result.push_back(dataRight);
                right_i++;
                break;
            }
            // If that was the last character of the name, add it next
            if (i == leftName.size()-1) {
                result.push_back(dataLeft);
                left_i++;
                break;
            }
            else if (i == rightName.size()-1) {
                result.push_back(dataRight);
                right_i++;
                break;
            }
            // If the characters were the same, move to the next chars
            i++;
        }

    }

    while(left_i < left.size()) {
        result.push_back(left[left_i]);
        left_i++;
    }

    while(right_i < right.size()) {
        result.push_back(right[right_i]);
        right_i++;
    }

    return result;
}


