#include "Player.h"
#include "prng.h"
#include "building.h"
#include "ownable.h"
#include "academic.h"

#include <cstddef>   
#include <cstdint>   
#include <iostream>  
#include <sstream>   
#include <string>   
#include <vector>   
#include <ctime>    
#include <map> 

using namespace std;

const string RED = "\033[31m";
const string BLUE = "\033[34m";
const string GREEN = "\033[32m";
const string RESET = "\033[0m";

Player::Player(string name, char acronym, int cups, int money, int pos, int jail, int turns) : 
    position(pos), name(name), money(money), acronym(acronym), inJail(jail), jailTurns(turns), isBankrupt(false), numRes(0), numGym(0), diceSum(0), rimCups(cups) {}

// true: moveforward step
// false: movebackward step
void Player::move(size_t step, bool forward) {
    if (forward){
        position += step;
        if (position > 40){
            position -= 40;
            cout << "Pass origin, get $200!" << endl;
            gainMoney(200);
            // return true;        
            // reports to main that the player pass COLLECT OSAP
        }
        if (position == 40){
            position = 0;
        }
    } else {
        if (position < step){
            position = (position - step) + 40;
        } else {
            position -= step;
        }
    }
    // return false            
    // reports to main that the player does not need to COLLECT OSAP
} // Player::move


void Player:: gainMoney(int amount){
    money += amount;
    cout << "You gain $" << amount << "!" << endl;
    cout << "Your current balance: $" << money << endl;
}

int Player:: loseMoney(int amount){
    if (money >= amount){
        money -= amount;
        cout << "You lose $" << amount << endl;
        cout << "Your current balance: $" << money << endl;
        return 0;
    } else {
        return amount;
    }
}

void Player::loseCup(){
    rimCups -= 1;
}

void Player::sentTo(size_t pos){
    position = pos;
    if (pos == 10){
        inJail = 1;
    }
}

size_t Player::rollDice(bool fairDice){
    // PRNG prng(12345);  // Create PRNG with seed 12345
    // PRNG prng;
    if (fairDice == true) {
        PRNG prng(static_cast<std::uint32_t>(std::time(0)));  // Seed with current time
        size_t dice1 = prng(6) + 1;
        size_t dice2 = prng(6) + 1;
        cout << "Dice1: " << dice1 << " Dice2: " << dice2 << endl;
        return dice1 + dice2;
    } else {
        int x;
        int y;
        cout << "Please enter your roll dice digits: [int] [int] " << endl;
        cin >> x;
        cin >> y;
        while (x < 0) {
            cout << "Oops, the first number is negative: please enter a postive number: " << endl;
            cin >> x;
        }
        while (y < 0) {
            cout << "Oops, the second number is negative: please enter a postive number: " << endl;
            cin >> y;
        }
        cout << "Dice1: " << x << " Dice2: " << y << endl;
        return x + y;
    }
}

size_t Player::rollDouble(bool fairDice){
        // PRNG prng(12345);  // Create PRNG with seed 12345
        // PRNG prng;
    if (fairDice == true){
        PRNG prng(static_cast<std::uint32_t>(std::time(0)));  // Seed with current time
        size_t dice1 = prng(6) + 1;
        size_t dice2 = prng(6) + 1;
        cout << "Dice1: " << dice1 << " Dice2: " << dice2 << endl;
        if (dice1 == dice2){
            return 2 * dice1;
        } else {
            return dice1 + dice2 + 12;
        }
    } else {
        int x;
        int y;
        cin >> x;
        cin >> y;
        while (x < 0) {
            cout << "Oops, the first number is negative: please enter a postive number: " << endl;
            cin >> x;
        }
        while (y < 0) {
            cout << "Oops, the second number is negative: please enter a postive number: " << endl;
            cin >> y;
        }
        cout << "Dice1: " << x << " Dice2: " << y << endl;
        if (x == y){
            return 2 * x;
        } else {
            return x + y + 12;
        }
        
    }
}

int Player:: ifInJail(){
    return inJail;
}

int Player:: timesInJail(){
    return jailTurns;
}

int Player::cups(){
    return rimCups;
}

void Player::winCup(){
    rimCups += 1;
}

void Player::setFree(){
    inJail = 0;
    jailTurns = 0;
}

void Player:: incJailTurn(){
    jailTurns += 1;
}

void Player::broadcastPos(Building* bld){
    bld->attachPlayer(acronym);
}

void Player::printPlayer() {
    cout << acronym; 
} // Player::printPlayer

