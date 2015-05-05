#ifndef STRINGS_H
#define STRINGS_H
#include <string>

namespace labyrinth {

const std::string welcome = {
"********************************************************************************\n"
"******************************   LABYRINTH   ***********************************\n"
"********************************************************************************\n"},

strPlayerNumber = "Player #",
strRound = "Round: ",
strTurn = "'s turn!.",
strQuest = "Quest: ",
strAnyKey = "Press ANY KEY to start new game.",
strBoardSize ="Please, select game board size:",
strBoardSizeRange = "Eneter odd number in range from 5 to 11.",
strInvalidNumber = "Invalid number, press Q to Quit, or ANY KEY to try again",
strItemsNumber = "Select number of items:\nsmall: 12 or large: 24",
strRotateNumber = "How many times do you wanna rotate free field for:",
strShiftMode = "Select shift mode:\nr - rows shift\nc - columns shift\nother - skip",
strShiftChoosePre = "Which (even) ",
strShiftChoosePost = " do you chose to shift:",
strSelectDirection = "Select shift direction: ",
strChooseName = "Choose your name:",
strUniqueName = "Player name has to be unique.",
strSelectPlayerNum = "Select number of players:\n2, 3 or 4",
strNumOORange = "Number out of range.",
strTryAgain  = " number, try again",
strFreeField = "Free boardfield:";


const std::string wrongDirection =  "can't move in choosen direction";

const char* const expWrongSize = "Wrong board size. Please, select size in range from 5 to 11.";
const char* const expWrongEvenSize = "Wrong board size. Board size oughts to be odd number.";

/// log strings:
const char logD = ';';
const std::string logEndOfRound = "###";

}

#endif // STRINGS_H
