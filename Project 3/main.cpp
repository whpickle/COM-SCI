//
//  main.cpp
//  Project 3
//
//  Created by Wolfe Pickett on 5/22/23.
//

#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

void doGameTests()
{
    BadPlayer bp1("Bart");
    BadPlayer bp2("Homer");
    Board b(3, 0);
    b.setBeans(SOUTH, 1, 2);
    b.setBeans(NORTH, 2, 1);
    b.setBeans(NORTH, 3, 2);
    Game g(b, &bp1, &bp2);
    bool over;
    bool hasWinner;
    Side winner;
      //    Homer
      //   0  1  2
      // 0         0
      //   2  0  0
      //    Bart
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
    g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);

    g.move(SOUTH);
      //   0  1  0
      // 0         3
      //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

    g.move(NORTH);
      //   1  0  0
      // 0         3
      //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

    g.move(SOUTH);
      //   1  0  0
      // 0         3
      //   0  0  1
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);

    g.move(NORTH);
      //   0  0  0
      // 1         4
      //   0  0  0
    g.status(over, hasWinner, winner);
    assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
    assert(hasWinner && winner == SOUTH);
}

void test()
{
    
    // Test Case 1: Empty Board
    Board b1(0, 0);
    assert(b1.beansInPlay(NORTH) == 0);
    assert(b1.beansInPlay(SOUTH) == 0);
    assert(b1.totalBeans() == 0);

    // Test Case 2: One Hole
    Board b2(1, 3);
    assert(b2.beansInPlay(NORTH) == 3);
    assert(b2.beansInPlay(SOUTH) == 3);
    assert(b2.totalBeans() == 6);

    // Test Case 3: Negative beans
    Board b3(2, -1);
    assert(b3.beansInPlay(NORTH) == 0);
    assert(b3.beansInPlay(SOUTH) == 0);
    assert(b3.totalBeans() == 0);
    

}

// Test Board class
void testBoard() {
    Board board(6, 4);

    // Test beansInPlay()
    assert(board.beansInPlay(NORTH) == 24);
    assert(board.beansInPlay(SOUTH) == 24);

    // Test totalBeans()
    assert(board.totalBeans() == 48);

    // Test setBeans()
    board.setBeans(NORTH, 2, 3);
    assert(board.beans(NORTH, 2) == 3);

    // Test beans()
    assert(board.beans(NORTH, 3) == 4);

    // Test moveToPot()
    assert(board.moveToPot(NORTH, 4, NORTH));
    assert(board.beans(NORTH, 4) == 0);
    assert(board.beans(NORTH, POT) == 4);

    // Test sow()
    Side endSide;
    int endHole;
    assert(board.sow(SOUTH, 1, endSide, endHole));
    assert(endSide == NORTH);
    assert(endHole == 3);
    assert(board.beans(SOUTH, 1) == 0);
    assert(board.beans(NORTH, 2) == 5);
}

void doPlayerTests()
{
    HumanPlayer hp("Marge");
    assert(hp.name() == "Marge"  &&  hp.isInteractive());
    BadPlayer bp("Homer");
    assert(bp.name() == "Homer"  &&  !bp.isInteractive());
    SmartPlayer sp("Lisa");
    assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
    Board b(3, 2);
    b.setBeans(SOUTH, 2, 0);
    cout << "=========" << endl;
    int n = hp.chooseMove(b, SOUTH);
    cout << "=========" << endl;
    assert(n == 1  ||  n == 3);
    n = bp.chooseMove(b, SOUTH);
    assert(n == 1  ||  n == 3);
    n = sp.chooseMove(b, SOUTH);
    assert(n == 1  ||  n == 3);
}

//void testSow()
//{
//    //test sow
//    Board c(6, 4);
//    //    Side endSide;
//    int endhole;
//    //Test the Sow Function
//    assert(c.sow(NORTH, 3, endSide, endhole));
//    assert(endhole == 1);
//    assert(endSide == SOUTH);
//
//    assert(c.sow(NORTH, 1, endSide, endhole));
//    assert(endhole == 4);
//    assert(endSide == SOUTH);
//
//    assert(!c.sow(NORTH, 0, endSide, endhole));
//    assert(c.setBeans(SOUTH, 1, 20));
//    assert(c.sow(SOUTH, 1, endSide, endhole));
//    assert(endhole == 6);
//    assert(endSide == NORTH);
//    assert(c.sow(SOUTH, 1, endSide, endhole));
//    assert(endhole == 2);
//    assert(endSide == SOUTH);
//}


int main()
{
    doGameTests();
    cout << "Passed all tests" << endl;
}
