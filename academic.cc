#include "academic.h"
#include "ownable.h"

#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>


using namespace std;

const string YELLOW = "\033[33m";
const string RESET = "\033[0m";
const int bottomLength = 7;

Academic::Academic(string name, size_t blockPosition, size_t improvementLevel, string monopolyBlock, unique_ptr<vector<size_t>> tuition, int purchaseCost, int improvementCost, bool hasMonopoly): 
    Ownable{name, blockPosition, true, purchaseCost}, improvementLevel{improvementLevel}, monopolyBlock{monopolyBlock}, tuition{move(tuition)}, purchaseCost{purchaseCost}, improvementCost{improvementCost}, hasMonopoly{hasMonopoly} {}

int Academic::getLevel() const {
    return improvementLevel;
}

void Academic::setImprovments(size_t newLevel) {
    improvementLevel = newLevel;
}

size_t Academic::getTuition() const {
    return (*tuition)[improvementLevel];
}

int Academic::getImprovementCost() const {
    return improvementCost;
}

void Academic::buyImprovement() {
    ++improvementLevel;
}

void Academic::sellImprovement() {
    --improvementLevel;
}

char Academic::getBType() const { return 'A'; }

string Academic::getMonopolyBlock() const {
    return monopolyBlock;
}

void Academic::printName() {
    string name = getBName();
    cout << left << setw(bottomLength) << name << "|";
}

void Academic::printImpr() {
    for (size_t i = 0; i < improvementLevel; i++){
        cout << YELLOW << "I" << RESET;
    }
    for (size_t i = 0; i < (bottomLength - improvementLevel); i++){
        cout << "-";
    }
    cout << "|";
}

void Academic::printLine(int lineNum){
    if (lineNum == 1){
        emptyRow();
    }
    if (lineNum == 2){
        printImpr();
    }
    if (lineNum == 3){
        printName();
    }
    if (lineNum == 4){
        printPlayer();
    }
    if (lineNum == 5){
        printBottom();
    }
}

void Academic::setHasMonopoly(bool b){
    hasMonopoly = b;
}

bool Academic::getHasMonopoly(){
    return hasMonopoly;
}

