#include <fstream>
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
    currentPlayer = players[round++ % (int)players.size()];

    if( currentPlayer->getCard() == nullptr ){
        currentPlayer->drawCard(deck);
    }
}

std::string Game::getRoundHeader()
{
    std::stringstream header;

    header << strRound << (round / (int)players.size()) + 1 << std::endl << currentPlayer->getName() << strTurn << std::endl
           << strFigure << currentPlayer->getFigure() << " " << strScore <<  currentPlayer->getScore() << std::endl
           << strQuest << currentPlayer->getQuest() << std::endl;

    return header.str();
}

std::string Game::getRoundStr()
{
    std::stringstream ss;
    ss << logEndOfRound;
    /// ROUND
    ss << round << logD;

    /// SIZE
    ss << (int)board.getSize() << logD;

    /// ITEMS
    ss << (int)items.size() << logD;

    /// PLAYERS COUNT
    ss << (int)players.size() << logD;

    /// PLAYERS INFO
    for( Player* p : players ){
        ss << p->getName() << logD
           << p->getFigure() << logD
           << p->getScore() << logD
           << p->getItem() << logD
           << p->getCurField()->getPosX() << logD
           << p->getCurField()->getPosY() << logD;
    }

    /// DECK
    ss << (int)deck.size() << logD;
    for( Card* c : deck.getCardStack() ){
        ss << c->getItem()->getFigure();
    }

    /// DISCARD PILE
    ss << (int)discardpile.size() << logD;
    for( Card* c : discardpile.getCardStack() ){
        ss << c->getItem()->getFigure();
    }

    /// BOARD FIELDS
    BoardField *field;
    char itFig;
    int pathChar;
    for( int y = 0; y < (int)board.getSize(); y++ ){
        for( int x = 0; x < (int)board.getSize(); x++ ){
            field = board.getField(x, y);

            /// FIELDS PATH + ITEM
            pathChar = 0;
            for(int i = 0; i < 4; i++){
                if( field->getPath(i) != closed ){
                    pathChar += (1 << i);
                }
            }

            ss << std::hex << pathChar;

            itFig = field->drawItem();
            if( itFig == ' '){
                itFig = '0';
            }
            ss << itFig;
        }
    }

    field = board.getFreeField();
    pathChar = 0;
    for(int i = 0; i < 4; i++){
        if( field->getPath(i) != closed ){
            pathChar += (1 << i);
        }
    }

    ss << std::hex << pathChar;

    itFig = field->drawItem();
    if( itFig == ' '){
        itFig = '0';
    }

    ss << itFig;
    ss << logD;

    ss << std::endl;

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

Game *Game::loadGame(const std::string savegame)
{
    std::string round {""}, lastround {""};
    std::ifstream save;
    save.open( savegame, std::ifstream::in );

    std::ofstream newLog;
    newLog.open("labyrinth2.log",  std::fstream::out | std::fstream::trunc );

    while( std::getline(save, round) ){
        newLog << round << std::endl;
        newLog.flush();
        lastround = round;
    }


    std::cout << "Loaded: " << lastround << std::endl;
    std::cout.flush();


    /// example:
    /// ###5;5;12;2;ho;@;0;b;0;3;po;&;0;k;4;2;10;iajfehlgdc0;5;6c60e0a0c05gefal305d7e30dk50db90b0cib09h30djb090906a;
    /// now fun with parsing
    /*
    ss << logEndOfRound;
    /// ROUND
    ss << round << logD;
    /// TURN
    ss << turn << logD;
    /// ITEMS
    ss << (int)items.size() << logD;
    */

    if(!(lastround.substr(0,3) != logEndOfRound)){
        throw brokenSave;
    }

    int pos = lastround.find_first_of(logD);
    int pos2;
    /// get size
    std::string token;
    token = lastround.substr(4, 4 - pos);
    pos += token.length();

    std::stringstream ss;
    int size;
    ss << token;
    if( !(ss >> size)){
        throw brokenSave;
    }

    ss.str() = {""};

    int roundN;
    int itemCount;

    int playerCount;

    pos++;
    pos2 = lastround.find(logD, pos);
    token = lastround.substr(pos, pos2 - pos);
    ss << token;
    if( !(ss >> roundN)){
        throw brokenSave;
    }
    ss.str() = {""};
    pos++;
    pos2 = lastround.find(logD, pos);
    token = lastround.substr(pos, pos2 - pos);
    ss << token;
    if( !(ss >> itemCount)){
        throw brokenSave;
    }
    ss.str() = {""};
    pos++;
    pos2 = lastround.find(logD, pos);
    token = lastround.substr(pos, pos2 - pos);
    ss << token;
    if( !(ss >> playerCount)){
        throw brokenSave;
    }
    ss.str() = {""};

    /* check */
    std::cout << "round: " << roundN << "size: " << size << "itemcount: " << itemCount << "playerCount: " << playerCount << std::endl;

    Game *loadedGame = nullptr;
    try{
        loadedGame = new Game( size, playerCount, itemCount );
        loadedGame->setRound(roundN);
    }
    catch(std::exception &ex){
        std::cerr << ex.what() << std::endl;
        loadedGame = nullptr;
    }

    return loadedGame;
}

int Game::shift(const int num, const int direction)
{
    board.shift(num, direction);
    /// @todo: check for last move undo
    ///
    return 1;
}

bool Game::move(const int direction)
{
    if(!board.movePlayer(currentPlayer, direction)){
        return false;
    }

    if(currentPlayer->pickupItem()){
        discardpile.push(currentPlayer->getCard());
        currentPlayer->dropCard();
    }
    return true;
}

bool Game::turnEnd()
{
    return currentPlayer->getCard() == nullptr;
}

