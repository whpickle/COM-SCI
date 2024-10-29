//
//  Game.cpp
//  Project 3
//
//  Created by Wolfe Pickett on 5/24/23.
//

#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "Side.h"
#include <iostream>
using namespace std;

Game::Game(const Board& b, Player* south, Player* north)
    : m_board(b), m_south(south), m_north(north), m_turn(SOUTH)
{}

void Game::display() const
{
    cout << "\t" << m_north->name() << endl; // display NORTH name
    cout << "  ";
    
    // display NORTH side
    for (int i = 1; i <= m_board.holes(); i++)
    {
        cout << m_board.beans(NORTH, i) << "  ";
    }
    cout << endl;
    
    // display NORTH pot
    cout << " " << m_board.beans(NORTH, POT);
    
    for (int i = 1; i <= m_board.holes(); i++)
    {
        cout << "  ";
    }
    
    // display SOUTH pot
    cout << " " << m_board.beans(SOUTH, POT) << endl;
    
    // display SOUTH side
    cout << "  ";
    for (int i = 1; i <= m_board.holes(); i++)
    {
        cout << m_board.beans(SOUTH, i) << "  ";
    }
    cout << endl;
    
    cout << "\t" << m_south->name() << endl; // display SOUTH name
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
    if (m_board.beansInPlay(NORTH) != 0 && m_board.beansInPlay(SOUTH) != 0)
    {
        over = false;
        hasWinner = false;
        return;
    }
    over = true;
    
    if (m_board.beans(NORTH, 0) != m_board.beans(SOUTH, 0)) {
        
        if (m_board.beans(NORTH, 0) > m_board.beans(SOUTH, 0)) {
            winner = NORTH;
            hasWinner = true;
        }
        else {
            winner = SOUTH;
            hasWinner = true;
        }
    }
    else {
        hasWinner = false;
    }
}

bool Game::move(Side s)
{
    
    display();
    
    bool over = false;
    bool hasWinner = false;
    Side winner = NORTH;

    status(over, hasWinner, winner);

    int endHole;
    Side endSide;
    Player* tempPlayer;
    int hole;

    if (m_turn == NORTH) {
        tempPlayer = m_north;
    }
    else {
        tempPlayer = m_south;
    }

    hole = tempPlayer->chooseMove(m_board, m_turn);
    cout << tempPlayer->name() << " chooses hole " << hole << endl;

    m_board.sow(m_turn, hole, endSide, endHole);

    if (endHole != 0 && endSide == m_turn && m_board.beans(m_turn, endHole) == 1 && m_board.beans(opponent(m_turn), endHole) > 0)
    {
        m_board.moveToPot(opponent(m_turn), endHole, m_turn);
        m_board.moveToPot(m_turn, endHole, m_turn);
    }

    while (endHole == 0 && m_turn == endSide)
    {
        display();
        cout << tempPlayer->name() << " gets another turn." << endl;
        hole = tempPlayer->chooseMove(m_board, m_turn);

        if (hole == -1 || !m_board.sow(m_turn, hole, endSide, endHole))
            break;

        cout << tempPlayer->name() << " chooses hole " << hole << endl;
    }

    m_turn = opponent(m_turn);

    if (m_board.beansInPlay(NORTH) == 0)
    {
        display();
        cout << "Sweeping remaining beans into " << m_south->name() << "'s pot." << endl;
        for (int i = 1; i <= m_board.holes(); i++)
        {
            m_board.moveToPot(SOUTH, i, SOUTH);
        }
        return false;
    }
    else if (m_board.beansInPlay(SOUTH) == 0)
    {
        display();
        cout << "Sweeping remaining beans into " << m_north->name() << "'s pot." << endl;
        for (int i = 1; i <= m_board.holes(); i++)
        {
            m_board.moveToPot(NORTH, i, NORTH);
        }
        return false;
    }

    return true;
}

void Game::play()
{
    bool over, hasWinner;
    Side winner = SOUTH;  // Initialize winner to SOUTH
    display();
    do {
        move(winner);
        display();

        if (!m_south->isInteractive() && !m_north->isInteractive()) {
            cout << "Press ENTER";
            cin.ignore(10000, '\n');
        }

        status(over, hasWinner, winner);
        
    } while (!over);
    
    if (!hasWinner) {
        cout << "The game ended in a draw" << endl;
    }
    else {
        if (winner == NORTH) {
            cout << "The winner is " << m_north->name() << endl;
        }
        else {
            cout << "The winner is " << m_south->name() << endl;
        }
    }
}

int Game::beans(Side s, int hole) const
{
    return m_board.beans(s, hole);
}
