//
// Created by jordan gillispie on 4/12/22.
//
#include "board.h"
#include "textureManager.h"
#include "tiles.h"
#include <cstdlib>
#include <random>
using namespace std;

void automateTesting(board &naked, board &main, string &fileName) {

    if(fileName == "./boards/testboard1.brd") {
        naked.flagCount = 0;
        naked.mines = 0;
        naked.testVector1.clear();
        naked.width = main.width;
        naked.height = main.height;

        naked.parseTestFile(fileName);

        naked.setBoard();
        // gameBoard.mines = 0;

        for (int i = 0; i < naked.testVector1.size(); i++) {
            if (naked.testVector1[i] == '1') {
                naked.allTiles[i].isMine = true;
                naked.flagCount++;
                naked.mines++;
            }
        }
    }
    else if(fileName == "./boards/testboard2.brd") {
        naked.flagCount = 0;
        naked.mines = 0;
        naked.testVector2.clear();
        naked.width = main.width;
        naked.height = main.height;

        naked.parseTestFile(fileName);

        naked.setBoard();
        // gameBoard.mines = 0;

        for (int i = 0; i < naked.testVector2.size(); i++) {
            if (naked.testVector2[i] == '1') {
                naked.allTiles[i].isMine = true;
                naked. mines++;
                naked.flagCount++;
                naked.mines++;


            }
        }
    }
    else if(fileName == "./boards/testboard3.brd") {
        naked.flagCount = 0;
        naked.mines = 0;
        naked.testVector3.clear();
        naked.width = main.width;
        naked.height = main.height;

        naked.parseTestFile(fileName);

        naked.setBoard();
        // gameBoard.mines = 0;

        for (int i = 0; i < naked.testVector3.size(); i++) {
            if (naked.testVector3[i] == '1') {
                naked.allTiles[i].isMine = true;
                naked.flagCount++;
                naked.mines++;


            }
        }
    }
}

