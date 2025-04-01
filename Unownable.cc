#include "Unownable.h"
// #include "observer.h
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <memory>

using namespace std;

const int bottomLength = 7;

Unownable::Unownable(std::string BName, size_t pos): Building{BName, pos, false} {
    // ownable = false;
}

void Unownable::printLongName(int lineNum) {
    std::string name = this->getBName();
    int length = name.length();
    if (length <= 7){
        if (lineNum == 1){
            std::cout << std::left << std::setw(bottomLength) << name << "|";
        } else {
            emptyRow();
        }
    } else {
        size_t lastSpace = name.rfind(' ');
        std::string first = name.substr(0, lastSpace);
        std::string second = name.substr(lastSpace + 1);
        if (lineNum == 1){
            std::cout << left << setw(bottomLength) << first << "|";
        } else {
            std::cout << left << setw(bottomLength) << second << "|";
        }
    }
}

void Unownable::printLine(int lineNum){
    if (lineNum == 1){
        printLongName(1);
    }
    if (lineNum == 2){
        printLongName(2);
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

void Unownable::printName(){
    cout << "";
}

int Unownable::triggerEvent(Player& player, bool fairDice){
    string BName = getBName();
    if (BName == "SLC"){
        std::unique_ptr event = EventFactory::createEvent(true);
        return event->execute(player, fairDice); // will always return 0
    } 
    if (BName == "NEEDLES HALL"){
        std::unique_ptr event = EventFactory::createEvent(false);
        return event->execute(player, fairDice); // if gain money return 0 and if can pay the lost money return 0, else player cannot pay the amount and return that number 
    } 
    if (BName == "COLLECT OSAP"){
        cout << "Collect $200!" << endl;
        player.gainMoney(200);
        return 0; //always 0
    } 
    if (BName == "DC Tims Line"){
        std::unique_ptr event = std::make_unique<OnDcTimsLine>();
        return event->execute(player, fairDice); //0 if still in jail, if left returns num 2-12 for steps or 50 bc player cant pay 50
    } 
    if (BName == "GO TO TIMS"){
        cout << "Go to DC Tims Line!" << endl;
        player.sentTo(10);
        return 0; //always 0
    }
    if (BName == "Goose Nesting"){
        cout << "Oops! You are attacked by a flock of nesting geese!" << endl;
        return 0; //always 0
    }
    if (BName == "COOP FEE"){
        cout << "Pay $150 Coop fee!" << endl;
        return player.loseMoney(150); //return 0 is can pay, else return 150 bc cant pay
    }
    if (BName == "TUITION"){ //return 0 if paid, returns a number is player cannot afford to pay (either 300 or 10% of their worth)
        cout << "Pay tuition: $300(1) or 1/10 total worth(2)?" << endl;
        char response;
        while (true){
            cin >> response;
            if (response == '1'){
                return player.loseMoney(300);
                break;
            }
            if (response == '2'){
                int tenPercent = player.total_worth() / 10;
                return player.loseMoney(tenPercent);
                break;
            }
            cout << "Invalid Input!" << endl;
        }
    }
}