void Player::addOwnable(Ownable* o){
   properties.emplace_back(o);
    if (o->getBType() == 'A'){ //if academic then looks for monopoly 
        map<string, int> m = {{"Arts1", 2}, {"Arts2", 3}, {"Eng", 3}, {"Health", 2}, {"Env", 3}, {"Sci1", 3}, {"Sci2", 3}, {"Math", 2}};
        string block = (static_cast<Academic*>(o))->getMonopolyBlock();
        int numBlocks = m[block];
        int ct = 0;
        
        for (int i = 0; i < properties.size(); ++i){
            if (properties[i]->getBType() == 'A'){
                if ((static_cast<Academic*>(properties[i]))->getMonopolyBlock() == block){
                    ++ct;
                }
            }
        }
        if (ct == numBlocks){ // found monopoly
            for (int i = 0; i < properties.size(); ++i){
                if (properties[i]->getBType() == 'A'){
                    if ((static_cast<Academic*>(properties[i]))->getMonopolyBlock() == block){
                        (static_cast<Academic*>(properties[i]))->setHasMonopoly(true);
                    }
                }
            }
        }
    }
   if (o->getBType() == 'G'){
       setNumGymOwned(1);
   }
   if (o->getBType() == 'R'){
       setNumResOwned(1);
   }
}


bool Player::findMonopolies(string monopolyName){
    for (int i = 0; i < monopolies.size(); ++i){
        if (monopolies[i] == monopolyName){
            return true;
        }
    }
    return false;
}

void Player::removeOwnable(Ownable* o){
   int i = 0;
   for (i = 0; i < properties.size(); ++i){
       if (properties[i]->getBName() == o->getBName()){
           break;
       }
   }
   properties.erase(properties.begin() + i);
}


Ownable* Player::getOwnable(int pos){
   return properties[pos];
}


Ownable* Player::getOwnable(string name){
   for (int i = 0; i < properties.size(); ++i){
       if (properties[i]->getBName() == name){
           return properties[i];
       }
   }
}


int Player::total_worth(){
   //calculate total worth of Player money + assests (in properties and improvements)
   int moneyTotal = money;
   int improvementsTotal = 0;
   int propertiesTotal = 0;
   for (int i = 0; i < properties.size(); ++i){
       //sell an improvement, they receive half of the cost of the improvement!!!
       if (properties[i]->getBType() == 'A'){
            Academic *a = static_cast<Academic*>(properties[i]);
           if (a->getLevel() != 0) {
                for (int j = 0; j < a->getLevel(); ++j){
                    improvementsTotal += (a->getImprovementCost() / 2);
                }
           }
       }
       //When a property is mortgaged, they receive half of the cost of the property
       // CHECK IF ITS NOT MORTGAGED
       if (properties[i]->getMortgageState() == false){
           propertiesTotal += (properties[i]->getCost() / 2);
       }
   }
   return moneyTotal + improvementsTotal + propertiesTotal;
}

// Getters and Setters: 

string Player::getName(){
    return name;
}

void Player::setName(string new_name){
    name = new_name;
}

size_t Player::getPos(){
    return position;
}

void Player::setPos(int pos){ //adds pos to the previous position value
    position = position + pos;
}

char Player::getAcronym(){
    return acronym;
}

void Player::setAcronym(char c){
    acronym = c; 
}

int Player::getMoney(){
    return money;
}

void Player::setMoney(int n){ //adds n to the previous money value
    money = money + n;
}

int Player::getDiceSum(){
    return diceSum;
}

void Player::setDiceSum(int n){
    diceSum = n;
}

int Player::getNumGymOwned(){
    return numGym;
}

void Player::setNumGymOwned(int n){
    numGym += n;
}

int Player::getNumResOwned(){
    return numRes;
}

void Player::setNumResOwned(int n){
    numRes += n;
}

int Player::getJailStatusNum(){
    return inJail;
}

void Player::setJailStatusNum(int n){
    inJail = n;
}

int Player::getJailTurns(){
    return jailTurns;
}

void Player::setJailTurns(int n){
    jailTurns += n;
}

int Player::getRimCups(){
    return rimCups;
}

void Player::setRimCups(int n){
    rimCups += n;
}

bool Player::getBankruptStatus(){
    return isBankrupt;
}

void Player::setBankruptStatus(bool b){
    isBankrupt = b;
}

void Player::printAssests(){
    cout << "Assets of: " << BLUE <<  getName() << " " << getAcronym() << RESET << ":" << endl; 
    cout << "Money: $" << GREEN << getMoney() << RESET << "  Number of RimCups: " << getRimCups() << endl; 
    cout << "Properties owned: " << endl; 
    int ct = 0; 
    if (properties.size() == 0){
        cout <<  RED << " NO PROPERTIES OWNED " << RESET << endl;
    }
    while (ct < properties.size()){
        cout << ct << ". " << BLUE << properties[ct]->getBName() << RESET << " ";
        if (properties[ct]->getMortgageState()){
            cout << "- " << RED << "MORTGAGED" << RESET << endl;
        } else {
            if (properties[ct]->getBType() == 'A') {
                cout << "- improvement number: " << (static_cast<Academic*>(properties[ct]))->getLevel();
            }
            cout << " - property cost: $" << properties[ct]->getCost() << endl;
        }
        ++ct;
    }
    cout << "Just in case you were too lazy to calculate your total worth, it's: $" << GREEN << total_worth() << RESET << endl;
    cout << "--------------------------------------------------------------------------" << endl;
}

