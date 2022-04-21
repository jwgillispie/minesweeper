//
// Created by jordan gillispie on 4/12/22.
//

#include "tiles.h"


tiles::tiles(float x, float y) {
    xpos = x;
    ypos = y;

    revealed.setTexture(textureManager ::getTexture("tile_revealed"));
    hidden.setTexture(textureManager ::getTexture("tile_hidden"));
    flagged.setTexture(textureManager ::getTexture("flag"));

    hidden.setPosition(x, y);
    revealed.setPosition(x,y);
    flagged.setPosition(x,y);
    defaultTile.setPosition(x,y);

    // hide the flag for now
    // hideTile(flagged);

    isMine = false;
    isRevealed = false;
    isFlagged = false;
    debugMode = false;

    // fill the vector nullpointer
    for(int i = 0; i < 8; i++){
        surroundingTiles.push_back(nullptr);
    }

}

void tiles::hideTile(Sprite &toHide) {
    // set the alpha to transparent so we cannot see it
    toHide.setColor(Color(255, 255, 255, 0));
}
void tiles ::showTile(Sprite &toShow) {
    toShow.setColor(Color(255, 255, 255, 255));
}


void tiles::setTile() {

    surroundingMines = 0;

    // if the tile is a number we can figure that out by the vector of surrounding tiles
    // count the number of mines that are near this tile
    for(int i = 0; i < 8; i++){
        if(surroundingTiles.at(i) != nullptr && surroundingTiles.at(i)->isMine )
            surroundingMines++;
    }
    // if its a mine then set the default to a mine  image
    if(isMine){
        defaultTile.setTexture(textureManager ::getTexture("mine"));
    }
    else{
        // depending on the number of bombs, that what the tile will become
        if(surroundingMines == 1){
            defaultTile.setTexture(textureManager ::getTexture("number_1"));
        }
        // depending on the number of bombs, that what the tile will become
        else if(surroundingMines == 2){
            defaultTile.setTexture(textureManager ::getTexture("number_2"));
        }
        // depending on the number of bombs, that what the tile will become
        else if(surroundingMines == 3){
            defaultTile.setTexture(textureManager ::getTexture("number_3"));
        }
        // depending on the number of bombs, that what the tile will become
        else if(surroundingMines == 4){
            defaultTile.setTexture(textureManager ::getTexture("number_4"));
        }
        // depending on the number of bombs, that what the tile will become
        else if(surroundingMines == 5){
            defaultTile.setTexture(textureManager ::getTexture("number_5"));
        }
        // depending on the number of bombs, that what the tile will become
        else if(surroundingMines == 6){
            defaultTile.setTexture(textureManager ::getTexture("number_6"));
        }
        // depending on the number of bombs, that what the tile will become
        else if(surroundingMines == 7){
            defaultTile.setTexture(textureManager ::getTexture("number_7"));
        }
        // depending on the number of bombs, that what the tile will become
        else if(surroundingMines == 8){
            defaultTile.setTexture(textureManager ::getTexture("number_8"));
        }
        // if it is none of those, then we just reveal it
        else{
            defaultTile.setTexture(textureManager ::getTexture("tile_revealed"));
        }
    }

    // now that we have if its a mine or a number, we can hide it under the hidden tile until its clicked later
    // make all the tiles hidden for now
    hideTile(flagged);
    hideTile(defaultTile);
    showTile(hidden);

    isRevealed = false;
    isFlagged = false;
    debugMode = false;

}

// function to flag a tile
// shouldnt be flagged if its already revealed or if its alr flagged
// if it is flagged, that neans we alr clicked on it, so we should set it to false and hide it

// if it isnt flagged then we should set it to true and show it
bool tiles :: flagTile(){
    if(!isRevealed){

        if(isFlagged){
            // set to true and then ,make it show
            isFlagged = false;
            flagged.setColor(Color(255, 255, 255, 0));
        }
        // if its already flagged, we already clicked on it before
        else{
            isFlagged = true;
            flagged.setColor(Color(255, 255, 255, 250));
        }
    }
    return isFlagged;
}
// function to reveal a tile
// make sure it isntn flagged or revealed already
// revelaed should be set to true after we click, and we should bring the tile with an either a number or empty up to the top
// if there are no surrounding mines and there isnt a mine at the current tile then we keep revealing
// keep revealing inside of the neighboring tiles
// if we reach a mine, it will already be revelaed, so we can return true for the mine
bool tiles::revealTiles(int &recursor) {

    // if it isnt flagged or revealed already
    if (!isRevealed && !isFlagged){
            // make the tile revealed and hide the hidden tile
            isRevealed = true;
            recursor++;
            hideTile(hidden);
            showTile(defaultTile);
            if (surroundingMines == 0 && !isMine)
            {
                for (int i = 0; i < 8; i++)
                {
                    if ( surroundingTiles[i] != nullptr && !(surroundingTiles[i]->isMine )){
                        surroundingTiles[i]->revealTiles(recursor);
                        showTile(defaultTile);
                    }
                }
            }
    }
    return isMine;
}

void tiles :: draw(RenderWindow &gameWindow) {
    gameWindow.draw(revealed);
    gameWindow.draw(hidden);
    gameWindow.draw(flagged);
    gameWindow.draw(defaultTile);

}

