//
//  main.cpp
//  Project2
//
//  Created by Wolfe Pickett on 1/30/24.
//

#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Map m;
    assert(m.insert("Fred", 123));
    assert(m.insert("Ethel", 456));
    assert(m.size() == 2);
    ValueType v = 42;
    assert(!m.get("Lucy", v)  &&  v == 42);
    assert(m.get("Fred", v)  &&  v == 123);
    v = 42;
    KeyType x = "Lucy";
    assert(m.get(0, x, v)  &&  x == "Ethel"  &&  v == 456);
    KeyType x2 = "Ricky";
    assert(m.get(1, x2, v)  &&  x2 == "Fred"  &&  v == 123);
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}

