//
//  main.cpp
//  WP_Project2
//
//  Created by Wolfe Pickett on 4/23/23.
//

#include "Sequence.h"
#include <iostream>
#include <cassert>
#include <cstdlib>
using namespace std;


void test()
{
    
    Sequence a1;
    assert(a1.insert(0,1)==0); //testing insert with size 0
    assert(a1.insert(0,0)==0); //testing insert at 0
    assert(a1.insert(2,3)==2); //testing insert at 2
    assert(a1.insert(2,2)==2); //testing insert
    assert(a1.insert(4,4)==4); //testing insert
    assert(a1.size()==5); //testing size
    
    unsigned long test;
    
    assert(a1.get(0, test)==true); //testing get
    assert(test==0); //testing value in list
    assert(a1.get(5, test)==false); //testing get
    assert(a1.get(4, test)==true); //testing get
    assert(test==4); //testing value in list
    
    assert(a1.get(-1, test)==false); //testing get
    assert(a1.insert(6, 9)==-1); //testing insert at invalid location
    assert(a1.insert(0)==0); //testing insert at right position
    assert(a1.insert(5)==6); //testing insert
    assert(a1.insert(100)==7); //testing insert
    assert(a1.insert(1)==2); //testing insert
    assert(a1.erase(0)==true); //testing erase
    assert(a1.erase(0)==true); //testing erase
    assert(a1.erase(6)==true); //testing erase
    assert(a1.erase(6)==false); //testing erase
    assert(a1.remove(1)==2); //testing remove
    assert(a1.find(2)==0); //testing find
    
    Sequence s; // default constructor creates an empty Sequence.
    assert(s.empty()); // testing empty()
    assert(s.size() == 0); // testing size()
    assert(s.remove(12) == 0); // nothing to remove.

    assert(s.insert(0, 10) == 0);

    assert(!s.empty()); // s is non-empty now.
    assert(s.size() == 1); // s contains one item.
    assert(s.insert(1, 12) == 1);
    assert(s.size() == 2); // each time an item is inserted, size increases by one.
    assert(s.insert(2, 14) == 2);
    assert(s.size() == 3);
    assert(s.insert(4, 20) == -1); // can't skip values while inserting
    assert(s.size() == 3); // unsuccessful insertion operation doesn't affect size

    // accessing data in a non-empty Sequence

    // testing get() for each position in the Sequence.
    ItemType x1 = 999;
    assert(s.get(0, x1) && x1 == 10);
    assert(s.get(1, x1) && x1 == 12);
    assert(s.get(2, x1) && x1 == 14);
    assert(!s.get(3, x1) && x1 == 14); // accessing outside bounds returns false and leaves x1 unaffected.

    // testing find() for each ItemType value in the list.
    assert(s.find(12) == 1);
    assert(s.find(14) == 2);
    assert(s.find(10) == 0);
//    assert(s.find(98) == -1); // cannot find what is not already there in the Sequence.

    Sequence p;                 //check insert, set up for other checks
    p.insert(0, 1);
    p.insert(1, 2);
    p.insert(2, 4);
    p.insert(3, 5);
    p.insert(4, 6);
    p.insert(0, 7);
    p.insert(3, 8);

    Sequence q;
    q.insert(0, 8);
    q.insert(1, 4);
    q.insert(2, 5);

    Sequence r;
    r.insert(0, 7);
    r.insert(1, 1);
    r.insert(2, 2);
    r.insert(3, 4);
    r.insert(4, 5);

    Sequence m;
    m.insert(0, 7);
    m.insert(1, 1);
    m.insert(2, 2);
    m.insert(3, 8);
    m.insert(4, 4);


    assert(subsequence(p, q) == 3);             //testing subsequence
    assert(subsequence(p, r) == -1);
    assert(subsequence(p, m) == 0);
    
    Sequence a;
    assert(a.empty() == true); // Testing .empty()
// Testing insert(pos,value)
    a.insert(0, 0);
    a.insert(1, 1);
    a.insert(2, 2);
// Testing empty() and size()
    assert(a.empty() == false);
    assert(a.size() == 3);
    ItemType x = 100;
// Testing get()
    assert(!a.get(3, x)  &&  x == 100);  // x is unchanged
    assert(a.get(2, x)  &&  x == 2); // x has been changed
    assert(a.get(1, x)  &&  x == 1);

// Testing insert(value)
    assert(a.insert(4) == 3); // insert at end
    assert(a.size() == 4); // size is incremented correctly
    assert(a.get(3, x)  &&  x == 4); // get works correctly

// Testing erase()
    assert(a.erase(3) == true); // removing from end of sequence
    assert(a.size() == 3);
    assert(!a.erase(4)); // erase returns false when out of bounds
//    assert(a.get(2, x)  &&  x == 2);

    assert(a.erase(2) == true); // removing from end
    assert(a.size() == 2);
    ItemType y = 99;
    assert(!a.get(2, y) &&  y == 99); // y is unchanged
    assert(a.insert(2,2) == 2); // insert back in at end
   
    assert(a.erase(1) == true); // removing from middle of ss
    assert(a.size() == 2);
    assert(a.insert(1,1) == 1); // insert back in at end
    assert(a.erase(2) == true);
    
// Testing remove()
    assert(a.insert(0) == 0);
    assert(a.insert(0) == 0);
    assert(a.insert(0) == 0);
    assert(a.size() == 5); // remove starting sequence
    assert(a.remove(0) == 4);
    assert(a.size() == 1);
    
    Sequence b;
    assert(b.remove(0) == 0);

// Testing set()
    Sequence c;
    assert(c.insert(0) == 0);
    assert(c.insert(1) == 1);
    assert(c.insert(2) == 2);
    assert(c.set(2,4) == true); // set() at end of sequence
    assert(c.get(2, y) &&  y == 4);
    assert(c.size() == 3); // size is 3 still
    
// Testing find()
    assert(b.find(0) == -1); // when seq is empty
    assert(c.find(0) == 0);
    assert(c.find(3) == -1); // not present value
    assert(c.find(2) == -1);

// Testing Copy Constructor
    Sequence d;
    assert(d.insert(0) == 0);
    assert(d.insert(1) == 1);
    Sequence e(d); // copying
    assert(e.get(0, y) &&  y == 0); // verifying values were copied over
    assert(e.get(1, y) &&  y == 1);

// Testing swap()
    Sequence f;
    assert(f.insert(100) == 0);
    d.swap(f);
    assert(d.get(0, y) &&  y == 100);
    assert(f.get(0, y) &&  y == 0); // both d and f's values were swapped
    assert(f.get(1, y) &&  y == 1);
    assert(d.size() == 1);
    assert(f.size() == 2);

// Testing concatReverse
    Sequence b1;
    assert(b1.insert(0,6) == 0);
    assert(b1.insert(1,5) == 1);
    assert(b1.insert(2,4) == 2);
    Sequence b2;
    
    assert(b2.insert(0,3) == 0);
    assert(b2.insert(1,2) == 1);
    assert(b2.insert(2,1) == 2);
    
    Sequence b3;
    assert(b3.insert(0,100) == 0);
    
    concatReverse(b1,b2,b3); // general case of concatReverse
    ItemType z;
    assert(b3.get(0,z) && z == 4);
    assert(b3.get(1,z) && z == 5);
    assert(b3.get(2,z) && z == 6);
    assert(b3.get(3,z) && z == 1);
    assert(b3.get(4,z) && z == 2);
    assert(b3.get(5,z) && z == 3);
    
    Sequence b4;
    assert(b4.insert(0,3) == 0);
    assert(b4.insert(1,2) == 1);
    assert(b4.insert(2,1) == 2);
    
    concatReverse(b4,b2,b4); // when the seq1 and results are the same
    assert(b4.get(0,z) && z == 1);
    assert(b4.get(1,z) && z == 2);
    assert(b4.get(2,z) && z == 3);
    assert(b4.get(3,z) && z == 1);
    assert(b4.get(4,z) && z == 2);
    assert(b4.get(5,z) && z == 3);
    
    Sequence ssempty1;
    Sequence ssempty2;
    concatReverse(ssempty1,ssempty2,b3); // when both seq1 and seq2 are empty
    assert(b3.empty());
    
    concatReverse(ssempty1,b2,b3); // when seq1 is empty
    assert(b3.get(0,z) && z == 1);
    assert(b3.get(1,z) && z == 2);
    assert(b3.get(2,z) && z == 3);
    
    concatReverse(b2,ssempty2,b3); // when seq2 is empty
    assert(b3.get(0,z) && z == 1);
    assert(b3.get(1,z) && z == 2);
    assert(b3.get(2,z) && z == 3);

    
    concatReverse(b3,ssempty2,b3); // when seq1 and result are the same, and seq2 is empty
    assert(b3.get(0,z) && z == 3);
    assert(b3.get(1,z) && z == 2);
    assert(b3.get(2,z) && z == 1);
    
}


int main() {
    
    test();
    cout << "Passed all test!" << endl;

}
