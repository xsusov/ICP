/**
 * @project LABYRINTH2015
 * ICP project
 * @class Game
 * @author xsusov01
 * @email  xsusov01@stud.fit.vutbr.cz
 * @author xbandz00
 * @email  xbandz00@stud.fit.vutbr.cz
 * @file game.cpp
 * @date 2015/05/10
 * @brief class for wrapping game model and providing Viewer/Controller independtent Model
*/
#include <iostream>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <math.h>
#include "game.h"
#include "strings.h"


using namespace labyrinth;

/**
 * @brief Game::Game constructor
 */
Game::Game()
{
}

/**
 * @brief Game::Game parametrized constructor
 * @param size  board size of new game
 * @param playerCount number of players in game
 * @param itemCount number of items
 */
Game::Game(const std::size_t size, const int playerCount, const int itemCount )
    : round{0},
      lastNum {-1},
      lastDirection {-1},
      currentPlayer{nullptr},
      board{GameBoard( size )}
{
    players.reserve(playerCount);           /// reserve space for number of players in players vector
    GameItem::fillVector(items, itemCount); /// fills items vector with all items
    deck = new Deck(items);                 /// deck of quest cards - filled with cards for each item at start
    discardpile = new Deck();               /// deck for used cards - empty at start
    winScore = itemCount / playerCount;     /// number of items needed to find by player to win
}

/**
 * @brief Game::~Game destructor
 */
Game::~Game()
{
    for(auto p : players)
        delete p;

    for(auto i : items)
        delete i;

    delete deck;
    delete discardpile;
}

/**
 * @brief Game::addPlayer add
 * @param playerName
 */
void Game::addPlayer(const std::string playerName)
{
    players.push_back(new Player(playerName));
}

void Game::addPlayer(Player *newPlayer, const int x, const int y)
{
    players.push_back(newPlayer);
    if( x >= 0 && x < board.getSize() && y >= 0 && y < board.getSize() ){
        board.getField(x, y)->addPlayer(newPlayer);
        newPlayer->placeOnField(board.getField(x, y));
    }
}


/**
 * @brief Game::setUp prepares Game's gameboard before starting new game
 */
void Game::setUp()
{
    board.setUpFields();
    board.setUpPlayers(players);
    board.setUpItems(items);
}

/**
 * @brief Game::nextRound raises round counter and changes active player
 */
void Game::nextRound()
{
    currentPlayer = players[round++ % (int)players.size()];

    if( currentPlayer->getCard() == nullptr ){
        currentPlayer->drawCard(*deck);
    }
}

/**
 * @brief Game::getRoundHeader
 * @return string of header for current round containg information about round and cactive player
 */
std::string Game::getRoundHeader()
{
    std::stringstream header;
    header << strRound << floor((float)round / ((int)players.size() - 0.01)) + 1 << std::endl << currentPlayer->getName() << strTurn << std::endl
           << strFigure << currentPlayer->getFigure() << " " << strScore <<  currentPlayer->getScore() << std::endl
           << strQuest << currentPlayer->getQuest() << std::endl;

    return header.str();
}

std::string Game::getRoundStr()
{
    std::stringstream ss;   /// stream for round str
    ss << logEndOfRound
       << round << logD                 /// ROUND
       << (int)board.getSize() << logD  /// SIZE
       << (int)items.size() << logD     /// ITEMS
       << (int)players.size() << logD;  /// PLAYERS COUNT

    /// DECK
    ss << (int)deck->size() << logD;
    for( Card* c : deck->getCardStack() ){
        ss << c->getItem()->getFigure();
    }
    ss << logD;

    /// DISCARD PILE
    ss << (int)discardpile->size() << logD;
    for( Card* c : discardpile->getCardStack() ){
        ss << c->getItem()->getFigure();
    }
    ss << logD;

    /// BOARD FIELDS
    BoardField *field;
    for( int y = 0; y < (int)board.getSize(); y++ ){
        for( int x = 0; x < (int)board.getSize(); x++ ){
            field = board.getField(x, y);
            /// FIELDS PATH + ITEM
            ss << field->getLogNum() << field->getLogItem();
        }
    }

    field = board.getFreeField();
    ss << field->getLogNum() << field->getLogItem() << logD;

    /// PLAYERS INFO
    for( Player* p : players ){
        ss << p->getName() << logD
           << p->getFigure() << logD
           << p->getScore() << logD
           << p->getItem() << logD
           << p->getCurField()->getPosX() << logD
           << p->getCurField()->getPosY() << logD;
    }

    ss << std::endl;    /// END OF ROUND
    return ss.str();
}

