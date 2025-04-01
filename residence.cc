#include "residence.h"
#include "ownable.h" 

#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
using namespace std;

const int bottomLength = 7;

Residence::Residence(string name, size_t blockPosition): Ownable{name, blockPosition, true, 200} {}

int Residence::calcResCost(int ownedNum) {
    int feeOwed = 0;
    
    if (ownedNum == 1) {
        return 25;
    } else if (ownedNum == 2) {
        return 50;
    } else if (ownedNum == 3) {
        return 100;
    } else if (ownedNum == 4) {
        return 200;
    }

    return feeOwed;
}

void Residence::printName() {
    string name = getBName();
    cout << left << setw(bottomLength) << name << "|";
}

void Residence::printLine(int lineNum){
    if (lineNum == 1){
        printName();
    }
    if (lineNum == 2){
        emptyRow();
    }
    if (lineNum == 3){
        emptyRow();
    }
    if (lineNum == 4){
        printPlayer();
    }
    if (lineNum == 5){
        printBottom();
    }
}

char Residence::getBType() const { return 'R'; }


