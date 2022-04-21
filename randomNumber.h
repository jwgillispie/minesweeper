//
// Created by jordan gillispie on 4/19/22.
//

#ifndef PROJECT_MINESWEEPER_RANDOMNUMBER_H
#define PROJECT_MINESWEEPER_RANDOMNUMBER_H
#include <random>

class randomNumber {
    static std :: mt19937 random;
public:
    static int numberInt(int min, int max);
    static float numberFloat(float min, float max);

};


#endif //PROJECT_MINESWEEPER_RANDOMNUMBER_H
