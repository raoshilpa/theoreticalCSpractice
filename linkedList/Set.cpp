//
//  Set.cpp
//  Project2CS32
//
//  Created by Shilpa Rao on 4/19/21.
//

#include "Set.h"
#include <algorithm>
using namespace std;

Set::Set() {

}

// Assignment operator
Set Set::operator=(const Set& other) {
    
    if (this != &other)
    {
        Set temp(other);
        swap(temp);
    }
    return *this;
    
}

// Copy constructor
Set::Set(const Set& other) {
    
    if (other.head != nullptr)
    {
        
        head = new Node;
        head->var = other.head->var;
        head->next = nullptr;

        Node* this_curr = head;
        Node* other_curr = other.head;

        while(other_curr->next != nullptr)
        {
            
            Node* new_node = new Node;
            new_node->var = other_curr->next->var;
            new_node->next = nullptr;
            this_curr->next = new_node;

            other_curr = other_curr->next;
            this_curr = this_curr->next;
            
        }
        
    } else {
        
        head = nullptr;
        
    }
    
}

// Double check this logic
Set::~Set(){
    
    Node* curr = head;
    while(curr != nullptr)
    {
        Node* to_delete = curr;
        curr = curr->next;
        delete to_delete;
    }
    
}

bool Set::empty() const {
    
    if (count == 0) {
        return true;
    } else {
        return false;
    }
    
    // reurn (count == 0); ?
    
}

int Set::size() const {
    return count;
}

bool Set::insert(const ItemType& value) {
    
    bool b = false;
    
    if (!contains(value)) {
        
        Node *newThing;
        newThing = new Node;
        
        // if we're not at the start of the list
        if (head != nullptr) {
            
            // tail's next has to point to this one
            tail->next = newThing;
            newThing->var = value;
            newThing->prev = tail;
            newThing->next = nullptr;
            tail = newThing;
            b = true;
            count++;
            
        } else {
            
            head = newThing;
            tail = newThing;
//            tail->prev = nullptr; //tail->next?
            newThing->prev = nullptr;
            newThing->next = nullptr;
            newThing->var=value;
            b = true;
            count++;
            
        }
        
    } else {
        b = false;
    }
    
    return b;

}


bool Set::erase(const ItemType& value) {
    
    bool b = false;

    for( Node *temp = head; temp != nullptr; temp = temp->next) {
        if (temp->next == nullptr) {
            tailErase = temp->prev;
        }
    }
    
    for( Node *temp = head; temp != nullptr; temp = temp->next) {
        
        // If we've located the value we wish to remove....
        if (temp->var == value) {
            
            // The following set of if statements contains the logic necessary to accurately re-position the pointers
            // If we're erasing the only element in the list:
            if (temp->next == nullptr && temp->prev == nullptr) {
                
                head = nullptr;
                tailErase = nullptr;
                count--;
                b = true;
                delete temp;
                return b;
                
            }
            // else, if we're erasing the last element in the list:
            else if (temp->next == nullptr && temp->prev != nullptr) {
                
                tailErase->next = nullptr;
                count--;
                b = true;
                delete temp;
                return b;
                
            }
            // else, if we're erasing the node somewhere in the hinterlands of the list, where we don't know where the tail is
            else if (tailErase->next != temp && temp != tailErase && temp->prev != tailErase) {
                 
                // not sure about this logic, might need to write a temporary variable or two
                temp->next->prev = temp->prev;
                
                // If we're deleting the start of the list but the tail is somewhere else
                if (temp->prev == nullptr) {
                    head = temp->next;
                // If we're not deleting the start of the list, then the previous element WILL have an accessible next.
                } else {
                    temp->prev->next = temp->next;
                }
                count--;
                b = true;
                delete temp;
                return b;
                
            }
            // else, if the node we're erasing is the tail but not first element
            else if (temp == tailErase && temp->prev != nullptr) { // possibly, temp->prev != nullptr
                tailErase = temp->prev;
                tailErase->next = temp->next;
                temp->next->prev = tailErase;
                count--;
                b = true;
                delete temp;
                return b;
            
            // else, if the node we're erasing is the tail but it is the first element
            } else if (temp == tailErase && temp->prev == nullptr) {
                tailErase = temp->next;
                tailErase->prev = nullptr;
                head = tailErase;
                count--;
                b = true;
                delete temp;
                return b;
            }
           
        } else {
            
            
        }
        
    }
    
    return b;
    
}

bool Set::contains(const ItemType& value) const {
    
    bool c = false;
                                            // temp->next means move it to the next element
    for( Node *temp = head; temp != nullptr; temp = temp->next) {
        if (temp->var == value) { 
            c = true;
            return c;
        }
    }
    
    return c;
    
}

