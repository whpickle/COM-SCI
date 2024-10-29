//
//  Sequence.h
//  WP_Project2
//
//  Created by Wolfe Pickett on 4/23/23.
//

#ifndef Sequence_h
#define Sequence_h

#include <iostream>
#include <string>

using ItemType = std::string;

class Sequence
{
  public:
    Sequence();
    ~Sequence();    //destructor
    Sequence(const Sequence& other);  //copy constructor
    Sequence &operator=(const Sequence& other);   //assignment operator
    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    
  private:
    
    struct Node
    {
        ItemType data;
        Node* next;
        Node* prev;
    
    };
    
    int m_size;
    Node *head;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result);


#endif /* Sequence_h */
