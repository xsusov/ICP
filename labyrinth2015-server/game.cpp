#include <sstream>
#include "game.h"
#include "strings.h"


using namespace labyrinth;

Game::Game()
{

}

Game::Game(const std::size_t size, const int playerCount, const int itemCount )
    : round{0},
      currentPlayer{nullptr},
      board{GameBoard( size )}
{
    players.reserve(playerCount);
    GameItem::fillVector(items, itemCount);
    deck = Deck(items);
    discardpile = Deck();
    winScore = itemCount / playerCount;
}

Game::~Game()
{
    for(auto p : players)
        delete p;

    for(auto i : items)
        delete i;
}

void Game::addPlayer(const std::string playerName)
{
    players.push_back(new Player(playerName));
}

void Game::setUp()
{
    board.setUpFields();
    board.setUpPlayers(players);
    board.setUpItems(items);
}

void Game::nextRound()
{
    round++;
    currentPlayer = players[turn++ % (int)players.size()];

    if( currentPlayer->getCard() == nullptr ){
        currentPlayer->drawCard(deck);
    }
}

std::string Game::getRoundHeader()
{
    std::stringstream header;

    header << strRound << round << std::endl << currentPlayer->getName() << strTurn << std::endl;
    header << strQuest << currentPlayer->getQuest() << std::endl;

    return header.str();
}

std::string Game::getRoundStr()
{
    std::stringstream ss;
    /// ROUND
    ss << round << logD;
    /// TURN
    ss << turn << logD;
    /// ITEMS

    /// PLAYERS COUNT
    ss << (int)players.size() << logD;
    /// PLAYERS INFO
    for( Player* p : players ){
        ss << p->getName() << logD
           << p->getFigure() << logD
           << p->getScore() << logD
           << p->getCard()->getItem()->getFigure() << logD
           << p->getCurField()->getPosX() << logD
           << p->getCurField()->getPosY() << logD;
    }

    /// GAMEBOARD
    ss << board.getSize() << logD;
    /// BOARD FIELDS



    ss << logEndOfRound;

    return ss.str();
}

std::string Game::getBoardStr()
{
    return "";
}

std::string Game::getFreeFieldString()
{
    return "";
}

bool Game::finish()
{
    return currentPlayer->getScore() >= winScore;
}

Game *Game::loadGame(std::string savegame)
{
    return new Game();
}

int Game::shift(const int num, const int direction)
{
    board.shift(num, direction);
    /// @todo: check for last move undo
    ///
    return 0;
}

int Game::move(const int direction)
{
    return board.movePlayer(currentPlayer, direction);
}

bool Game::turnEnd()
{
    return currentPlayer->getCard() == nullptr;
}