bool Set::get(int j, ItemType& value) const {
    
    bool b = false;

    if (j < 0 || j >= size()) {
        return b;
    }
    
    // increment through list
    for( Node *temp = head; temp != nullptr; temp = temp->next)
    {
        int c = 0;
        for( Node *temp2 = head; temp2 != nullptr; temp2 = temp2->next)
        {
            // Check each place of the array against each following place. If our current place is less than anything in front of it, increment c.
            if (temp->var < temp2->var) {
                c++;
            }
        }
        // If the count of items less than that in the ith place is equal to the parameter j, set value.
        if (c == j) {
            value = temp->var;
            b = true;
            return b;
        }
    }

    return b;
    
}

// Exchange contents of set with another one.
void Set::swap(Set& other) {
    
    Node * tempHead = head;
    head = other.head;
    other.head = tempHead;
    
    Node * tempTail = tail;
    tail = other.tail;
    other.tail = tempTail;
    
    Node * tempTailErase = tailErase;
    tailErase = other.tailErase;
    other.tailErase = tempTailErase;
    
    int tempCount = count;
    count = other.count;
    other.count = tempCount;
    
}

void unite(const Set& s1, const Set& s2, Set& result) {
    
    // If result is empty
    if (result.size() == 0) {
        // copy elements over to s1
        int sizeS1 = s1.size();
        for ( int i = 0; i < sizeS1; i++) {
            ItemType value;
            s1.get(i, value); // This edits var to find desired value in get!
            result.insert(value);
        }
        
        // for elements of s2, if !contains(val), copy over
        int sizeS2 = s2.size();
        for ( int j = 0; j < sizeS2; j++) {
            
            ItemType value2;
            s1.get(j, value2); // This edits var to find desired value in get!
            result.insert(value2);

        }
        
    } else if (result.size() > 0) {

        // Empty the result set first
        int sizeRes = result.size();
        for ( int k = 0; k < sizeRes; k++) {
            ItemType value2;
            result.get(k, value2);
            result.erase(value2);
        }
        
        // Then, proceed with the regular approach
        int sizeS1 = s1.size();
        for ( int i = 0; i < sizeS1; i++) {
            ItemType value;
            s1.get(i, value); // This edits var to find desired value in get!
            result.insert(value);
        }
        
        // for elements of s2, if !contains(val), copy over
        int sizeS2 = s2.size();
        for ( int j = 0; j < sizeS2; j++) {
            
            ItemType value2;
            s1.get(j, value2); // This edits var to find desired value in get!
            result.insert(value2); // DOUBLE CHECK

        }
        
    } else {
        // Do nothing
    }
    
}

// Result consists of the values that are not shared between sets
void difference(const Set& s1, const Set& s2, Set& result) {
    
    // If result is not empty
    if (result.size() == 0) {
        
        // First, we iterate through s1. If s2 doesn't contain the value, we add it.
        int sizeS1 = s1.size();
        for ( int i = 0; i < sizeS1; i++) {
            ItemType value;
            s1.get(i, value); // This edits var to find desired value in get!
            bool s2Contains = s2.contains(value);
            
            if (!s2Contains) {
                result.insert(value);
            }
            
        }
        
        // Next, we iterate through s2. If s1 doesn't contain the value, we add it.
        int sizeS2 = s2.size();
        for ( int j = 0; j < sizeS2; j++) {
            ItemType value;
            s2.get(j, value); // This edits var to find desired value in get!
            bool s1Contains = s1.contains(value);
            
            if (!s1Contains) {
                result.insert(value);
            }
            
        }
        
    } else if (result.size() > 0) {

        // Empty the result set first
        int sizeRes = result.size();
        for ( int k = 0; k < sizeRes; k++) {
            ItemType value2;
            result.get(k, value2);
            result.erase(value2);
        }
        
        // First, we iterate through s1. If s2 doesn't contain the value, we add it.
        int sizeS1 = s1.size();
        for ( int i = 0; i < sizeS1; i++) {
            ItemType value;
            s1.get(i, value); // This edits var to find desired value in get!
            bool s2Contains = s2.contains(value);
            
            if (!s2Contains) {
                result.insert(value);
            }
            
        }
        
        // Next, we iterate through s2. If s1 doesn't contain the value, we add it.
        int sizeS2 = s2.size();
        for ( int j = 0; j < sizeS2; j++) {
            ItemType value;
            s2.get(j, value); // This edits var to find desired value in get!
            bool s1Contains = s1.contains(value);
            
            if (!s1Contains) {
                result.insert(value);
            }
            
        }
        
    }
    
}
