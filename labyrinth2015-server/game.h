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
    Game();
    Game(const std::size_t size, const int playerCount, const int itemCount );
    ~Game();
    std::vector<Player*> &getPlayers() {return players;}
    void addPlayer( const std::string playerName );
    void addPlayer( Player *newPlayer, const int x = -1, const int y = -1 );
    void setUp();
    void nextRound();
    std::string getRoundHeader();
    std::string getRoundStr();
    std::string getBoardStr();
    std::string getFreeFieldString();
    GameBoard *getBoard() {return &board;}
    bool finish();
    static Game *loadGame(const std::string savegame);
    int shift(const int num, const int direction);
    bool move(const int direction);
    bool turnEnd();
    void setRound(const int newRound) {round = newRound;}
    GameItem* getItemByName(const char figure);

private:
    int round;
    Player *currentPlayer;
    int winScore;
    GameBoard board;
    std::vector<Player*> players;
    std::vector<GameItem*> items;
    Deck *deck;
    Deck *discardpile;
};

#endif // GAME_H
