#ifndef GAME_H
#define GAME_H
#include <string>
#include "gameboard.h"
#include "player.h"
#include "gameitem.h"
#include "deck.h"

class Game
{
public:
    Game(const std::size_t size, const int playerCount, const int itemCount );
    //Game();
    void addPlayer( const std::string playerName );
    void setUp();
    void nextRound();

private:
    int round;
    int turn;
    Player *currentPlayer;

    GameBoard board;
    std::vector<Player*> players;
    std::vector<GameItem*> items;
    Deck deck;
    Deck discardpile;
};

#endif // GAME_H
