//
// Created by jordan gillispie on 4/12/22.
//

#include "textureManager.h"

// redeclare the map variable, will be used just the same
unordered_map<string, sf:: Texture> textureManager:: textures;

void textureManager ::loadTexture(string fileName) {
    // standardize the filepath to load, and it will match the map key
    string path = "./images/";
    path += fileName + ".png";
    // now we have our full filepath and we can load the image into the map
    textures[fileName].loadFromFile(path);
}

// now that its loaded we can retrieve it
// the purpose of retrieving is to create a sprite out of the texture
// keep in mind that the textures are stored in a map
sf::Texture& textureManager ::getTexture(string textureName) {

    // iterate through the map and find the texture object we are looking for
    // if it doesnt exist then we can add it to the map
    if(textures.find(textureName) == textures.end()){
        loadTexture(textureName);
    }
    // if it alr exists...or we just created it and added it to the map
    // return it
    return textures[textureName];
}

// clear
void textureManager ::Clear() {
    textures.clear();
}

