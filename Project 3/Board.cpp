//
//  Board.cpp
//  Project 3
//
//  Created by Wolfe Pickett on 5/24/23.
//

#include "Board.h"
#include "Side.h"
#include <iostream>

using namespace std;

Board::Board(int nHoles, int nInitialBeansPerHole)
{
    if (nHoles < 0)
        nHoles = 1;
    if (nInitialBeansPerHole < 0)
        nInitialBeansPerHole = 0;
    
    m_holes = nHoles;

    northVector.push_back(0); // pot starts at 0
    for (int i = 1; i <= m_holes; i++) {
        northVector.push_back(nInitialBeansPerHole);
    }

    southVector.push_back(0); // pot starts at 0
    for (int i = 1; i <= m_holes; i++) {
        southVector.push_back(nInitialBeansPerHole);
    }
}

int Board::holes() const
{
    return m_holes;
}

int Board::beans(Side s, int hole) const
{
    if (s == NORTH && hole >= 0 && hole <= m_holes)
        return northVector[hole];

    else if (s == SOUTH && hole >= 0 && hole <= m_holes)
        return southVector[hole];
    else
        return -1;
}


int Board::beansInPlay(Side s) const {
    
    int count = 0;
    if (s == SOUTH) {
        for (int i = 1; i <= m_holes; i++) {
            count += southVector[i];
        }
        return count;
    } else if (s == NORTH) {
        for (int i = 1; i <= m_holes; i++) {
            count += northVector[i];
        }
        return count;
    } else {
        return 0;
    }
}


int Board::totalBeans() const
{
    int count = 0;
    for (int i = 0; i <= m_holes; i++) { // Include the pots (index 0)
        count += southVector[i];
        count += northVector[i];
    }
    return count;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
    if(hole > m_holes || hole <= 0 || beans(s, hole) == 0) // invalid hole
        return false;
    
    int count;
    if (s == NORTH) {
        count = northVector[hole];
        northVector[hole] = 0;
    }
    else {
        count = southVector[hole];
        southVector[hole] = 0;
    }
        
    endHole = hole; // initialize the ending hole to the starting hole
    endSide = s;    // initialize the ending side to the current side

    while (count > 0)
    {
        if (endHole == 0) // check if the last hole was reached
        {
            endHole = m_holes;
            endSide = opponent(endSide);
        }
        else if (endHole == m_holes && endSide == SOUTH)
        {
            if (s == SOUTH)
                endHole = 0;
            else
                endHole = m_holes;
        }
        else if (endHole == 1 && endSide == NORTH)
        {
            if (s == NORTH)
                endHole = 0;
            else
                endHole = 1;
        }
        else
        {
            if (endSide == NORTH)
                endHole -= 1;
            else
                endHole += 1;
        }

        if (endSide == NORTH)
            northVector[endHole]++;
        else
            southVector[endHole]++;

        count--;
    }
    return true;

}

bool Board::moveToPot(Side s, int hole, Side potOwner)
{
    if (hole > m_holes || hole <= 0)
        return false;

    int count = 0;
    if (s == NORTH) {
        count = northVector[hole];
        northVector[hole] = 0;

        if (potOwner == NORTH)
            northVector[0] += count;
        else
            southVector[0] += count;
    } else {
        count = southVector[hole];
        southVector[hole] = 0;

        if (potOwner == NORTH)
            northVector[0] += count;
        else
            southVector[0] += count;
    }
    return true;
}

bool Board::setBeans(Side s, int hole, int beans)
{
    if (hole > m_holes || hole < 0) // invalid hole
        return false;
    if (beans < 0)
        return false;

    if (s == SOUTH) {
        southVector[hole] = beans;
    } else {
        northVector[hole] = beans;
    }
    return true;
}

