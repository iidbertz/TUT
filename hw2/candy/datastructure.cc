#include "datastructure.hh"

// Empty implementations for public interface, modify and add your own code here


Datastructure::Datastructure()
{
    length_ = 59999;
    array_ = new LinkedList[length_];
    count_ = 0;
    free = NULL;
}

Datastructure::~Datastructure()
{
    delete [] array_;
}

// Adds candy to storage.
void Datastructure::add(const string &ID, const string &location,
                        unsigned int amount, const string &name)
{
    // Find the right array index for the data
    int index{hash(ID)};
    // See if there's already some of that candy in the storage.
    // If yes, add the new amount to the existing candy
    // If not, add new item to the hash table
    Item* oldItem{array_[index].getItem(ID)};
    if (oldItem != NULL) {
        int qty{stoi(oldItem->data_.at(1))};
        qty += amount;
        oldItem->data_.at(1) = to_string(qty);
    } else {
        // Save the new data to fized-size vector
        vector<string> candy(4);
        candy.at(0) = ID;
        candy.at(1) = to_string(amount);
        candy.at(2) = location;
        candy.at(3) = name;

        Item* newItem = allocateObject(); // Allocate memory for new data
        newItem->data_ = candy;
        newItem->next_ = NULL;
        newItem->prev_ = NULL;
        array_[index].add(newItem);
        count_ += 1;
    }
}

// Substracts candy from the storage
void Datastructure::substract(const string &ID, unsigned int amount)
{
    int index{hash(ID)}; // Find the linked list where the candy should be
    Item* curr{array_[index].getItem(ID)};
    // If the wanted candy is found, see if there's enough of it
    if (curr != NULL) {
        unsigned int qty{stoi(curr->data_.at(1))};
        // If there is enough candy, substract wanted amount
        // Print remaining amount and shelf
        if (qty >= amount) {
            qty -= amount;
            curr->data_.at(1) = to_string(qty);
            cout << "Amount: " << curr->data_.at(1) << " Shelf: " <<
                    curr->data_.at(2) << endl;
            // If there's no more candy, remove it from the hash table
            if (qty == 0) {
                array_[index].remove(curr);
                count_ -= 1;
                freeObject(curr);
            }
        } else { // Not enough candy, print error message, amount and shelf
            cout << NOT_ENOUGH_CANDY << endl;
            cout << "Amount: " << curr->data_.at(1) << " Shelf: " <<
                    curr->data_.at(2) << endl;
        }
    } else { // There's none of the wanted candy, print error message
        cout << NOT_AVAILABLE << endl;
    }
}

// Finds the wanted candy
void Datastructure::find(const string &ID) const
{
   // Find the candy from the storage
   int index{hash(ID)};
   Item* curr{array_[index].getItem(ID)};
   // If the candy is found, print name, amount and shelf
   if (curr != NULL) {
       cout << curr->data_.at(3) << " " << curr->data_.at(1) << " "
            << curr->data_.at(2) << endl;
   } else { // If candy is not found, print error message
       cout << NOT_AVAILABLE << endl;
   }
}

// Returns the amount of differend candies in the storage
size_t Datastructure::count() const
{
    return count_;
}

// Empties the storage
void Datastructure::empty()
{
    Item* curr; // Pointer to the candy to be deleted
    // Go trough every index in array
    for (int i = 0; i < length_; i++) {
        // Remove every candy in the index
        curr = array_[i].getHead();
        while (curr != NULL) {
            array_[i].remove(curr);
            freeObject(curr);
            curr = array_[i].getHead();
        }
    }
    count_ = 0; // Number of different candies to 0
}

// Returns an array index for given key
int Datastructure::hash(string key) const
{
    int value = 0;
    // Go trough every char in key and add to value
    for ( unsigned int i = 0; i < key.length(); i++ )
        value += key[i];
    return value % length_; // Return the remainder of value/length of array
}

// Allocate new object only if there aren't any free
Item *Datastructure::allocateObject()
{
    if (free == NULL) {
        Item* candy = new Item;
        return candy;
    }
    Item* candy = free;
    free = candy->next_;
    return candy;
}

// Add object to the list of free
void Datastructure::freeObject(Item *deleted)
{
    deleted->next_ = free;
    free = deleted;
}

LinkedList::LinkedList()
{
    head_ = NULL;}

// Add new item to the beginning of the list
void LinkedList::add(Item *newItem)
{
    newItem->next_ = head_;
    if (head_ != NULL) {
        head_->prev_ = newItem;
    }
    head_ = newItem;
}

// Remove an item from the list
void LinkedList::remove(Item* candy)
{
    // If there's a previous item, link it to the next
    if (candy->prev_ != NULL) {
        candy->prev_->next_ = candy->next_;
    } else { // If not, next is the new head
        head_ = candy->next_;
    }
    // If there's a next item, link it to the previous
    if (candy->next_ != NULL) {
        candy->next_->prev_ = candy->prev_;
    }
}

// Return pointer to the wanted item
Item *LinkedList::getItem(string key) const
{
    // Go through the list until item is found or there's no more items
    Item* curr = head_;
    while (curr != NULL && curr->data_.front() != key) {
        curr = curr->next_;
    }
    return curr; // Return the wanted item or NULL
}

// Return the first item of the list (the head)
Item *LinkedList::getHead()
{
    return head_;
}

LinkedList::~LinkedList()
{

}
