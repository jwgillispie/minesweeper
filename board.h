//
// Created by jordan gillispie on 4/12/22.
//

#ifndef PROJECT_MINESWEEPER_BOARD_H
#define PROJECT_MINESWEEPER_BOARD_H
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include "textureManager.h"
#include "tiles.h"

/***

 == attributes ==

 the board will have dimensions, and we can calculate a flagcount and mine count from the config file
     - we can keep track of the number of mines

 the board will have the test/debug buttons under the tiles --> the win/loss faces can be drawn later --> maybe we can hide/show them
    - the test files have all integers, so we can store them maybe in a vector

 we can have sprites for the 3 numbers to keep track of the flag counter
 the board will be made out of  a vector of tile objectd
 the game can be won or lost
    we can keep track of the number of tiles revealed.. if it reached a certain point then the game is won
    if a tile is clicked and isMine is true, then the game is lost

  == behaviors ==
   *** creating a new board object ***
 - we should parse the config file, which which set the board dimensions and give us our mine/flag count
 - we should initialize the tiles which will be defined in another function using the dimensions and setting the menu icons
 - we should randomize the mines which will be in another function as well, that uses a board object's vector of tiles

  parse the test files and store the values
  parse the config file and store

  create a board object from the dimensions of the files
        - setposition/ store all the tiles in the vector
            - position is set based on the file we have
        - randomize the mines in the vector
        - we should have the counter set and respond to the initial flag count
            - have a variable for the flag count
        - set the menu/ debug tiles
  create board objects from the test files

  calculate the number of mines using sprites to display the right number
    - this is based on the flag count
    - can be negative and can be greater than the number of mines

  update the smiley face depending on if the game is won or lost

  function to set the different numbers/ clear image per tile if its pressed
  tiles with less than 8 should have null pointers where the tiles dont exist
    - our tiles are all done one by one ( we have 0 -400)
    - tiles in the corners will have 3 tiles near them
    - tiles on the top and bottom row will have 5, besides the corners
    - tiles on the right will have 5 besides the corners as well
    - all tiles in the middle of the window will have 8

    for all of the tiles, maybe set the surrounding tile vector to all null to start.. or do a try catch
    === lets say we have 400 tiles==
     - loop through all
        - the one at position 0 will have a vector of surrounding tiles
            - the one to the right, the one below, and the one diagona
            - lets say the one above the currrent tile is surroundingtiles[0], and go clockwise
            -- so at the top left corner
            -- we have 25 tiles per row
                        0       1           2                   3                           4                   (567)
                - [ nullptr, nullptr, -->tiles[1], -->tiles[length of a row + 2], -->[length of a row + 1], rest are null]
       - so we can use the length of a row/ column to decide where to place the pointer tiles vectors

***/

struct board {

    board();

    // dimensions attributes
    int width;
    int height;
    int mines;
    int tileCount;
    int flagCount;
    // keep track of the revealed tiles to see if the game is wonm
    int tilesLeft;
    vector<struct tiles> allTiles;
    vector<char> testVector1;
    vector<char> testVector2;
    vector<char> testVector3;

    // game conditions
    bool gameOver;
    bool gameLost;
    bool debugMode;
    // testing mode will help us go back and forth between gameplay and
    bool testingMode;
    bool gameWon;

    // sprites for the counter
    Sprite zerothDigit;
    Sprite firstDigit;
    Sprite secondDigit;
    Sprite negative;
    // sprites for the testng/ debugging
    Sprite smileyFace, debugger, testOne, testTwo, testThree;

    // parse the dimensions -- these will help create the board object
    void parseCFG(const string &fileName);
    void setBoard();
    void randomizeMines();

    // function to calculate and set the mine counter thingy
    void displayFlagCount();

    // function to draw that takes in the window we are working in
    void drawBoard(RenderWindow &gameWindow);

    // debug mode
    void turnOnDebugMode();

    // function to change the smiley face if the board is won or lost
    string checkGameStatus();

    // function to reset the board
    void reset(board &resetter);

    // function to parse and draw the test boards
    void changeTestingMode();

    void parseTestFile(string &fileName);

    void calculateTileNumber();


};


#endif //PROJECT_MINESWEEPER_BOARD_H
