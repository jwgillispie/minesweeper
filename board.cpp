//
// Created by jordan gillispie on 4/12/22.
//

#include "board.h"
#include "tiles.h"
#include "randomNumber.h"


// board constructor
board ::board() {
    gameWon = false;

}

// when im parsing i am going to create a new dimensions object from the config file
// i will use that to send to the board to create/draw it
void board :: parseCFG(const string &fileName) {

    fstream tempFile(fileName, ios_base::in);

    // as long as its open
    if (tempFile.is_open()) {

        string currentLine;
        getline(tempFile, currentLine);
        int w = stoi(currentLine);
        width = w * 32 ;

        getline(tempFile, currentLine);
        int h = stoi(currentLine);
        height = (h * 32) + 100;

        getline(tempFile, currentLine);
        mines = stoi(currentLine);
        tileCount = w * h;
        flagCount = mines;

        tilesLeft = tileCount - mines;
    }
}

void board::setBoard() {
//    parseCFG("./boards/config.cfg"); // now the board has dimensions

    float xpos = 0;
    float ypos = 0;

    int bottomx = width / 2;
    int bottomy = height - 100;

    int numCols = width / 32;  // number of columns
    int numRows = height - 100;
    numRows /= 32;

    tileCount = numRows * numCols;// number of rows

    // now set its position, we will use the gameboard to get the numbers that we need
    // this loop will take care of all of the variable tiles

    // go through each row ( 0 -16)
    for (int i = 0; i < numRows ; i++) {
        xpos = 0;
        // go through each column and place a tile
        for (int j = 0; j < numCols ; j++) {

            tiles newTile = tiles(xpos, ypos);
            allTiles.push_back(newTile);
            xpos += 32;
        }
        ypos += 32;
    }

    // the smiley face will be in the center

    smileyFace.setTexture(textureManager ::getTexture("face_happy"));
    smileyFace.setPosition(bottomx, bottomy);

    // set the position of the debugger
    // two columns to the right of the smiley
    // bottomx is 2 tiles wide.. so move this over by 6 tiles for 4 total
    bottomx += 128;
    debugger.setTexture(textureManager ::getTexture("debug"));
    debugger.setPosition(bottomx + 16, bottomy);

    testOne.setTexture(textureManager ::getTexture("test_1"));
    bottomx += 64;
    testOne.setPosition(bottomx + 16, bottomy);

    testTwo.setTexture(textureManager ::getTexture("test_2"));
    bottomx += 64;
    testTwo.setPosition(bottomx + 16, bottomy);

    testThree.setTexture(textureManager ::getTexture("test_3"));
    bottomx += 64;
    testThree.setPosition(bottomx + 16, bottomy);

    // set the minecounter
    // we can calculate these later
    negative.setTexture(textureManager ::getTexture("digits"));
    negative.setPosition(3, bottomy);
    zerothDigit.setTexture(textureManager ::getTexture("digits"));
    zerothDigit.setPosition(21, bottomy);
    firstDigit.setTexture(textureManager ::getTexture("digits"));
    firstDigit.setPosition(42, bottomy);
    secondDigit.setTexture(textureManager ::getTexture("digits"));
    secondDigit.setPosition(64, bottomy);

    tilesLeft = tileCount - mines;
    debugMode = false;
    gameWon = false;

}
void board :: randomizeMines(){

    int count = mines;
    int tiles= tileCount;

    while (count > 0){

        // create a random number between 0 and totaltiles
        int random = randomNumber::numberInt(0, tiles);

        // if the random number is already chosen, get a new one
        for (int i = 0; i < tileCount; i++){
            // if the random number is already a mine
            if(allTiles[random].isMine){
                // another random number
                random = randomNumber::numberInt(0, tiles);
            }
        }
        allTiles[random].isMine = true;
        count--;
    }
    testingMode = false;
};
/***
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
            - the one to the right, the one below, and the one diagonal
            - lets say the one above the currrent tile is surroundingtiles[0], and go clockwise
            -- so at the top left corner
            -- we have 25 tiles per row
                        0       1           2                   3                           4                   (567)
                - [ nullptr, nullptr, -->tiles[1], -->tiles[length of a row + 2], -->[length of a row + 1], rest are null]
       - so we can use the length of a row/ column to decide where to place the pointer tiles vectors

       doing this straight up wont let us account for when we enter the next row  and there is overlap..
            if we are at 50

***/

