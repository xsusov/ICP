#include "game.h"


Game::Game(const std::size_t size, const int playerCount, const int itemCount )
    : round{0},
      currentPlayer{nullptr},
      board{GameBoard( size )}
{
    players.reserve(playerCount);
    GameItem::fillVector(items, itemCount);
    deck = Deck(items);
    discardpile = Deck();
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
}