std::string Game::getBoardStr()
{
    return board.getStr();
}

std::string Game::getFreeFieldString()
{
    return board.getFreeField()->getStr();
}

bool Game::finish()
{
    return currentPlayer->getScore() >= winScore;
}

GameItem *Game::getItemByName(const char figure)
{
    if(figure == '0'){
        return nullptr;
    }

    for(GameItem *item : items){
        if( item->getFigure() == figure){
            return item;
        }
    }

    return nullptr;
}


Game *Game::loadGame(const std::string savegame)
{
    std::string round {""}, lastround {""};
    std::ifstream save;
    save.open( savegame, std::ifstream::in );

    std::ofstream newLog;
    newLog.open(logfile, std::fstream::out | std::fstream::trunc );

    //lastround = round;

    while( std::getline(save, round) ){
        newLog << round << std::endl;
       /// newLog.flush();
        lastround = round;
    }


/*
    std::getline(save, round);
    lastround = round;
    while( std::getline(save, round) ){
        newLog << lastround << std::endl;
        newLog.flush();
        lastround = round;
    }
    lastround = round;
    */
    newLog.flush();
    newLog.close();
    save.close();

    std::cout << "Loaded: " << lastround << std::endl;
    std::cout.flush();

    /// example:
    /// ###2;11;12;2;kok;@;0;k;1;6;oz;&;0;d;10;0;10;lcefjgbhia0;6050e0a0e0a0e0ege060c05060b0a0c0c0b090e0ae5070e07
    /// la0b0c070d070e0dd70e030c0a060e030a0705070707030e0a0b050703fd0709070d0a0e0c030a0c05070aae050e0e0d0c07030d0
    /// 303cd0e0aka05060c0d0d070c0b0c0b030d0e0e060di60603060ej60d09050a0d03090b090b0a0b0a0b09b9ha0;
    /// now fun with parsing
    if(lastround.substr(0,3) != logEndOfRound){
        throw brokenSave;
    }

    int roundN;
    int len;
    int num;
    int size;
    int itemCount;
    int playerCount;

    std::stringstream ss(lastround);
    std::string token;

    /// get round
    std::getline(ss, token, logD);
    roundN = std::stoi(token.substr(3));

    /// get size
    std::getline(ss, token, logD);
    size = std::stoi(token);

    /// get itemcount
    std::getline(ss, token, logD);
    itemCount = std::stoi(token);

    /// get playercount
    std::getline(ss, token, logD);
    playerCount = std::stoi(token);

    Game *loadedGame {nullptr};
    try{
        loadedGame = new Game( size, playerCount, itemCount );
        loadedGame->setRound(roundN);
    }
    catch(std::exception &ex){
        std::cerr << ex.what() << std::endl;
        return nullptr;
    }

    /// get Deck
    std::getline(ss, token, logD);
    len = std::stoi(token);
    std::getline(ss, token, logD);
    GameItem *newItem {nullptr};
    loadedGame->deck->clear();
    for( int i = 0; i < len; i++){
        newItem = loadedGame->getItemByName(token.at(i));
        loadedGame->deck->push(new Card(newItem, newItem->getName()));
    }

    /// get Discard
    std::getline(ss, token, logD);
    len = std::stoi(token);
    std::getline(ss, token, logD);
    loadedGame->discardpile->clear();
    for( int i = 0; i < len; i++){
        newItem = loadedGame->getItemByName(token.at(i));
        loadedGame->discardpile->push(new Card(newItem, newItem->getName()));
    }

    /// get and setup boardfields
    for( int y = 0; y < size; y++){
        for( int x = 0; x < size; x++){
            num = ss.get() - '0';
            newItem = loadedGame->getItemByName(ss.get());
            loadedGame->board.setField(x, y, GameBoard::makeTargetBoardField( x, y, num, newItem ) );
        }
    }

    num = ss.get() - '0';
    newItem = loadedGame->getItemByName(ss.get());
    loadedGame->board.setFreeField( GameBoard::makeTargetBoardField( posFree, posFree, num, newItem ) );

    ss.get();
    /// players
    char figure;
    int score;
    int x, y;
    /// kok;@;0;k;1;6;
    std::string playerName {""};
    Player *newPlayer;
    for(int i = 0; i < playerCount; i++){
        std::getline(ss, playerName, logD);
        figure = ss.get();
        ss.get();
        std::getline(ss, token, logD);
        score = std::stoi(token);
        newItem = loadedGame->getItemByName(ss.get());
        ss.get();
        std::getline(ss, token, logD);
        x = std::stoi(token);
        std::getline(ss, token, logD);
        y = std::stoi(token);
        newPlayer = new Player( playerName, figure, score, (newItem != nullptr ? new Card(newItem, newItem->getName()) : nullptr ) ) ;
        loadedGame->addPlayer( newPlayer, x, y );
    }

    loadedGame->currentPlayer = loadedGame->players[(roundN - 1) % playerCount];
    if( loadedGame->currentPlayer->getCard() == nullptr ){
        loadedGame->currentPlayer->drawCard(*(loadedGame->deck));
    }

    return loadedGame;
}