void board::calculateTileNumber() {
    // get the size of a row and the size of a column
    int rowLength = (int)(width / 32);
    int colSize = (height - 100) / 32;

    // go through all of the tiles in our board tiles vector
    // i need to make sure that  i am not in the corners
    // i need to make sure that i am not on the edges
    // otherwise i will unveal tiles that are in the following/ previous rows
    // shoulda done a 2d vec lol
    for(int i = 0; i < tileCount; i++) {

        // when i am in a corner, i will only have 3 pointers
        // very first tile -- 2, 3, 4
        if (i == 0) {
            try {
                allTiles[i].surroundingTiles.at(2) = &allTiles.at(i + 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(2) = nullptr;

            }
            try {
                allTiles[i].surroundingTiles.at(3) = &allTiles.at((i + rowLength) + 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(3) = nullptr;

            }
            try {
                allTiles[i].surroundingTiles.at(4) = &allTiles.at(i + rowLength);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(4) = nullptr;

            }

        }
            // if i am in the top right corner then the i will be equal to the length of the row
            // i nwill have 4, 5, 6
        else if (i == rowLength - 1) {
            try {
                allTiles[i].surroundingTiles.at(4) = &allTiles.at(i + rowLength);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(4) = nullptr;

            }
            try {
                allTiles[i].surroundingTiles.at(5) = &allTiles.at((i + rowLength) - 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(5) = nullptr;

            }
            try {
                allTiles[i].surroundingTiles.at(6) = &allTiles.at(i - 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(6) = nullptr;

            }
        }
            // if i am in the bottom left corner then i am at the max number of rows, and the xpos = 0
            // 0 , 1, 2
        else if (i == tileCount - rowLength) {
            try {
                allTiles[i].surroundingTiles.at(0) = &allTiles.at(i - rowLength);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(0) = nullptr;
            }

            try {
                allTiles[i].surroundingTiles.at(1) = &allTiles.at((i - rowLength) + 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(1) = nullptr;

            }
            try {
                allTiles[i].surroundingTiles.at(2) = &allTiles.at(i + 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(2) = nullptr;

            }

        }
        // bottom right corner is == the max # of tiles
        // then i need 0 , 7 , 6
        else if (i == tileCount) {
            try {
                allTiles[i].surroundingTiles.at(0) = &allTiles.at(i - rowLength);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(0) = nullptr;
            }
            try {
                allTiles[i].surroundingTiles.at(6) = &allTiles.at(i - 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(6) = nullptr;

            }
            try {
                allTiles[i].surroundingTiles.at(7) = &allTiles.at((i - rowLength) - 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(7) = nullptr;
            }
            allTiles[i].setTile();
        }
        // so now if im in the first row
        // the xpos is gonna b 0 and i wont be at position zero or tile count - row length
        else if (allTiles[i].xpos == 0){
            try {
                allTiles[i].surroundingTiles.at(0) = &allTiles.at(i - rowLength);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(0) = nullptr;
            }

            try {
                allTiles[i].surroundingTiles.at(1) = &allTiles.at((i - rowLength) + 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(1) = nullptr;

            }
            try {
                allTiles[i].surroundingTiles.at(2) = &allTiles.at(i + 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(2) = nullptr;

            }
            try {
                allTiles[i].surroundingTiles.at(3) = &allTiles.at((i + rowLength) + 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(3) = nullptr;

            }
            try {
                allTiles[i].surroundingTiles.at(4) = &allTiles.at(i + rowLength);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(4) = nullptr;
            }

        }
        // on the right side
        // then i am
        else if ((allTiles[i].xpos / 32) == rowLength - 1){
            try {
                allTiles[i].surroundingTiles.at(4) = &allTiles.at(i + rowLength);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(4) = nullptr;

            }
            try {
                allTiles[i].surroundingTiles.at(5) = &allTiles.at((i + rowLength) - 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(5) = nullptr;

            }
            try {
                allTiles[i].surroundingTiles.at(6) = &allTiles.at(i - 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(6) = nullptr;
            }
            try {
                allTiles[i].surroundingTiles.at(7) = &allTiles.at((i - rowLength) - 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(7) = nullptr;
            }
        }
        // if i am on the top row
        else if (i < rowLength){
            try {
                allTiles[i].surroundingTiles.at(2) = &allTiles.at(i + 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(2) = nullptr;

            }
            try {
                allTiles[i].surroundingTiles.at(3) = &allTiles.at((i + rowLength) + 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(3) = nullptr;

            }
            try {
                allTiles[i].surroundingTiles.at(4) = &allTiles.at(i + rowLength);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(4) = nullptr;

            }
            try {
                allTiles[i].surroundingTiles.at(5) = &allTiles.at((i + rowLength) - 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(5) = nullptr;

            }
            try {
                allTiles[i].surroundingTiles.at(6) = &allTiles.at(i - 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(6) = nullptr;
            }

        }
        else {
            try {
                allTiles[i].surroundingTiles.at(0) = &allTiles.at(i - rowLength);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(0) = nullptr;
            }

            try {
                allTiles[i].surroundingTiles.at(1) = &allTiles.at((i - rowLength) + 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(1) = nullptr;

            }
            try {
                allTiles[i].surroundingTiles.at(2) = &allTiles.at(i + 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(2) = nullptr;

            }
            try {
                allTiles[i].surroundingTiles.at(3) = &allTiles.at((i + rowLength) + 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(3) = nullptr;

            }
            try {
                allTiles[i].surroundingTiles.at(4) = &allTiles.at(i + rowLength);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(4) = nullptr;

            }
            try {
                allTiles[i].surroundingTiles.at(5) = &allTiles.at((i + rowLength) - 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(5) = nullptr;

            }
            try {
                allTiles[i].surroundingTiles.at(6) = &allTiles.at(i - 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(6) = nullptr;

            }
            try {
                allTiles[i].surroundingTiles.at(7) = &allTiles.at((i - rowLength) - 1);
            }
            catch (const out_of_range &out_of_range) {
                allTiles[i].surroundingTiles.at(7) = nullptr;
            }
        }
        allTiles[i].setTile();
    }
}

// function to calculate the flags we place and the initial mines
// this is based on the flagcount
// we can calculate the different places using modulo
// this will be incremented or decremented when we right click
// so we can just take the number and calculate it here, without worrying about what it is
void board::displayFlagCount() {

    // get the flagcount
    int getCount = flagCount; // 451

    // calculate the ints for each digit
    int first = 0;
    int second = 0;
    int third = 0;

    // the first digit is gonna be the  count divided by 100
    // if its negative then we dont need to calculate it, we can just place a negative sign there
    if (getCount > 0) {
        first = getCount / 100; // 451 / 100 = 4

        if (getCount > 99) {
            int copy = getCount - (first *100);  // 451 - 400 = 51

            second = copy / 10; // 51 / 10 = 5
            third = copy % 10; // 51 % 10 = 1
        }
        else{
            second = getCount / 10; // 99 / 10 = 9
            third = getCount % 10; // 99  % 10 = 9
        }
    }
    // if its negative then the first position will be negative
    // - 327
    else if(getCount < 0){
        int makePos = getCount * -1; // now 327
        // get negative to positive

        first = makePos / 100; // 327 / 100 = 3

        if (makePos > 99) {
            int copy = makePos - (first *100);  // 327 - 300 = 27

            second = copy / 10; // 27 / 10 = 2
            third = copy % 10; // 27 % 10 = 7
        }
        else{
            second = makePos / 10; // 1 / 10 = 0
            third = makePos % 10; // 1  % 10 = 9
        }

    }
//    // if its == to zero then set all to 0
//    else {
//        first = 0;
//        second = 0;
//        third = 0;
//    }

    // if the flag count is below 0, then it will be the negative sprite in the zeroth digit
    // if the flag count is == 0, then it will be zero in that position,
    // otherwise it will be the first digit of the flag count
    if(getCount < 0){
        // set the negative sign
        negative.setTextureRect(Rect<int>(210, 0, 21, 32));
        zerothDigit.setTextureRect(Rect<int> ((21 * first), 0 , 21, 32));
        firstDigit.setTextureRect(Rect<int> ((21 * second), 0 , 21, 32));
        secondDigit.setTextureRect(Rect<int> ((21 * third), 0 , 21, 32));
    }
    else{
        zerothDigit.setTextureRect(Rect<int> ((21 * first), 0 , 21, 32));
        firstDigit.setTextureRect(Rect<int> ((21 * second), 0 , 21, 32));
        secondDigit.setTextureRect(Rect<int> ((21 * third), 0 , 21, 32));

    }
}

// update the smiley face
// if the game is over, then enter
// the player has pressed on a mine, then we will change the face to the sad one
    // the game is lost
// if all of the possibel revealed tiles are revealed then we can change it to the cool face
string board::checkGameStatus() {
    // check to see if we lost
    if(gameLost){
        // change to the sad face
        smileyFace.setTexture(textureManager ::getTexture("face_lose"));
        return "Game lost";
    }
    else if(gameWon){
        smileyFace.setTexture(textureManager ::getTexture("face_win"));
        return "Game won";
    }
    // if the game isnt over then return the regular face
    else{
        smileyFace.setTexture(textureManager::getTexture("face_happy"));
    }
    return "mememe";
}

// debug mode on
void board :: turnOnDebugMode(){
    // if its true that means we already turned it on
    if(debugMode){
        for (int i = 0; i < tileCount; i ++){
            // if it is a mine and the debug mode is true, then turn off the debig mode
            if(allTiles[i].isMine && allTiles[i].debugMode){
                allTiles[i].debugMode = false;
            }
        }
        debugMode = false;

    }
    // other wise we just clicked and now we need to turn on debug mode for all the tiles
    // all the tiles that have mines are now set to debug mode on
    // if the boards debug mode is on then we need to show the mines
    else{
        debugMode = true;
        // go through all the tiles, if there is a mine, then turn on the tiles debugmode on too
        for (int i = 0; i < tileCount; i ++){
            // if it is a mine and the debug mode is false, then turn on the debig mode
            if(allTiles[i].isMine && !allTiles[i].debugMode){
                allTiles[i].debugMode = true;

            }
        }
    }
}
// function to reset the board
void board::reset(board &resetter) {
    resetter.allTiles.erase(allTiles.begin(), allTiles.end());

    resetter.parseCFG("./boards/config.cfg");
    resetter.setBoard();
    resetter.displayFlagCount();
    resetter.randomizeMines();
    resetter.calculateTileNumber();

}
// function to get the testin board one
// parse the first board file
// if testing mode is false set it to true
void board::changeTestingMode() {

    if(!testingMode){
        testingMode = true;

    }
    else{
        testingMode = false;
    }
}

// function to parse any board
// store all of the info in a vector of ints
// set tiles for the number of those ints
// keep track of the boards columns and rows
// use that to set the board
void board::parseTestFile(string &fileName) {


    fstream tempFile(fileName, ios_base :: in);

    // as long as the file is open, get each line and store it
    char currentNum;
    if(fileName == "./boards/testboard1.brd" ){
        testVector1.clear();
        testVector2.clear();
        testVector3.clear();
        allTiles.clear();
        while(!tempFile.eof()){
            tempFile >> currentNum;
            testVector1.push_back((currentNum));
        }
        cout << "test vector size : " << testVector1.size() << endl;
        tempFile.close();

    }
    else if (fileName == "./boards/testboard2.brd" ){
        allTiles.clear();

        while(!tempFile.eof()){
            tempFile >> currentNum;
            testVector2.push_back((currentNum));
        }
        cout << "test vector size : " << testVector2.size() << endl;
        tempFile.close();

    }
    else if (fileName == "./boards/testboard3.brd" ){
        allTiles.clear();

        while(!tempFile.eof()){
            tempFile >> currentNum;
            testVector3.push_back((currentNum));
        }
        cout << "test vector size : " << testVector3.size() << endl;
        tempFile.close();
    }
}

//
// function to draw
void board::drawBoard(RenderWindow &gameWindow) {

    // use the tile class to draw each sprite since they have various sprites
    for(int i = 0; i < tileCount; i++){
        allTiles[i].draw(gameWindow);
//        gameWindow.draw(allTiles[i].revealed);
//        gameWindow.draw(allTiles[i].hidden);
//        gameWindow.draw(allTiles[i].flagged);
//        gameWindow.draw(allTiles[i].defaultTile);

        if(allTiles[i].debugMode){
            Sprite mine(textureManager ::getTexture("mine"));
            mine.setPosition(allTiles[i].xpos, allTiles[i].ypos);
            gameWindow.draw(mine);
        }
        if(checkGameStatus() == "Game lost" && allTiles[i].isMine){
            Sprite backDrop(textureManager ::getTexture("tile_revealed"));
            backDrop.setPosition(allTiles[i].xpos, allTiles[i].ypos);
            gameWindow.draw(backDrop);

            Sprite mine(textureManager ::getTexture("mine"));
            mine.setPosition(allTiles[i].xpos, allTiles[i].ypos);
            gameWindow.draw(mine);
        }


    }

    gameWindow.draw(smileyFace);
    gameWindow.draw(debugger);
    gameWindow.draw(testOne);
    gameWindow.draw(testTwo);
    gameWindow.draw(testThree);

    // draw the count[er
    if(flagCount < 0){
        gameWindow.draw(negative);
        gameWindow.draw(zerothDigit);
        gameWindow.draw(firstDigit);
        gameWindow.draw(secondDigit);
    }else{
        gameWindow.draw(zerothDigit);
        gameWindow.draw(firstDigit);
        gameWindow.draw(secondDigit);

    }
    for(int i =0; i < tileCount; i++){
        if(checkGameStatus() == "Game won" && allTiles[i].isMine){
            // mark all the tiles with mines with flags
            Sprite flagger(textureManager ::getTexture("flag"));
            Sprite background(textureManager::getTexture(("tile_revealed")));
            flagger.setPosition(allTiles[i].xpos, allTiles[i].ypos);
            gameWindow.draw(background);
            gameWindow.draw(flagger);

            int bottomy = height - 100;
            Sprite winOne(textureManager ::getTexture("digits"));
            Sprite winTwo(textureManager ::getTexture("digits"));
            Sprite winThree(textureManager ::getTexture("digits"));

            winOne.setPosition(21, bottomy);
            winTwo.setPosition(42, bottomy);
            winThree.setPosition(64, bottomy);
            winOne.setTextureRect(IntRect(0, 0, 21, 32));
            winTwo.setTextureRect(IntRect(0, 0, 21, 32));

            winThree.setTextureRect(IntRect(0, 0, 21, 32));

            gameWindow.draw(winOne);
            gameWindow.draw(winTwo);
            gameWindow.draw(winThree);

        }
    }
}


