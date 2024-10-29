//
//  Sequence.cpp
//  WP_Project2
//
//  Created by Wolfe Pickett on 4/23/23.
//

#include "Sequence.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Sequence::Sequence()  // Create an empty sequence (i.e., one whose size() is 0).
: m_size(0), head(nullptr)
{
    head = new Node;
    head->next = head; //circular
    head->prev = head;
}

Sequence::~Sequence() // Destructor
{
    Node *p = head->next;
    while (p != head) {  // // delete all nodes until left with the head node
        Node* n = p->next;
        delete p;
        p = n;
    }
    delete head;
}

Sequence::Sequence(const Sequence& other)
{
    head = new Node;        //create a dummy node
    head->next = head;
    head->prev = head;
    m_size = 0;
    ItemType temp;

    for (int i = 0; i < other.size(); i++)
    {
        other.get(i, temp);
        insert(i, temp);
    }
}

Sequence& Sequence::operator=(const Sequence& other)
{
    if (this != &other) {
        Sequence temp(other);
        swap(temp);
    }
    return *this;
}


int Sequence::size() const
{
    return m_size;
}

bool Sequence::empty() const
{
    return (m_size == 0);

}

int Sequence::insert(int pos, const ItemType& value) //function for inserting a new node at a position in the list
{
    if (pos < 0 || pos > m_size)            //attempting to add beyond the size of the list
        return -1;

    if (pos == m_size)      //insert at the end of the list
    {
        Node* p;
        for (p = head->next; p->next != head; p = p->next)
        {}

        Node* n = new Node;
        n->data = value;
        n->prev = p;
        n->next = p->next;
        p->next = n;
        m_size++;
        return pos;
    }
    else            //for adding anywhere in the list except at the end
    {
        Node* p;
        int i = 0;
        for (p = head->next; p->next != head && i < pos; p = p->next)        //loop to reach the position where the new value needs to be added
        {
            i++;
        }
        Node* n = new Node;        //create a new node that needs to be added
        n->data = value;
        n->prev = p->prev;
        p->prev->next = n;
        n->next = p;
        p->prev = n;

        m_size++;            //increase the size since new element was added
        return pos;
    }
}


int Sequence::insert(const ItemType& value)        //function to add an element whereever the value <= the value the a position in the list
{

    if (m_size == 0)        //handle the case when the list is empty
    {
        head->next = new Node;
        head->next->data = value;
        head->next->next = head;
        head->next->prev = head;
        m_size++;
        return 0;
    }

    else        //case if the list is not empty
    {
        Node* p;        //create a temporary pointer to iterate through the linked list
        int i = 0;
        for (p = head->next; p->next != head && value > p->data; p = p->next)    //iterate till we reach the end or when value <= the value at that position
        {
            i++;
        }

        if (p->next == head && value > p->data)        //if its at the end and is greater than all the values in the list
        {
            Node* n = new Node;            //create a new node to be added
            n->data = value;
            n->next = p->next;            //add it at the end of the list
            p->next = n;
            n->prev = p;
            m_size++;
            return m_size - 1;
        }

        else                                    //any case other than the above case
        {
            Node* n = new Node;        //create a new node to be added
            n->data = value;
            n->next = p;                //add it before the current element
            n->prev = p->prev;
            p->prev->next = n;
            p->prev = n;
            m_size++;
            return i;
        }
    }
}


bool Sequence::erase(int pos)        //function to erase an existing node at the given position
{
    if (pos >= m_size)        //attempting to erase out of bounds
        return false;

    Node* p;        //dummy node
    int i = 0;
    for (p = head; i <= pos; p = p->next)    //iterate till we hit the position
    {
        i++;
    }
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;        //delete the node
    m_size--;
    return true;
}


int Sequence::remove(const ItemType& value)        //function to remove an all nodes that have value equal to the parameter passed
{
    int counter = 0;
    int i = 0;

    for (Node* p = head->next; i < m_size; p = p->next)    //iterates through the list to find the element
    {
        if (p->data == value)
        {
            Node* temp = p;            //create a temporary node
            p = p->prev;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;        //delete the temporary pointer that points to the node that has to be deleted
            m_size--;
            counter++;
            i--;    //i decreases since the size also decreases
        }
        i++;
    }
    return counter;    //return counter
}


bool Sequence::get(int pos, ItemType& value) const
{
    if (pos < 0 || pos >= m_size)    //
        return false;

    else if (head == nullptr)
        return false;

    else
    {
        Node* p;        //we create a dummy node
        int i = 0;
        for (p = head->next; i < pos; p = p->next)    //iterate till we hit the position
        {
            i++;
        }

        value = p->data;
        return true;
    }
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos >= m_size)
        return false;

    else
    {
        Node* p;        //we create a dummy node
        int i = 0;
        for (p = head; i <= pos; p = p->next)    //iterate till we hit the position
        {
            i++;
        }

        p->data = value;        //set the parameter to the value at the position
        return true;
    }
}


int Sequence::find(const ItemType& value) const
{
    int i = 0;
    int counter = -1;

    for (Node* p = head->next; p != head; p = p->next)        //loop to iterate through the list
    {
        if (p->data == value)        //if the value at that position is equal to the parameter passed
        {
            counter = i;    //set counter to the position at which it's equal
            break;
        }
        i++;
    }
    return counter;    //return the position at which it was found
}


void Sequence::swap(Sequence& other)
// Swap elements.  Since the only elements that matter are those up to
// m_size and other.m_size, only they have to be moved.
{
    Node* temp = other.head;
    other.head = head;
    head = temp;

    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
}


int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    if(seq1.size() < seq2.size())
        return -1;

    if (seq1.empty() || seq2.empty())
        return -1;

    ItemType counter1;
    ItemType counter2;
    for(int i = 0; i < seq1.size(); i++)
    {
        // if the size of seq1 - size of seq2 - the pos you are at in seq1 is less than 0 return -1
        if ((seq1.size() - seq2.size() - i) < 0)
            break;
        
        seq1.get(i,counter1);
        seq2.get(0,counter2);
        //if a value of seq 1 == value of seq2 then loop through seq to check if they match
        if(counter1 == counter2)
        {
            for(int k = 0; k < seq2.size(); k++)
            {
                seq1.get(i + k , counter1);
                seq2.get(k , counter2);
                if(counter1 != counter2)
                    break;
                else if (k == seq2.size() - 1)
                    return i;
            }
        }
    }
    return -1;
}

void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
    Sequence temp;
    ItemType val;
    if (seq1.empty() && !seq2.empty()) {
        for (int i = 0; i < seq2.size(); i++) {
            seq2.get((seq2.size()-1-i), val);
            temp.insert(i, val); // Insert at end
        }
    }
        
    else if (seq2.empty() && !seq1.empty()) {
        for (int i = 0; i < seq2.size(); i++) {
            seq1.get((seq1.size()-1-i), val);
            temp.insert(i, val); // Insert at end
        }
    }
    int pos = 0;
    for (int i = seq1.size() - 1; i >= 0; i--) {
        if (seq1.get(i, val)) {
            temp.insert(pos, val); // Insert in reverse order
            pos++;
        }
    }
    for (int i = seq2.size() - 1; i >= 0; i--) {
        if (seq2.get(i, val)) {
            temp.insert(pos, val); // Insert at end
            pos++;
        }
    }
    result = temp;
}




