//
// Created by jordan gillispie on 4/12/22.
//

#ifndef PROJECT_MINESWEEPER_TILES_H
#define PROJECT_MINESWEEPER_TILES_H
#include "textureManager.h"
#include "board.h"
#include <SFML/Graphics.hpp>
#include <string>


/***
 == attributes ==

    this will be used to make the board.. each tile is an element accessible by the board class
    the tiles have an (x,y) position, can be flagged, hidden, revealed, a mine, can be indebug mode
    maybe have a permanent position for the menu-- debug/tests, flagcounter,
    each tile has a different number of neighboring tiles, and a number of mines around it
        - max is 8.. in the center of 8 mines
        - this can be found out by the 'isMine' attribute of surrounding tiles
    use the color aspect of a sprite to hide and show sprites
        - make it invisible if the condition is false, or make it show to the top if its true

   use the hide or show to change when a tile is double clicked
   every tile can be either hidden, revealed, or a flag
   not every tile will have the same number or will be a mine at the start

== behaviors == much of the behaviors are dependent on te attributes

   - create a tile with (x,y) position, set everything to false to start
   - create the neighboring mines
   - hide/show tiles based on conditions
   - set/ clear a flag -- really just hiding and showing
   - hide/show the mines when we click on the debug button
   - reveal a tile
        - it cant be flagged if u want to reveal it
        - surrounding tiles should have 0 mines in their surrounding tiles
            - keep track of surrounding mines
         - keep track of boolean isMine
        - if it has a mine then stop revealing
        - recursion functions should have termination conditions
            If the number of adjacent mines is 0,
            reveal any neighboring tiles as well (as long as they aren’t mines) In revealing those,
            do the same sort of check for any neighbors to that tile... (sounds a bit like recursion here!)
        - each tile (sprites in the tile) should be drawn after set

 ***/
struct tiles {

    // x, y position for the sprites
    float xpos, ypos;

    // conditions of the tiles
    bool isMine, isRevealed, isFlagged, debugMode;

    // sprites for each tile type
    Sprite hidden;
    Sprite revealed;
    Sprite flagged;
    Sprite defaultTile;

    // has a vector of neighboring tiles
    vector<tiles*> surroundingTiles;
    // bomb count for neighboring tiles
    int surroundingMines;

    // construct a tile object for each of th tiles in the board
    tiles(float x, float y);

    // function to hide/show tiles when appropriate
    void hideTile(Sprite &toHide);
    void showTile(Sprite &toShow);

    // tiles can be updated/ changed based on the board
    // also accounting for surrounding tiles
    void setTile();

    // hide/show flag when its clicked
    bool flagTile();

    // function to show each of the tiles that have mines
    // lets u go back and forth without changing whether its a mine or not

    // function to reveal tiles
    // return the state of the bomb to see if we should end the game
    bool revealTiles(int &recursor);

    // draw the tiles (sprites in the tiles)
    // draw them in the same window as the board
    void draw(RenderWindow &gameWindow);


};



#endif //PROJECT_MINESWEEPER_TILES_H
