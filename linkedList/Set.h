//
//  Set.hpp
//  Project2CS32
//
//  Created by Shilpa Rao on 4/19/21.
//

#ifndef Set_h
#define Set_h

#include <stdio.h>
#include <iostream>
#include <string>

class Set;

void unite(const Set& s1, const Set& s2, Set& result);

void difference(const Set& s1, const Set& s2, Set& result);

using ItemType = std::string;

class Set
{

    int count = 0;
    
    // declaring a new type
    // has nothing to do with size of set or list
    struct Node {
        
        ItemType var;
        Node* next;
        Node* prev;
        
    };
    
    Node* tail = nullptr;
    Node* head = nullptr;
    Node* tailErase = nullptr;
    
  public:
    
    Set();
    
    // Assignment operator
    Set operator=(const Set& other);
    
    // Copy constructor
    Set(const Set& other);
    
    // Destructor
    ~Set();
    
    bool empty() const;
    
    int size() const;
    
    bool insert(const ItemType& value); // how to implement?
                                // Node --> holds value that we're inserting
                                // where do pointers point?
                        // we need to DYNAMICALLY ALLOCATE memory for this new node
                        // if count = 0
                        // for every linked list, only one private member: head pointing to start
                        // how to know if empty? if head == null, then list = empty
                        // head = first node (WHERE DO I DECLARE)?
                                // in constructor of set
                                // when we start, there's nothing in linked list. at beginning, head = nullptr.
                                    // when we insert first element, so when count = 1, head points to insertion
                                        // head = newNode;
                                        // newNode->prev = nullptr;
    
                        // when next = null, we're at end
                        // Node * node = new Node;
                                // if (node->next == nullptr)
    
                    // how to know if at first element?
                            // use counter
                            // if head != nullptr
            
                    // make sure that when we delete everything from linked list, if we delete first node, we also need to modify head pointer.
                    // how can I tell?
                            // next = nullptr, prev = nullptr
                            // to delete: locate which node we need to delete. when we know that, then compare pointers. if head -> node to delete, then delete head after deletion.
    
                // HOW TO CALL DESTRUCTOR ON EVERYTHING?
                                
    bool erase(const ItemType& value);
    
    bool contains(const ItemType& value) const;
    
    bool get(int pos, ItemType& value) const;
    
    void swap(Set& other);

};

#endif /* Set_h */

