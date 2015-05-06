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

    /// DECK
    ss << (int)deck.size() << logD;
    for( Card* c : deck.getCardStack() ){
        ss << c->getItem()->getFigure();
    }

    ss << logD;

    /// DISCARD PILE
    ss << (int)discardpile.size() << logD;
    for( Card* c : discardpile.getCardStack() ){
        ss << c->getItem()->getFigure();
    }

    ss << logD;

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

    /// PLAYERS INFO
    for( Player* p : players ){
        ss << p->getName() << logD
           << p->getFigure() << logD
           << p->getScore() << logD
           << p->getItem() << logD
           << p->getCurField()->getPosX() << logD
           << p->getCurField()->getPosY() << logD;
    }

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


int Game::getNumFromSave(int pos, const std::string& savestring )
{

}

GameItem *Game::getItemByName(const char figure)
{
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
    newLog.open("labyrinth2.log",  std::fstream::out | std::fstream::trunc );

    while( std::getline(save, round) ){
        newLog << round << std::endl;
        newLog.flush();
        lastround = round;
    }


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
    int pos = lastround.find_first_of(logD);
    int pos2;
    int size;
    int itemCount;
    int playerCount;

    std::stringstream ss(lastround);
    std::string token;

    /* parse csv check
    while(std::getline(ss, token, logD))
        std::cout << token << std::endl;
    */

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

    /// get Deck
    std::getline(ss, token, logD);
    len = std::stoi(token);
    std::getline(ss, token, logD);
    GameItem *newItem {nullptr};
    for( int i = 0; i < len; i++){
        newItem = loadedGame->getItemByName(token.at(i));
        loadedGame->deck.push(new Card(newItem, ""));
    }

    /// get Discard
    std::getline(ss, token, logD);
    len = std::stoi(token);
    std::getline(ss, token, logD);
    for( int i = 0; i < len; i++){
        newItem = loadedGame->getItemByName(token.at(i));
        loadedGame->discardpile.push(new Card(newItem, ""));
    }

    /// get and setup boardfields



    /// players
    ///
    std::string playerName = "p";
    for(int i = 0; i < playerCount; i++){
        playerName += "ip";
        loadedGame->addPlayer(playerName);
    }

    /// default gameplay
    loadedGame->setUp();

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

