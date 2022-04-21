//
// Created by jordan gillispie on 4/12/22.
//

#ifndef PROJECT_MINESWEEPER_TEXTUREMANAGER_H
#define PROJECT_MINESWEEPER_TEXTUREMANAGER_H
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using namespace std;
using namespace sf;

/***
  This class is going to load all of our textures so we can access them in other files as sprites
  They will be stored in a map and we will have functions that return them by address
  Lets say we want to create the board using this... we can create x amount of tiles (sprites) in the board class
***/

class textureManager {
    // create the map that will store the textures
    static unordered_map<string, sf:: Texture> textures;
public:
    // function to load the file and modify the path
    static void loadTexture(string fileName);
    // function to return the texture from the map, it can be used to build sprites
    static sf::Texture& getTexture(string textureName);
    // function to clear the texture objects
    static void Clear();
};


#endif //PROJECT_MINESWEEPER_TEXTUREMANAGER_H
