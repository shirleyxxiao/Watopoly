#include "DisplayEvent.h"
#include "observer.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <memory>
using namespace std;


Display::Display(Board* b): b{b} {}

void Display::notify(){
    b->stateOfBoardChange();
    b->printBoard();
}

