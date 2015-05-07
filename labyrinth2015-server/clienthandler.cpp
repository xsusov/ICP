/**
 * @project LABYRINTH2015
 * ICP project
 * @class ClientHandler
 * @author xsusov01
 * @email  xsusov01@stud.fit.vutbr.cz
 * @author xbandz00
 * @email  xbandz00@stud.fit.vutbr.cz
 * @file clienthandler.cpp
 * @date 2015/05/10
 * @brief class for recieving player's input (from cin in CLI mode)
*/
#include "clienthandler.h"

using namespace labyrinth;

/**
 * @brief ClientHandler::ClientHandler constructor
 */
ClientHandler::ClientHandler()
    : userInput{""}
{
}

/**
 * @brief ClientHandler::startNewGame
 * @return player keypress for accepting starting labyrinth
 */
bool ClientHandler::startNewGame()
{
    std::cout << strAnyKey << std::endl;
    return getchar();
}

/**
 * @brief ClientHandler::mainMenu
 *        displays MainMenu and let player select from options
 * @return player's option
 */
int ClientHandler::mainMenu()
{
    int option;

    std::cout << strMenuNew << std::endl
              << strMenuLoad << std::endl
              << strMenuCredits << std::endl
              << strMenuExit << std::endl;

    std::cin.clear();
    std::cin >> option;
    return option;
}


/**
 * @brief ClientHandler::getSize get size of board from player and checks wheter is good
 * @return size for GameBoard of new Game (5-11)
 */
int ClientHandler::getSize()
{
    std::cout << strBoardSize << std::endl << strBoardSizeRange << std::endl;
    int size ;
    std::cin.clear();
    fflush(stdin);

    while(1){
        std::cin >> userInput;
        std::stringstream numberStream(userInput);

        if( !(numberStream >> size) ){
            std::cout << strInvalidNumber << std::endl;
            char anykey;
            std::cin >> anykey;
            if( anykey == 'q' || anykey == 'Q' ){
                return -1;
            }
            std::cout << strBoardSize << std::endl << strBoardSizeRange << std::endl;
        }
        else if( size < labyrinth::boardMinSize || size > labyrinth::boardMaxSize ){
            std::cout << expWrongSize << std::endl; /// size not in range 5-11
        }
        else if( !(size%2) ){
            std::cout << expWrongEvenSize << std::endl; /// size must be odd number
        }
        else{
            break;
        }
    }

    return size;
}

/**
 * @brief ClientHandler::getItemCount get number of items from player and checks wheter is good
 * @return number of items for new Game (12 or 24)
 */
int ClientHandler::getItemCount()
{
    int count;
    std::cout << strItemsNumber << std::endl;
    std::cin >> userInput;
    std::stringstream numberStream(userInput);
    if( !(numberStream >> count)){
        std::cout << strInvalidNumber;
        char anykey;
        std::cin >> anykey;
        if( anykey == 'q' || anykey == 'Q' ){
            return -1;
        }
        else{
            return getItemCount();
        }
    }

    if( !(count == itemsSmall || count == itemsLarge )){
        return getItemCount();
    }

    return count;
}

/**
 * @brief ClientHandler::getRotate
 * @return number of times for rotating field
 */
int ClientHandler::getRotate()
{
    int rotate;
    std::cout << strRotateNumber << std::endl;
    std::cin >> userInput;
    std::stringstream numberStream(userInput);
    if( !(numberStream >> rotate)){
        std::cout << strInvalidNumber;
        return getRotate();
    }
    return rotate;
}

/**
 * @brief ClientHandler::getShiftMode
 * @return mode for shifting - row or column
 */
char ClientHandler::getShiftMode()
{
    char mode;
    std::cout << strShiftMode << std::endl;
    std::cin >> mode;
    return mode;
}

/**
 * @brief ClientHandler::getShiftNum
 * @param size - size of GameBoard for checking range
 * @param mode - wheter row or column is gonna be shifted
 * @return number of row/column which will be shifted
 */
int ClientHandler::getShiftNum(const int size, char mode)
{
    int num;
    std::cout << strShiftChoosePre << getShiftStr(mode) << strShiftChoosePost << std::endl;
    std::cout << 2 << "-" << size - 1 << std::endl;
    std::cin >> userInput;
    std::stringstream numberStream(userInput);
    if( !(numberStream >> num)){
        std::cout << "wrong " << getShiftStr(mode) << strTryAgain << std::endl;
        return getShiftNum(size, mode);
    }
    if( num < 1 || num > size || num % 2){
        std::cout << "wrong " << getShiftStr(mode) << strTryAgain << std::endl;
        return getShiftNum(size, mode);
    }

    return num - 1;
}

/**
 * @brief ClientHandler::getShiftDirection
 * @param rowMode - shift row or column
 * @return direction (north/east/south/west) for shifting
 */