int main() {

    // now my board has its dimensions, lets create a window size using the dimensions object
    board gameBoard;
    board testBoard;

    gameBoard.parseCFG("./boards/config.cfg");
    gameBoard.setBoard();
    gameBoard.displayFlagCount();
    gameBoard.randomizeMines();
    gameBoard.calculateTileNumber();


    sf::RenderWindow window(sf::VideoMode(gameBoard.width, gameBoard.height), "MineSweeper");
    while (window.isOpen()) {
        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // see if a mouse button is pressed
            if (event.type == Event::MouseButtonPressed) {

                // get the position of the click
                auto mousePosInt = Mouse::getPosition(window);
                Vector2f mousePosFloat((float) mousePosInt.x, (float) mousePosInt.y);

                if(event.mouseButton.button == Mouse::Left && !gameBoard.gameOver){

                    // get the position of the mouse
                    auto mousePos = Mouse::getPosition(window);
                    Vector2f mousePosFloatLeft((float) mousePos.x, (float) mousePos.y);

                    // get a vector of all of the rectangles
                    vector<FloatRect> getPosition;
                    getPosition.reserve(gameBoard.tileCount);
                    // add all the rectangle of the board to the vector
                    for(int i = 0; i < gameBoard.tileCount; i++){
                        getPosition.push_back(gameBoard.allTiles[i].revealed.getGlobalBounds());
                    }

                    int count = 0;
                    int recursiveCounter = 0;
                    // go through the rectangle vector to see whre we press
                    for(int i = 0; i < getPosition.size(); i++) {

                        if (getPosition[i].contains(mousePosFloatLeft)) {
                            // if the tile i click is not revealed or flagged, then keep going until its a mine
                            // if we click on a mine return true
                            if (gameBoard.allTiles[i].revealTiles(count)) {
                                // game is over
                                gameBoard.gameOver = true;
                                gameBoard.gameLost = true;


                                // here, the counter will go until it finds a mine
                                if (gameBoard.allTiles[i].isFlagged && gameBoard.allTiles[i].isMine) {
                                    gameBoard.allTiles[i].flagTile();
                                }
                                if (gameBoard.allTiles[i].isMine) {
                                    gameBoard.allTiles[i].revealTiles(recursiveCounter);
                                }
                            }
                        }
                    }
                }
                // if we have a left click that is below the main board
                // then we are clicking on menu items
                if(event.mouseButton.button == Mouse::Left && mousePosInt.y >= gameBoard.height- 100){

                    // get a rectangle for each of the different icons
                    FloatRect smileyFaceButton(gameBoard.smileyFace.getGlobalBounds());
                    FloatRect debuggerButton(gameBoard.debugger.getGlobalBounds());
                    FloatRect testOneButton(gameBoard.testOne.getGlobalBounds());
                    FloatRect testTwoButton(gameBoard.testTwo.getGlobalBounds());
                    FloatRect testThreeButton(gameBoard.testThree.getGlobalBounds());

                    // if we click on the smiley face then we need to clear the board and randomize the mines
                    if(smileyFaceButton.contains(mousePosFloat)){
                        gameBoard.gameOver = false;
                        gameBoard.gameLost = false;
                        gameBoard.reset(gameBoard);

                    }
                    if(debuggerButton.contains(mousePosFloat)){
                        int testCount = 0;
                        // if i click on this button then the debug mode turns on
                        gameBoard.turnOnDebugMode();
                        if(gameBoard.debugMode){
                            for(int i = 0; i < gameBoard.tileCount; i++){
                                if(gameBoard.allTiles[i].debugMode){
                                    testCount++;
                                }
                            }
                        }
                        else{
                            testCount = 0;
                            for(int i = 0; i < gameBoard.tileCount; i++){
                                if(gameBoard.allTiles[i].debugMode){
                                    testCount++;
                                }
                            }
                        };
                    }
                    if(testOneButton.contains(mousePosFloat)){

                        testBoard.flagCount = 0;
                        testBoard.allTiles.clear();
                        gameBoard.changeTestingMode();
                        string board1 = "./boards/testboard1.brd";
                        automateTesting(testBoard, gameBoard, board1);
                        testBoard.calculateTileNumber();
                        testBoard.displayFlagCount();

                    }
                    if(testTwoButton.contains(mousePosFloat)){

                        testBoard.flagCount = 0;
                        testBoard.allTiles.clear();
                        gameBoard.changeTestingMode();
                        string board2 = "./boards/testboard2.brd";
                        automateTesting(testBoard, gameBoard, board2);
                        testBoard.calculateTileNumber();
                        testBoard.displayFlagCount();

                    }
                    if(testThreeButton.contains(mousePosFloat)) {

                        testBoard.flagCount = 0;
                        testBoard.allTiles.clear();
                        gameBoard.changeTestingMode();
                        string board3 = "./boards/testboard3.brd";
                        automateTesting(testBoard, gameBoard, board3);
                        testBoard.calculateTileNumber();
                        testBoard.displayFlagCount();
                    }

                }

                // see if the mouse button is right and the game isnt over then i need to see where i clicked
                if (event.mouseButton.button == Mouse::Right && !gameBoard.gameOver) {

                    // get the position of the mouse
                    auto mousePos = Mouse::getPosition();
                    mousePos = Mouse::getPosition(window);
                    Vector2f mousePosFloatRight((float) mousePos.x, (float) mousePos.y);
                    vector<FloatRect> getPosition;

                    getPosition.reserve(gameBoard.tileCount);
                    for (int i = 0; i < gameBoard.tileCount; i++) {
                        // create a rectangle for each of the tiles
                        getPosition.push_back(gameBoard.allTiles[i].defaultTile.getGlobalBounds());
                    }

                    // now i have a vector containing all of the positions stored by rect of every tile in the board
                    for(int i = 0; i < getPosition.size(); i++){
                        // see where we clicked
                        if(getPosition[i].contains(mousePosFloatRight)) {

                            // if the tile isnt flagged and isnt revealed
                            if (!gameBoard.allTiles[i].isFlagged && !gameBoard.allTiles[i].isRevealed) {
                                // get the flag image and change the count
                                gameBoard.allTiles[i].flagTile();
                                gameBoard.flagCount--;
                                cout << " current flag count " << gameBoard.flagCount;

                            }
                            else if(gameBoard.allTiles[i].isFlagged && !gameBoard.allTiles[i].isRevealed){
                                gameBoard.allTiles[i].flagTile();
                                gameBoard.flagCount++;
                            }
                            gameBoard.displayFlagCount();
                        }
                    }
                }
            }
            int tileCounter = 0;
            for(int i =0; i < gameBoard.tileCount; i++){
                if(gameBoard.allTiles[i].isRevealed){
                    tileCounter++;
                }
            }
            cout << "there are " << tileCounter << " tiles revealed " << endl;
            cout << gameBoard.mines << endl;
            if(tileCounter == (gameBoard.tileCount - gameBoard.mines)){
                gameBoard.gameOver = true;
                gameBoard.gameWon = true;
            }
            gameBoard.checkGameStatus();
        }

        window.clear();

        if(gameBoard.testingMode){
            gameBoard = testBoard;
            gameBoard.drawBoard(window);
        }
        else{
            gameBoard.drawBoard(window);
        }
        window.display();

    }
    return 0;
}
