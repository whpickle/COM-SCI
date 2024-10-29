//
//  Map.cpp
//  Project2
//
//  Created by Wolfe Pickett on 1/30/24.
//

#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

Map::Map()
: head(nullptr), tail(nullptr), m_size(0)
{

}

Map::~Map() 
{
    Node* p = head;
    while (p != nullptr) {
        Node* move = p;
        p = p->next;
        delete move;
    }
}

Map::Map(const Map& other)
: head(nullptr), tail(nullptr), m_size(0)
{
    KeyType tempK;
    ValueType tempV;

    for (int i = 0; i < other.size(); i++)
    {
        other.get(i, tempK, tempV);
        insert(tempK, tempV);
    }
}

Map& Map::operator=(const Map& other)
{
    if (this != &other) {
        Map temp(other);
        swap(temp);
    }
    return *this;
}


bool Map::empty() const
{
    return m_size == 0;
}

int Map::size() const {
    return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value) {
    // Check for existing key
    Node* p = this->head;
    while (p != nullptr) {
        if (p->m_key == key) {
            return false;
        }
        p = p->next;
    }

    // Create new node and add it to the head
    Node* n = new Node;
    n->m_key = key;
    n->m_value = value;
    n->next = head;
    n->prev = nullptr;
    
    if (head != nullptr) {
        head->prev = n;
    }
    head = n;
    if (tail == nullptr) {
        tail = n;
    }
    m_size++;
    return true;
}


bool Map::update(const KeyType& key, const ValueType& value) {

    Node* p = this->head;
    
    // Traverse the list to find the node with the matching key
    while (p != nullptr) {
        if (p->m_key == key) {
            // If Key found, update the value
            p->m_value = value;
            return true;
        }
        p = p->next; // Move to the next node
    }

    // Return false if Key is not found
    return false;
}


bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    // If the list contains key
    if (this->update(key, value))
        return true;
    
    // Insert, otherwise
    this->insert(key, value);
    return true;
    
}


bool Map::erase(const KeyType& key) {

    Node* p = this->head;

    // Traverse the list to find the node with the matching key
    while (p != nullptr) {
        if (p->m_key == key) {

            // If it's the only node in the list
            if (p == this->head && p == this->tail) {
                this->head = nullptr;
                this->tail = nullptr;
            }
            // If it's the head node
            else if (p == this->head) {
                this->head = p->next;
                this->head->prev = nullptr;
            }
            // If it's the tail node
            else if (p == this->tail) {
                this->tail = p->prev;
                this->tail->next = nullptr;
            }
            // If it's a middle node
            else {
                p->prev->next = p->next;
                p->next->prev = p->prev;
            }

            delete p;
            this->m_size--;  // Decrement the size of the map
            return true;
        }
        p = p->next; // Move to the next node
    }

    // Key not found, return false
    return false;
}

bool Map::contains(const KeyType& key) const {
    Node* p = head;
    while (p != nullptr) {
        if (p->m_key == key) {
            return true;
        }
        p = p->next;
    }
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const {
    
    Node* p = this->head;

    // Traverse the list to find the node with the matching key
    while (p != nullptr) {
        if (p->m_key == key) {
            value = p->m_value; // Set the value
            return true; // Key found
        }
        p = p->next; // Move to the next node
    }

    return false; // Key not found
}


bool Map::get(int i, KeyType& key, ValueType& value) const {
    if (i < 0 || i >= m_size)
        return false; // Index out of bounds

    Node* p = head;
    for (int k = 0; k < i; k++)
        p = p->next;

    key = p->m_key;
    value = p->m_value;
    return true;
}


void Map::swap(Map& other) {
    
    // Swap heads
    Node* tempHead = other.head;
    other.head = head;
    head = tempHead;

    // Swap tails
    Node* tempTail = other.tail;
    other.tail = tail;
    tail = tempTail;

    // Swap sizes
    int tempSize = other.m_size;
    other.m_size = m_size;
    m_size = tempSize;
}


bool merge(const Map& m1, const Map& m2, Map& result) {
    
    Map tempMap;
    KeyType tempKey1, tempKey2;
    ValueType tempValue1, tempValue2;
    bool conflict = true; // Assume conflict initially

    // Search through the keys in m1
    for (int i = 0; i < m1.size(); i++) {
        // For each key, get its key and value
        m1.get(i, tempKey1, tempValue1);

        // Check if m2 has the same key
        if (m2.contains(tempKey1)) {
            // If it does, get m2's value for that key
            m2.get(tempKey1, tempValue2);

            // If they are the same...
            if (tempValue2 == tempValue1) {
                // Insert it into the temporary map
                tempMap.insert(tempKey1, tempValue1);
                conflict = false; // No conflict for this key
            }
        } else {
            // If m2 doesn't have the key that was in m1, insert it into the temporary map
            tempMap.insert(tempKey1, tempValue1);
            conflict = false; // No conflict for this key
        }
    }

    // Now go through m2, and get all the keys that are in m2 but not in m1
    for (int i = 0; i < m2.size(); i++) {
        m2.get(i, tempKey2, tempValue2);
        if (!m1.contains(tempKey2)) {
            tempMap.insert(tempKey2, tempValue2);
        }
    }

    // Update result with the contents of the temporary map
    result = tempMap;
    return !conflict;
}


void reassign(const Map& m, Map& result) {
    // First, clear the result map
    while (!result.empty()) {
        KeyType k;
        ValueType v;
        result.get(0, k, v);
        result.erase(k);
    }

    // Handle the special case when m has only one pair
    if (m.size() == 1) {
        KeyType k;
        ValueType v;
        m.get(0, k, v);
        result.insert(k, v);
        return;
    }

    // For more than one pair, reassign values
    KeyType firstKey, currentKey, nextKey;
    ValueType firstValue, nextValue;

    // Store the first key-value pair
    m.get(0, firstKey, firstValue);
    currentKey = firstKey;

    // Reassign values to the next key in the map
    for (int i = 1; i < m.size(); ++i) {
        m.get(i, nextKey, nextValue);
        result.insert(nextKey, firstValue); // Assign the first value to the next key
        firstValue = nextValue; // Update the firstValue for the next iteration
    }

    // Assign the last value to the first key
    result.insert(firstKey, firstValue);
}


