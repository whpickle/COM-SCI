//
//  Player.h
//  Project 3
//
//  Created by Wolfe Pickett on 5/24/23.
//

#ifndef Player_h
#define Player_h

#include <iostream>
#include <string>

#include "Side.h"
#include "Board.h"

class Player {
public:
    Player(std::string name);
    //Create a Player with the indicated name.

    std::string name() const;
    //Return the name of the player.

    virtual bool isInteractive() const;
    //Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.

    virtual int chooseMove(const Board& b, Side s) const = 0;
    //Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.

    virtual ~Player();
    //Since this class is designed as a base class, it should have a virtual destructor.
    
private:
    std::string m_name;
};


class HumanPlayer : public Player {
//A HumanPlayer chooses its move by prompting a person running the program for a move (reprompting if necessary until the person enters a valid hole number), and returning that choice. We will never test for a situation where the user doesn't enter an integer when prompted for a hole number. (The techniques for dealing with the issue completely correctly are a distraction to this project, and involve either a function like stoi or strtol, or the type istringstream.)
public:
    HumanPlayer(std::string name);
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const;
};

class BadPlayer : public Player {
//A BadPlayer is a computer player that chooses an arbitrary valid move and returns that choice. "Arbitrary" can be what you like: leftmost, nearest to pot, fewest beans, random, etc.. The point of this class is to have an easy-to-implement class that at least plays legally.
public:
    BadPlayer(std::string name);
    int chooseMove(const Board& b, Side s) const;
};

class SmartPlayer: public Player {
//Here's your chance to shine. A SmartPlayer chooses a valid move and returns it. For any game played on a board of up to six holes per side, with up to four initial beans per hole, SmartPlayer::chooseMove must return its choice in no more than five seconds on the SEASnet Linux server lnxsrv07.seas.ucla.edu or lnxsrv09.seas.ucla.edu: (We'll give you a way of determining the time soon; until then, you can meet this requirement by limiting the depth of your game tree search or the number of game tree positions you explore to a limit you determine experimentally.) SmartPlayer::chooseMove will be worth about 15-20% of the points for this project.
public:
    SmartPlayer(std::string name);
    virtual int chooseMove(const Board& b, Side s) const;

private:
    int eval(const Board& b, Side s) const;
    void minimax(int& bestHole, int& value, const Board& b, Side s, int searchDepth, int alpha, int beta) const;
};

#endif /* Player_h */