bool Game::saveGame(const std::string savegame)
{
    std::string round {""};
    std::ifstream log;
    log.open(logfile, std::ifstream::in );

    std::ofstream save;
    save.open(savegame,  std::fstream::out | std::fstream::trunc );
    if(!save.is_open()){
        return false;
    }

    while(std::getline(log, round)){
        save << round << std::endl;
        save.flush();
    }

    return true;
}

/**
 * @brief Game::shift takes direction of shifting and number of row/column
 *        checks that this shift doen't reverse last turn's shift and do it on board if possible
 * @param num number of row/column to shift
 * @param direction shifting direction
 * @return true wheter this shifting won't reverse shifting in last turn
 */
bool Game::shift(const int num, const int direction)
{
    /// check for last move
    if( round > (int)players.size()){
        if( lastDirection == opositeDirection(direction) && lastNum == num){
            return false;   /// this shifiting would reverse shifitng in last turn
        }
    }
    board.shift(num, direction); /// shift and save info for check in next turn
    lastNum = num;
    lastDirection = direction;
    return true;
}

/**
 * @brief Game::isUndoPossible checks if undo is availabile this turn
 * @return undo availability
 */
bool Game::isUndoPossible()
{   /// can't undo start of game
    return round > (int)players.size();
}

/**
 * @brief Game::undo reverse game state to beginning of current player's previous turn
 * @return succes of undo operation
 */
bool Game::undo()
{
    int roundAfterUndo = round - ((int)players.size() + 1);
    std::string roundStr;

    std::ifstream log;
    log.open( logfile, std::ifstream::in );

    std::ofstream newLog;
    newLog.open(tmplogfile,  std::fstream::out | std::fstream::trunc );

    for(int i = 0; i <= roundAfterUndo; i++){
        if( !(std::getline(log, roundStr)) ){
            std::cerr << strUndoErr << std::endl;
            std::remove(tmplogfile.c_str());
            return false;
        }

        std::cout << roundStr << std::endl;
        newLog << roundStr << std::endl;
        newLog.flush();
    }

    log.close();
    return true;
}

/**
 * @brief Game::move tries to move current player in given direction
 *        also checks new player field for item hes finding and if possible pick it
 * @param direction for player move on boardfield
 * @return possibility of player move in direction
 */
bool Game::move(const int direction)
{
    if(!board.movePlayer(currentPlayer, direction)){
        return false;
    }

    if(currentPlayer->pickupItem()){
        discardpile->push(currentPlayer->getCard());
        currentPlayer->dropCard();
    }
    return true;
}

/**
 * @brief Game::turnEnd checks wheter player picked item this turn and thus his turn ends
 * @return wheter player picked up item this turn
 */
bool Game::turnEnd()
{
    return currentPlayer->getCard() == nullptr;
}

