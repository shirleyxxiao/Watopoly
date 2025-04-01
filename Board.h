#ifndef BOARD_H
#define BOARD_H

#include "Player.h"
#include "subject.h"
#include "building.h"
#include "academic.h"
#include "ownable.h"
#include "gym.h"
#include "Unownable.h"
#include "residence.h"

#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace std;

class Board: public Subject {
    int currPlayer;
    int remainingRimCups;
    public: 
        Board();
        ~Board();
        vector<unique_ptr<Player>> vec_players_selected;
        vector<unique_ptr<Building>> vec_buildings;
        Player* getPlayer(string s);
        void printBoard();
        void stateOfBoardChange();
        int getNumPlayers();
        Building* getBuilding(string Bname);
        void addPlayer(unique_ptr<Player> player);
        void addBuildingINIT(string Bname, string block, int improvements, int pos, int pur, int imp, size_t z, size_t o, size_t t, size_t thr, size_t f, size_t fiv);
        int getCurrPlayer();
        void setCurrPlayer(int n);
        int getRemainingNumRimCups();
        void setRemainingNumRimCups(int n);
        int moneyOwed(Building *building, int diceSum);
        void trade(string name, string giveMoney, string receiveMoney, Player *player);
        void academicImprovements(Building *property, string action, Player *player);
        void mortgage(Building *property, Player *player);
        void unmortgage(Building *property, Player *player);
        bool bankrupt(Player *player, int Owed, Player *toWho);
        void auction(Building *building);
        void pay(Player *whoOwes, int howMuchOwed, Player *toWhoOwed);
        Player* getOwner(Building *b);
        void setOwner(Building *b, Player *p); 
        void removeOwner(Building *b);
        void squareProcessing(int sum_of_roll, bool fair_dice);
        void reset();
};


#endif