int ClientHandler::getShiftDirection(bool rowMode)
{
    int direction;
    std::cout << strSelectDirection << std::endl
              << "0 - " << (rowMode ? "right" : "up") << std::endl
              << "1 - " << (rowMode ? "left" : "down") << std::endl;
    std::cin >> direction;

    direction *= 2;
    if( rowMode )
        direction++;

    return direction;
}

/**
 * @brief ClientHandler::getPlayerCount get number of players from player and checks wheter is good
 * @return number of players for new Game (2-4)
 */
int ClientHandler::getPlayerCount()
{
    int count;
    std::cout << strSelectPlayerNum << std::endl;
    std::cin >> userInput;
    std::stringstream numberStream(userInput);
    if( !(numberStream >> count)){
        std::cout << strInvalidNumber;
        char anykey;
        std::cin >> anykey;
        if( anykey == 'q' || anykey == 'Q' ){
            return -1;
        }
        else{
            return getPlayerCount();
        }
    }

    if( count < minPlayers || count > maxPlayers) {
        std::cout << strNumOORange << std::endl;
        return getPlayerCount();
    }
   std::getline(std::cin, userInput);
   return count;
}

/**
 * @brief ClientHandler::getPlayerName gets name for new player from player and checks it against players already in game
 * @param players - vector of players already in game
 * @return name for new Player
 */
std::string ClientHandler::getPlayerName(const std::vector<Player *> &players)
{
    std::string name = "";
    std::cout << strChooseName << std::endl;
    std::getline(std::cin, name);
    if(name.empty())
        return getPlayerName(players);

    for (Player * player : players){
        if (player->getName() == name){
            std::cout << strUniqueName << std::endl;
            return getPlayerName(players);
        }
    }
    return name;
}

/**
 * @brief ClientHandler::getMoveDirection
 *        gets direction from player for next move
 *        player also can save game instead of moving or undo game changes to his last turn
 * @return players option to move in one direction or to save/undo game
 */
int ClientHandler::getMoveDirection()
{
    std::string direction;
    std::cout << strSelectMoveDirection << std::endl << strSave << std::endl;


    if(!std::cin){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }

    std::cin >> direction;

    if (direction == "W" || direction == "w") return north;
    else if (direction == "S" || direction == "s") return south;
    else if (direction == "A" || direction == "a") return west;
    else if (direction == "D" || direction == "d") return east;
    else if (direction == "E" || direction == "e" || direction == "0" ) return stop;
    else if (direction == "SAVE" || direction == "save" ) return saveN;
    else if (direction == "UNDO" || direction == "undo" ) return undoN;

    std::cout << strInvalidMove << std::endl;
    return getMoveDirection();
}

/**
 * @brief ClientHandler::getGame displays MainMenu to player and let him select option
 *        wheter start new game or load savegame of inserted name or let him exit game completly (resources are cleaned properly)
 * @return name of new Game - empty=new nonempty=savegame
 */
std::string ClientHandler::getGame()
{
    std::string savegame {newGame};
    switch( mainMenu() ){
        case 1:
            return newGame;
        case 2:
            std::cout << strLoadGame << std::endl;
            std::cin >> savegame;
            return savegame;
        case 3:
            std::cout << strCredits << std::endl;
            return getGame();
        case 4:
            exit(0);
    }

    return newGame;
}

/**
 * @brief ClientHandler::getSaveGameName gets name of savegame file for new save from player
 * @return name for new savegame
 */
std::string ClientHandler::getSaveGameName()
{
    std::string savegame {newGame};
    std::cout << strSaveGame << std::endl;
    std::cin >> savegame;
    return savegame;
}

/**
 * @brief ClientHandler::getNewGame gets parameters of new Game and players, creates it and add player to it
 * @return new created Game instance or nullptr for wrong parameters
 */
Game *ClientHandler::getNewGame()
{
    Game *newGame {nullptr};
    int size {0};
    int itemCount {0};
    int playerCount {0};

    size = getSize();
    if(size < 0){
        return nullptr;
    }
    itemCount = getItemCount();
    if(itemCount < 0){
        return nullptr;
    }
    playerCount = getPlayerCount();
    if(playerCount < 0){
        return nullptr;
    }

    newGame = new Game(size, playerCount, itemCount);

    for(int i = 0; i < playerCount; i++){
        newGame->addPlayer(getPlayerName(newGame->getPlayers()));
    }

    return newGame;
}

/**
 * @brief ClientHandler::getShift gets information about shifting from player and saves them to referenced variables
 * @param size - size of board for checking range
 * @param shiftNum - var for saving number of row/column
 * @param direction of shifting
 * @return validity of user input
 */
int ClientHandler::getShift(const int size, int &shiftNum, int &direction)
{
    char mode = getShiftMode();
    if(!( mode == 'r' || mode == 'R' || mode == 'c' || mode == 'C' ))
        return 0;
    shiftNum = getShiftNum(size, mode);
    direction = getShiftDirection(mode == row);
    return 1;
}
