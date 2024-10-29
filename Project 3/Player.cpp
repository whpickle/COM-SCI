//
//  Player.cpp
//  Project 3
//
//  Created by Wolfe Pickett on 5/24/23.
//

#include "Player.h"
#include <string>

//========================================================================
// Timer t;                 // create and start a timer
// t.start();               // restart the timer
// double d = t.elapsed();  // milliseconds since timer was last started
//========================================================================

#include <chrono>

class Timer
{
  public:
    Timer()
    {
        start();
    }
    void start()
    {
        m_time = std::chrono::high_resolution_clock::now();
    }
    double elapsed() const
    {
        std::chrono::duration<double, std::milli> diff =
                          std::chrono::high_resolution_clock::now() - m_time;
        return diff.count();
    }
  private:
    std::chrono::high_resolution_clock::time_point m_time;
};


Player::Player(std::string name): m_name(name) {}

std::string Player::name() const {
    return m_name;
}

bool Player::isInteractive() const {
    return false;
}

int Player::chooseMove(const Board& b, Side s) const
{
    return -1;
}

Player::~Player() {}

HumanPlayer::HumanPlayer(std::string name) : Player(name) {}

bool HumanPlayer::isInteractive() const
{
    return true;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const
{
    int choice;
    
    if (b.beansInPlay(NORTH) == 0 || b.beansInPlay(SOUTH) == 0)
        return -1; //if beans in both sides' holes are empty, return -1
    
    do {
        std::cout << "Select a hole " << this->name() << ": ";
        std::cin >> choice;
        
    } while(choice <= 0 || choice > b.holes() || b.beans(s, choice) == 0);

    return choice;
}

BadPlayer::BadPlayer(std::string name) : Player(name) {}

int BadPlayer::chooseMove(const Board& b, Side s) const
{
    if (b.beansInPlay(NORTH) == 0 || b.beansInPlay(SOUTH) == 0)
        return -1; //if beans in both sides' holes are empty, return -1
    
    int i = 1;
    while (i <= b.holes())
    {
        if (b.beans(s, i) != 0)
            return i;
        i++;
    }
    
    return -1;
}

SmartPlayer::SmartPlayer(std::string name) : Player(name) {}

int SmartPlayer::eval(const Board& b, Side s) const
{
    int value = 0;
    
    // Check if one move can lead to a win or loss
    if (b.beansInPlay(SOUTH) == 0 || b.beansInPlay(NORTH) == 0) {
        if (b.beans(SOUTH, 0) + b.beansInPlay(SOUTH) > b.beans(NORTH, 0))
            value = INT_MAX; // Winning position
        else if (b.beans(SOUTH, 0) + b.beansInPlay(SOUTH) < b.beans(NORTH, 0))
            value = INT_MIN; // Losing position
        else
            value = 0; // Draw
        return value;
    }
    
    // Calculate the difference between player's pot and opponent's pot
    value = b.beans(SOUTH, 0) - b.beans(NORTH, 0);
    
    // Check if one move can grant an extra turn
    for (int i = 1; i <= b.holes(); i++) {
        if (b.beans(s, i) == i) {
            value += 1000; // Extra turn possibility
            break;
        }
    }
    
    // Check if one move can capture opponent's seeds
    for (int i = 1; i <= b.holes(); i++) {
        if (b.beans(s, i) == i && b.beans(opponent(s), i) > 0) {
            value += 100; // Capture possibility
            break;
        }
    }
    
    return value;
}

void SmartPlayer::minimax(int& bestHole, int& value, const Board& b, Side s, int searchDepth, int alpha, int beta) const
{
    value = (s == NORTH) ? INT_MAX : INT_MIN;

    if (b.beansInPlay(SOUTH) == 0 || b.beansInPlay(NORTH) == 0)
    {
        bestHole = -1;
        if (b.beans(SOUTH, 0) > b.beans(NORTH, 0))
            value = INT_MAX; // set to positive infinity if South wins
        else if (b.beans(SOUTH, 0) < b.beans(NORTH, 0))
            value = INT_MIN; // set to negative infinity if North wins
        else
            value = 0; // set value to 0 if there's a tie
        return;
    }

    if (searchDepth <= 0)
    {
        bestHole = -1;
        value = eval(b, s);
        return;
    }

    Side endSide;

    for (int hole = 1; hole <= b.holes(); hole++)
    {
        int endHole;

        Board tempB(b);

        if (!tempB.sow(s, hole, endSide, endHole))
            continue;

        if (endHole != 0 && endSide == s && tempB.beans(s, endHole) - 1 == 0 && tempB.beans(opponent(s), endHole) != 0)
        {
            tempB.moveToPot(s, endHole, s);
            tempB.moveToPot(opponent(s), endHole, s);
            value += 2;
        }

        while (endHole == 0 && s == endSide)
        {
            int n;
            do
            {
                n = (rand() % b.holes()) + 1;
            } while (tempB.beans(s, n) == 0 && tempB.beansInPlay(s) != 0 && tempB.beansInPlay(opponent(s)) != 0);

            if (!tempB.sow(s, n, endSide, endHole))
                break;
            value++;
        }

        if (tempB.beansInPlay(SOUTH) == 0 || tempB.beansInPlay(NORTH) == 0)
        {
            for (int i = 1; i <= b.holes(); i++)
            {
                tempB.moveToPot(s, i, s);
                tempB.moveToPot(opponent(s), i, opponent(s));
            }
        }

        int opponentHole, opponentValue;

        minimax(opponentHole, opponentValue, tempB, opponent(s), searchDepth - 1, alpha, beta);

        if (s == SOUTH)
        {
            if (opponentValue > value)
            {
                bestHole = hole;
                value = opponentValue;
            }
            alpha = std::max(alpha, value);
        }
        else
        {
            if (opponentValue < value)
            {
                bestHole = hole;
                value = opponentValue;
            }
            beta = std::min(beta, value);
        }

        if (alpha >= beta)
            break;
    }
}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
    int bestHole = -1;
    int value = (s == NORTH) ? INT_MAX : INT_MIN;

    if (b.beansInPlay(SOUTH) == 0 || b.beansInPlay(NORTH) == 0)
        return -1;

    int searchDepth = 10;
    int alpha = INT_MIN;
    int beta = INT_MAX;
    
    Timer timer;
    double timeLimit = 5000; // 5 seconds in milliseconds
    
    if (timer.elapsed() > timeLimit)
    {
        value = eval(b, s);
    }
        
    for (int hole = 1; hole <= b.holes(); hole++)
    {
        
        if (b.beans(s, hole) != 0)
        {
            Board tempB(b);
            Side endSide;
            int endHole;

            if (!tempB.sow(s, hole, endSide, endHole))
                continue;

            if (endHole != 0 && endSide == s && tempB.beans(s, endHole) - 1 == 0 && tempB.beans(opponent(s), endHole) != 0)
            {
                tempB.moveToPot(s, endHole, s);
                tempB.moveToPot(opponent(s), endHole, s);
            }

            int opponentHole, opponentValue;

            minimax(opponentHole, opponentValue, tempB, opponent(s), searchDepth - 1, alpha, beta);

            if (s == SOUTH)
            {
                if (opponentValue > value)
                {
                    bestHole = hole;
                    value = opponentValue;
                }
                alpha = std::max(alpha, value);
            }
            else
            {
                if (opponentValue < value)
                {
                    bestHole = hole;
                    value = opponentValue;
                }
                beta = std::min(beta, value);
            }
        }
    }
    return bestHole;
}

