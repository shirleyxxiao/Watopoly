#include "gym.h"
#include "ownable.h"
#include "building.h"

#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;

const int bottomLength = 7;

//Gym::Gym(string name, size_t blockPosition, Player *owner): Ownable{name, blockPosition, true, owner, 150} {}
Gym::Gym(string name, size_t blockPosition): Ownable{name, blockPosition, true, 150} {}


/* diceSum -> is the sum of the two dice rolled */
/* numGymOwner -> is the number of gym owners (maximum 2) */
int Gym::usageFee(int diceSum, int numGymOwner) {
    //One can only claim rent if there exists and owner, so we do not consider the case of 0 gym owners here
    int fee = 0;
    if ( numGymOwner == 1) {
        fee = 4 * diceSum;
    } else if ( numGymOwner == 2 ) {
        fee = 10 * diceSum;
    }
    return fee;
}

void Gym::printName() {
    string name = getBName();
    cout << left << setw(bottomLength) << name << "|";
}

void Gym::printLine(int lineNum){
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

/* getBType -> returns the type of building from either {A, R, G} */
char Gym::getBType() const { return 'G'; }
