#include "ownable.h"
#include "building.h" 

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

const int bottomLength = 7;

Ownable::Ownable(string name, size_t blockPosition, bool isOwnable, int propertyCost): Building{name, blockPosition, isOwnable}, propertyCost{propertyCost}, isMortgaged{false} {}

int Ownable::getCost() const {
    return propertyCost;
} 

bool Ownable::getMortgageState() const {
    return isMortgaged;
}
void Ownable::setMortgageState(bool mortgage) {
    isMortgaged = mortgage;
}

void Ownable::printName(){
    string name = getBName();
    cout << name;
}

void Ownable::printLine(int lineNum){
}


