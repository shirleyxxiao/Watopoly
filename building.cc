#include "building.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int bottomLength = 7;

Building::Building(string name, size_t blockPosition, bool isOwnable): name{name}, blockPosition{blockPosition}, isOwnable{isOwnable} {
    playerOn = std::vector<char>();
}

string Building::getBName() const {
    return name;
}

size_t Building::getBPos() const {
    return blockPosition;
}

bool Building::getOwnableStatus() const {
    return isOwnable;
}
void Building::setOwnable(bool b){
    isOwnable = b;
}


void Building::printBottom() {
    for (int i = 0; i < bottomLength; i++){
        cout << "_";
    }
    cout << "|";
} // Subject::getObserverNames

void Building::emptyRow(){
    for (int i = 0; i < bottomLength; i++){
        cout << " ";
    }
    cout << "|";
}

void Building::printPlayer(){
    for (size_t i = 0; i < playerOn.size(); i++){
        cout << playerOn[i];
    }
    for (size_t i = 0; i < bottomLength - playerOn.size(); i++){
        cout << " ";
    }
    cout << "|";
}

void Building::attachPlayer(char token){
    playerOn.push_back(token);
}

void Building::clearPlayer(){
    if (playerOn.size() > 0){
        playerOn = std::vector<char>();
    }
}

bool Building::ifOwnable(){
    return isOwnable;
}


