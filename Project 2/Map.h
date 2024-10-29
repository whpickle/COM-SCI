//
//  Map.h
//  Project2
//
//  Created by Wolfe Pickett on 1/30/24.
//

#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#include <string>

using KeyType = std::string;
using ValueType = double;

class Map
{
  public:
    Map();
    ~Map();    //destructor
    Map(const Map& other);  //copy constructor
    Map &operator=(const Map& other);   //assignment operator
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
  
  private:
    struct Node
    {
        KeyType m_key;
        ValueType m_value;
        Node* next;
        Node* prev;
    };
    
    Node *head;
    Node *tail;
    int m_size;
};

bool merge(const Map& m1, const Map& m2, Map& result);
void reassign(const Map& m, Map& result);


#endif /* MAP_INCLUDED */
