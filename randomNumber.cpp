//
// Created by jordan gillispie on 4/19/22.
//

#include "randomNumber.h"
#include <ctime>
std :: mt19937 randomNumber:: random(time(0));

int randomNumber::numberInt(int min, int max) {
    std:: uniform_int_distribution<int> dist(min, max);
    return dist(random);
}
float randomNumber ::numberFloat(float min, float max) {
    std::uniform_real_distribution<float> dist( min,  max);
    return dist(random);

}
