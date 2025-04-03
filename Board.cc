#include "Board.h"
#include "Player.h"
#include "academic.h"
#include "building.h"
#include "ownable.h"
#include "gym.h"
#include "Unownable.h"
#include "residence.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string RESET = "\033[0m"; 

Board::Board(): currPlayer(0), remainingRimCups(2) {}

Board::~Board() {
    vec_buildings.clear();  // unique_ptrs auto-delete if destructor virtual
    vec_players_selected.clear();  // unique_ptrs auto-delete players
}

Player* Board::getPlayer(string s){
    for (int i = 0; i < vec_players_selected.size(); ++i){
        if (vec_players_selected[i]->getName() == s){
            return vec_players_selected[i].get();
        }
    }
    return nullptr; 
}


void Board::stateOfBoardChange(){
    for (size_t i = 0; i < 40; i++){
        vec_buildings[i].get()->clearPlayer();
    }
    for (size_t i = 0; i < vec_players_selected.size(); i++){
        vec_players_selected[i].get()->broadcastPos(vec_buildings[vec_players_selected[i].get()->getPos()].get());
    }
}

void Board::printBoard(){
    for (int i = 0; i < 89; i++){
        cout << "_";
    }
    cout << endl;
    for (int k = 1; k <= 5; k++){
        cout << "|";
        for (size_t i = 20; i <= 30; i++){
            vec_buildings[i]->printLine(k);
        }
        cout << endl;
    }
    for (int i = 19; i >= 17; i--){
        for (int k = 1; k <= 5; k++){
            cout << "|";
            vec_buildings[i]->printLine(k);
            for (int i = 0; i <= 70; i++){
                cout << " ";
            }
            cout << "|";
            vec_buildings[50 - i]->printLine(k);
            cout << endl;
        }
    }
    for (int k = 1; k <= 3; k++){
        cout << "|";
        vec_buildings[16]->printLine(k);
        for (int i = 0; i <= 70; i++){
            cout << " ";
        }
        cout << "|";
        vec_buildings[34]->printLine(k);
        cout << endl;
    }

    cout << "|";
    vec_buildings[16]->printLine(4);
    for (int i = 0; i <= 12; i++){
        cout << " ";
    }
    for (int i = 0; i <= 44; i++){
        cout << "_";
    }
    for (int i = 0; i <= 12; i++){
        cout << " ";
    }
    cout << "|";
    vec_buildings[34]->printLine(4);
    cout <<  endl;

    cout << "|";
    vec_buildings[16]->printLine(5);
    for (int i = 0; i <= 11; i++){
        cout << " ";
    }
    cout << "|";
    for (int i = 0; i <= 44; i++){
        cout << " ";
    }
    cout << "|";
    for (int i = 0; i <= 11; i++){
        cout << " ";
    }
    cout << "|";
    vec_buildings[34]->printLine(5);
    cout <<  endl;

    cout << "|";
    vec_buildings[15]->printLine(1);
    for (int i = 0; i <= 11; i++){
        cout << " ";
    }
    cout << "| ";
    cout << GREEN << "#   #  ##  #####  ###  ###   ###  #   #   #" << RESET;
    cout << " |";
    for (int i = 0; i <= 11; i++){
        cout << " ";
    }
    cout << "|";
    vec_buildings[35]->printLine(1);
    cout <<  endl;

    cout << "|";
    vec_buildings[15]->printLine(2);
    for (int i = 0; i <= 11; i++){
        cout << " ";
    }
    cout << "| ";
    cout << GREEN << "#   # #  #   #   #   # #  # #   # #   #   #" << RESET;
    cout << " |";
    for (int i = 0; i <= 11; i++){
        cout << " ";
    }
    cout << "|";
    vec_buildings[35]->printLine(2);
    cout <<  endl;

    cout << "|";
    vec_buildings[15]->printLine(3);
    for (int i = 0; i <= 11; i++){
        cout << " ";
    }
    cout << "| ";
    cout << GREEN << "# # # ####   #   #   # ###  #   # #    # # " << RESET;
    cout << " |";
    for (int i = 0; i <= 11; i++){
        cout << " ";
    }
    cout << "|";
    vec_buildings[35]->printLine(3);
    cout <<  endl;

    cout << "|";
    vec_buildings[15]->printLine(4);
    for (int i = 0; i <= 11; i++){
        cout << " ";
    }
    cout << "| ";
    cout << GREEN << "# # # #  #   #   #   # #    #   # #     #  " << RESET;
    cout << " |";
    for (int i = 0; i <= 11; i++){
        cout << " ";
    }
    cout << "|";
    vec_buildings[35]->printLine(4);
    cout <<  endl;

    cout << "|";
    vec_buildings[15]->printLine(5);
    for (int i = 0; i <= 11; i++){
        cout << " ";
    }
    cout << "| ";
    cout << GREEN << "##### #  #   #    ###  #     ###  ## #  #  " << RESET;
    cout << " |";
    for (int i = 0; i <= 11; i++){
        cout << " ";
    }
    cout << "|";
    vec_buildings[35]->printLine(5);
    cout <<  endl;

    cout << "|";
    vec_buildings[14]->printLine(1);
    for (int i = 0; i <= 11; i++){
        cout << " ";
    }
    cout << "|";
    for (int i = 0; i <= 44; i++){
        cout << "_";
    }
    cout << "|";
    for (int i = 0; i <= 11; i++){
        cout << " ";
    }
    cout << "|";
    vec_buildings[36]->printLine(1);
    cout <<  endl;

    for (int k = 2; k <= 5; k++){
        cout << "|";
        vec_buildings[14]->printLine(k);
        for (int i = 0; i <= 70; i++){
            cout << " ";
        }
        cout << "|";
        vec_buildings[36]->printLine(k);
        cout << endl;
    }
    for (int i = 13; i >= 12; i--){
        for (int k = 1; k <= 5; k++){
            cout << "|";
            vec_buildings[i]->printLine(k);
            for (int i = 0; i <= 70; i++){
                cout << " ";
            }
            cout << "|";
            vec_buildings[50 - i]->printLine(k);
            cout << endl;
        }
    }
    for (int k = 1; k <= 4; k++){
        cout << "|";
        vec_buildings[11]->printLine(k);
        for (int i = 0; i <= 70; i++){
            cout << " ";
        }
        cout << "|";
        vec_buildings[39]->printLine(k);
        cout << endl;
    }
    cout << "|";
    vec_buildings[11]->printLine(5);
    for (int i = 0; i <= 70; i++){
        cout << "_";
    }
    cout << "|";
    vec_buildings[39]->printLine(5);
    cout <<  endl;
    for (int k = 1; k <= 5; k++){
        cout << "|";
        for (size_t i = 11; i >= 1; i--){
            vec_buildings[i - 1]->printLine(k);
        }
        cout << endl;
    }
}

// void Board::stateOfBoardChange(){
//     notifyObservers();
// }

int Board::getNumPlayers(){
    return vec_players_selected.size();
}

void Board::addPlayer(unique_ptr<Player> player){
    vec_players_selected.emplace_back(move(player));
}

int Board::getCurrPlayer(){
    return currPlayer;
}

void Board::setCurrPlayer(int n){
    currPlayer = n;
}

int Board::getRemainingNumRimCups(){
    return remainingRimCups;
}

void Board::setRemainingNumRimCups(int n){
    remainingRimCups = n; 
}


int Board::moneyOwed(Building *building, int diceSum){
    Ownable* ownableBuilding = static_cast<Ownable*>(building);

    char bType = ownableBuilding->getBType();
    int owed = 0;
    if (bType == 'A') {

        Academic *academic = static_cast<Academic*>(ownableBuilding);
        //check the number of academic properties an owner owns?
        //tuition is the rent
        //Tuition is doubled for each building that has no improvements when the monopoly is owned by a single player.
        //check if the current building is a part of a monopoly and if there are no improvements
        //otherwise, just regular tuition cost
        
        //1. can check if the current building (getMonopolyBlock) is a part of the monopoly vector of player
        //2. if is part of a monopoly, check if there are improvements (getImprovementLevel) if 0 => double, else return Tuition
        
        //1. get owner
        //2. from academic building -> get getMonopolyBlock
        //2. from player, findMonopolies() => T/F

        //Player *owner = academic->getOwner();
        Player *owner = getOwner(academic);
        if (owner == nullptr) {
            std::cerr << "Error. There is no owner for this building." <<endl;
            return 0;
        }

        string monBlock = academic->getMonopolyBlock();
        bool isInMonopoly = owner->findMonopolies(monBlock);

        if (isInMonopoly) {
            int impLevel = academic->getLevel();
            if(impLevel == 0) {
                return 2*academic->getTuition();
            }
        }

        return academic->getTuition();

    } else if (bType = 'R') {
        Residence *residence = static_cast<Residence*>(ownableBuilding);
        //Player *owner = residence->getOwner();
        Player *owner = getOwner(residence);
        if (owner == nullptr) {
            std::cerr << "Error. There is no owner for this building." <<endl;
            return 0;
        }

        int numOwner = owner->getNumResOwned();
        return residence->calcResCost(numOwner);

    } else if (bType == 'G') {

        Gym *gym = static_cast<Gym*>(ownableBuilding);
        //Player* owner = gym->getOwner();
        Player *owner = getOwner(gym);

        if (owner == nullptr) {
            std::cerr << "Error. There is no owner for this building." <<endl;
            return 0;
        }
        
        int gymNum = owner->getNumGymOwned();
        return gym->usageFee(diceSum, gymNum);
    }

    return owed;

}
void Board::academicImprovements(Building *property, string action, Player *player){ //NEED TO CHECK IF USER GETS BANKRUPT
    //verifying ownership
   try {
        string playerName = player->getName();
        Ownable *o = static_cast<Ownable*>(property);
        //o->getOwner()

        if (o->getBType() != 'A') {
            cout << "Unsuccesful attempt at improvement. This is not an academic building."<<endl;
            return;
        }

        if (getOwner(o) == nullptr) {
            std::cerr << "Unsuccesful attempt at improvement. The building has no owner. " << endl;
            return;
        }

        //string buildingOwner = o->getOwner()->getName();
        string buildingOwner = getOwner(o)->getName();

        if (buildingOwner != playerName) { //verifying ownership
            std::cerr << "Unsuccesful attempt at improvement. " << playerName << " does not own " << property->getBName() <<endl;
            return;
        }

        Academic *a = static_cast<Academic*>(property);
        if (action == "buy") {
            if (!a->getHasMonopoly()) {
                cout << "Attempt to purchase improvement failed. You do not have a monopoly." << endl;
                return;
            }
            if (a->getLevel() >= 5 ) {
                cout << "Attempt to purchase improvement failed. You have the maximum number of improvements already." << endl;
                return;
            }
            

            //1. check that player owns that building
            //2. check if they have enough money -> checking bankruptcy


            //take money out of their money
            int impCost = a->getImprovementCost();

            if (player->getMoney() < impCost) {
                std::cerr << "Unable to purchase improvement, you do not have enough funds. Consider selling or mortgaging properties if possible." << endl;
                return;
            }
            if (player->getMoney() == impCost) {
                cout << "If you make this improvement purchase, you will have a cash balance of $0. Would you like to proceed?" << endl;
                char response;
                while (true) {
                    cout << "Please enter Y for yes and N for no:" << endl;
                    cin >> response;
                    if (response == 'Y') {
                        break;
                    } 
                    if (response == 'N') {
                        cout << "You have decided to terminate this purchase. Good choice." << endl;
                        return;
                    }
                }
            }

            impCost = -impCost;
            player->setMoney(impCost);
            a->buyImprovement();
            cout << "You have successfully purchased an improvement for " << a->getBName() << " for $" << a->getImprovementCost() <<". Now with " << a->getLevel() << " improvements. " << endl;
        }
        if (action == "sell") {
            if (!a->getHasMonopoly()) {
                cout << "Attempt to sell improvement failed. You do not have a monopoly." << endl;
                return;
            }
            if (a->getLevel() <= 0){
                cout << "Attempt to sell improvement failed. You do not have improvements to sell." << endl;
                return;
            }
            int impCost = a->getImprovementCost() / 2;
            player->setMoney(impCost);
            a->sellImprovement();
            cout << "You have successfully sold an improvement for " << a->getBName() << " for $" << a->getImprovementCost() <<". Now with " << a->getLevel() << " improvements. " << endl;
        }
   } catch (...) {
        std::cerr << "Invalid action. Denied." <<endl;
        return;
   }
}

void Board::trade(string name, string giveMoney, string receiveMoney, Player *player){
       try {
        //Player *player is the person trade is requested from
        Player *reqFrom = getPlayer(name);

        //if user is receiving/giving building else money and stoi()
        bool giveBuilding = false;
        bool receiveBuilding = false;

        bool isGiveMortgaged = false;
        bool isReceiveMortgaged = false;

        int giveMortgage = 0; //if mortgaged, player receive building + pay 10%
        int receiveMortgage = 0;  //if mortgaged, player receive building + pay 10%

        //if there is time, do a check for ownership for building in the below loop?

        //doing check for mortgage in here and calcalate the 10%

        vector<string> trading = {giveMoney, receiveMoney};
        Ownable *give;
        Ownable *receive;
        //trading.size()
        for (int i = 0; i < trading.size(); ++i) {
            for (int j = 0; j < vec_buildings.size(); ++j) {

                //also want to check it is the correct owner                
                if (vec_buildings[j]->getBName() == trading[i]){
                    if (!(vec_buildings[j]->getOwnableStatus())){
                        cout << "Trade rejected. This building is unownable." << endl;
                        return;
                    }
                    if (trading[i] == giveMoney) {


                        giveBuilding = true;
                        
                        give = static_cast<Ownable*>(vec_buildings[j].get());
                        if(give->getBType() == 'A') { 

                            if(static_cast<Academic*>(give)->getLevel() != 0) {
                                cout << "Trade rejected, you cannot trade a property with improvements." << endl; 
                                return;     
                            }
                            
                        }
                        if (give->getMortgageState()) { //get getMortgageState
                            isGiveMortgaged = true;
                            giveMortgage = give->getCost() * 0.1;
                        }
                    } else if (trading[i] == receiveMoney){


                        receiveBuilding = true;
                        receive = static_cast<Ownable*>(vec_buildings[j].get());
                        if(receive->getBType() == 'A') {
                            if(static_cast<Academic*>(receive)->getLevel() != 0) {
                                cout << "Trade rejected. You cannot trade a property with improvements." << endl;    
                                return;  
                            }
                            
                        }
                        if (receive->getMortgageState()) { //get getMortgageState
                            isReceiveMortgaged = true;
                            receiveMortgage = receive->getCost() * 0.1;
                        }
                    }
                }
            }
        }

        if (!giveBuilding && !receiveBuilding) {
            cout << " Trade rejected. Invalid trade." << endl;
            return;
        }
        //Accept/Reject Stage
        cout << name << ", do you accept or reject this offer?" << endl;
        string choice;
        while(true) {
            cout << "Please enter accept or reject." << endl;      
            cin >> choice;
            if(choice == "accept" || choice == "reject") {
                break;
            }
        }

        if (choice == "reject") {
            cout << name << " has rejected the offer." << endl;
            return;
        }

        //HERE:
        //1. check bool of giveBuilding and receiveBuilding
        //2. check BType
        //3. cast to the correct type
        //4. redefine give and receive
        //5. if the building is mortgaged, need to consider differently!! march 28th
        

        //Money Building
        if (!giveBuilding && receiveBuilding) {
            //how much the player is giving, convert to integer
            int giveM = stoi(giveMoney);
            int bank = player->getMoney(); 

        
            //check if the building is mortgaged

            if ((giveM + receiveMortgage) > bank) {
                cout << "Trade rejected. You do not have enough money to make this trade" <<endl;
                return;
            }

            Player *tmpPlayer = getOwner(receive);
            if(tmpPlayer == nullptr) {
                cout << "Trade rejected. " << name << " does not own " << receiveMoney <<endl;
                return;
            }

            string receiveName = tmpPlayer->getName();

            if ( receiveName != name) { //verifying ownership
                cout << "Trade rejected. " << name << " does not own " << receiveMoney <<endl;
                return;
            }

            receiveMortgage = -receiveMortgage;

            removeOwner(receive);
            setOwner(receive, player);
            reqFrom->setMoney(giveM);

            giveM = -giveM;
            player->setMoney(giveM);
            player->setMoney(receiveMortgage);

            cout << "Trade succesful! " <<endl;
            return;
        } else if (giveBuilding && receiveBuilding) {
            Player *tmpPlayer1 = getOwner(receive);

            if(tmpPlayer1) {
                cout << "Trade rejected. " << name << " does not own " << receiveMoney <<endl;
                return;
            }

            string receiverBuilding = tmpPlayer1->getName();

            if ( receiverBuilding != name ) { //verifying ownership
                cout << "Trade rejected. " << name << " does not own " << receiveMoney <<endl;
                return;
            }

            string giveName = player->getName();
            Player *tmpPlayer = getOwner(give);
            //if no owner
            if(tmpPlayer == nullptr) {
                cout << "Trade rejected. " << giveName << " does not own " << receiveMoney <<endl;
                return;
            }

            string buildingOwner = tmpPlayer->getName();


            if ( buildingOwner != giveName) { //verifying ownership
                cout << "Trade rejected. " << giveName << " does not own " << giveMoney <<endl;
                return;
            }

            //check mortgaging 
            int bankP = player->getMoney(); 
            int bankR = reqFrom->getMoney(); 

            if ( receiveMortgage > bankP ) {
                cout << "Trade rejected. You do not have enough money to make this trade" <<endl;
                return;
            }

            if ( giveMortgage > bankR ) {
                cout << "Trade rejected. You do not have enough money to make this trade" <<endl;
                return;
            }

            giveMortgage = -giveMortgage;
            receiveMortgage = -receiveMortgage;

            reqFrom->setMoney(giveMortgage);
            player->setMoney(receiveMortgage);

            removeOwner(receive);
            setOwner(receive, player);

            removeOwner(give);
            setOwner(give, reqFrom);

            cout << "Trade succesful! " <<endl;
            return;
        } else if (giveBuilding && !receiveBuilding) {  //BUILDING MONEY
            int receiveM = stoi(receiveMoney);
            int bank = reqFrom->getMoney(); 

            if ((receiveM + giveMortgage) > bank) {
                cout << "Trade rejected. " << name << " does not have enough money to make this trade" <<endl;
                return;
            }

            string giveName = player->getName();
            Player *tmpPlayer = getOwner(give);

            if(tmpPlayer == nullptr) {
                cout << "Trade rejected. " << giveName << " does not own " << receiveMoney <<endl;
                return;
            }

            string buildingOwner = tmpPlayer->getName();

            if (buildingOwner != giveName) { //verifying ownership
                cout << "Trade rejected. " << giveName << " does not own " << giveMoney <<endl;
                return;
            }

            removeOwner(give);
            setOwner(give, reqFrom);

            player->setMoney(receiveM);

            receiveM = -receiveM;
            giveMortgage = -giveMortgage;
            reqFrom->setMoney(receiveM);
            reqFrom->setMoney(giveMortgage);
            cout << "Trade succesful! " <<endl;
            return;
            
        } else {
            //throw error
            cout << "Unsuccesful attempt at trading. " << endl;
            return;
        }    
    } catch (...) {
        std::cerr << "Invalid action. Denied." <<endl;
        return;
    }

}

void Board::mortgage(Building *property, Player *player){
    // TO IMPLEMENT

    //1. check the owner of property is in fact player
    //2. check mortgage is false, otherwise, cerr already mortgaged
    //3. determine building type
    //4. check improvements are sold
    //5. change mortgage to true, by setMortgage(false) => non-owners do not have to pay rent when landed
    //6. increase player money by half of the property cost, through getCost in ownable

    //cout << "hello" <<endl;

    Ownable *ownable = static_cast<Ownable*>(property);
    if (ownable->getMortgageState()) {
        cout << "Mortgage Failed. " << ownable->getBName() << " is already mortgaged" <<endl;
        return;
    }
    //Academic *ownable = static_cast<Ownable*>(property);
    //above can only access ownable type
    // Player *tmp = ownable->getOwner();
    Player *tmp = getOwner(ownable);

    
    if (tmp == nullptr) {
        std::cerr << "Mortgage failed. You do not own this property." << endl;
        return;
    }
    string name = tmp->getName();

    if (name != player->getName()) {
        std::cerr << "Mortgage failed. You do not own this property." << endl;
        return;
    }
    if (ownable->getBType() == 'A') {

        Academic *a = static_cast<Academic*>(ownable);
        if (a->getLevel() != 0) {
            std::cerr << "Mortgage failed. You must sell improvements before mortgaging." << endl;          
            return;
        }

        int mortgageValue = a->getCost() / 2;
        player->setMoney(mortgageValue);
        a->setMortgageState(true);


    } else if (ownable->getBType() == 'R') {

        Residence *r = static_cast<Residence*>(ownable);
        int mortgageValue = r->getCost() / 2;
        player->setMoney(mortgageValue);
        r->setMortgageState(true);

    } else if (ownable->getBType() == 'G') {

        Gym *g = static_cast<Gym*>(ownable);
        int mortgageValue = g->getCost() / 2;
        player->setMoney(mortgageValue);
        g->setMortgageState(true);

    } else {
        std::cerr << "Mortgage failed. Property is not of Academic, Residence, or Gym." << endl;
        return;
    }

    cout << "Mortgage successful!" << endl;
    return;

}

void Board::unmortgage(Building *property, Player *player){
   int unmortgageCost = ((static_cast<Ownable*>(property))->getCost()) * 0.6;
   if (player->getMoney() >= unmortgageCost){
       player->setMoney(unmortgageCost * -1); // removes the money from the player
       (static_cast<Ownable*>(property))->setMortgageState(false); //set state of mortgage to false
       setOwner(property, player); // sets the player as the owner of the property (might not need since mortgaging doesnt change ownership)
   } else { //player doesnt have enough to pay
       cout << "You do not have enough money to unmortgage this property. To unmortgage this property you need to pay: $" << unmortgageCost << endl;
   }
}


bool Board::bankrupt(Player *player, int Owed, Player *toWho){
    try {

        if (player->getMoney() >= Owed) { //has enough money to pay
            cout << "You have enough money to pay your debts, you do not meet the criteria to declare Bankruptcy." << endl; 
            return false;
        } else { //has enough money to pay with assets 
            if ( player->total_worth()>= Owed) {
                cout << "You have enough assets to sell/mortgage to pay your debts, you do not meet the criteria to declare Bankruptcy." << endl; 
                return false;
            } else { //doesnt have enough money 
                //PLAYER IS BANKRUPT
                cout << "Your total worth if you sell/mortgage all of your improvements and properties is: $" << player->total_worth() << ". Unfortunately, you still won't have enough money to pay your debts. We are sorry to see you go, better luck next time." << endl;
                if (toWho) { //money owed to another player
                    cout << toWho->getName() << " receives all assets from " << player->getName() << ": " << endl;
                    for (int i = 0; i < player->properties.size(); ++i) {
                        if (player->properties[i]->getMortgageState() == true){
                            int fee = player->properties[i]->getCost() * 0.1;
                            if (toWho->getMoney() < fee){
                                cout << "To get this mortgaged property you need to pay 10% of its original cost ($" << fee << ")" << endl;
                                pay(toWho, fee, nullptr); //figure out payment with money owed to BANK
                            } else {
                                toWho->setMoney(fee * -1); // player given the property pays 10% of the property cost (as required)
                                cout << toWho->getName() << " pays $" << fee << " to the bank for the mortgaged property " << player->properties[i]->getBName() << endl;
                            }
                        }
                    }
                    toWho->setMoney(player->getMoney()); //gives the remaining money to the player owed 
                    cout << "Properties recieved: " << endl; 
                    for (int i = 0; i < player->properties.size(); ++i){
                        cout << player->properties[i]->getBName() << " ";
                        if (player->properties[i]->getMortgageState()){
                            cout << "- MORTGAGED" << endl;
                        } else {
                            if (player->properties[i]->getBType() == 'A') {
                                cout << "- improvement number: " << (static_cast<Academic*>(player->properties[i]))->getLevel() << endl;
                            }else{
                                cout << endl;
                            }
                        }  
                    }
                    for (int i = 0; i < player->properties.size(); ++i) { //does the unmortgaging if chosen
                        if (player->properties[i]->getMortgageState()) { //if property given is mortgaged 
                            cout << "Would you like to unmortgage " << player->properties[i]->getBName() << ", for $" << (player->properties[i]->getCost() * 0.5) << "? (y/n)" << endl;
                            char ans;
                            while (true){
                                cin >> ans;
                                if (ans == 'y'){
                                    toWho->setMoney((player->properties[i]->getCost() * 0.5) * -1); 
                                    cout << player->properties[i]->getBName() << " is now unmortgaged." << endl;
                                    break;
                                } else if (ans == 'n'){
                                    toWho->setMoney((player->properties[i]->getCost() * 0.1)); //returning the 10% 
                                    cout << "The 10% of the property cost you have previously paid has been returned. If you would like to unmortage this property in the future just call the normal unmortage command." << endl;
                                    break;
                                } else{
                                    cout << "Invalid choice, please try again: " << endl;
                                    break;
                                }
                            }
                        }
                    }
                    cout << "Properties recieved: " << endl; 
                    for (int i = 0; i < player->properties.size(); ++i){
                        cout << player->properties[i]->getBName() << " ";
                        if (player->properties[i]->getMortgageState()){
                            cout << "- MORTGAGED" << endl;
                        } else {
                            if (player->properties[i]->getBType() == 'A') {
                                cout << "- improvement number: " << (static_cast<Academic*>(player->properties[i]))->getLevel() << endl;
                            }else{
                                cout << endl;
                            }
                        }  
                    }
                    //changes the ownership 
                    for (int i = 0; i < player->properties.size(); ++i){
                        setOwner(player->properties[i], toWho); //change ownership to player that is owed 
                    }
                                       
                } else { //TO BANK
                    cout << player->getName() << "'s properties go to auction!" << endl;

                    for (int i = 0; i < player->properties.size(); ++i) { //removes the improvments and owner and unmortgages the mortgaged properties
                        if (player->properties[i]->getBType() == 'A') {
                            Academic *a = static_cast<Academic*>(player->properties[i]);
                            while (a->getLevel() > 0) {
                                string action = "sell";
                                academicImprovements(a, action, player);
                            }
                        }
                        removeOwner(player->properties[i]);
                        player->properties[i]->setMortgageState(false);
                        auction(player->properties[i]);
                    }            
                }
                //get rid of their rim card 
                if (player->getRimCups() != 0){ //if player had a rim cup this gives them back into the game (no need to remove from player bc the player will be deleted anyway) 
                    setRemainingNumRimCups(player->getRimCups());
                }
            }
        }
        string name = player->getName();
        player->setBankruptStatus(true);

        for (int i = 0; i < vec_players_selected.size(); ++i){ //removes the player from vec of players in the game
            if (player->getAcronym() == vec_players_selected[i]->getAcronym()){ //player found in the vec
                vec_players_selected.erase(vec_players_selected.begin() + i); //remove from the vector of players playing
                break;
            }
        }
        if (currPlayer == vec_players_selected.size()){ //shifts the turn to the next player if the player removed was at the end, else the currPlayer int stays the same as before becuase the next player shifted into the pos of the removed player 
            currPlayer = 0;
        }

        cout << name << " has left the game!" << endl;
        stateOfBoardChange();
        printBoard();
        return true;

    } catch (...) {
        cout << "Invalid occurence." << endl;
        return false;
    }
}

void Board::auction(Building *building){
    vector<Player *> temp_vec; //temporary vector that holds all the players in the auction
    for (int i = 0; i < vec_players_selected.size(); ++i){
        temp_vec.emplace_back(vec_players_selected[i].get());
        cout << temp_vec[i]->getName() << endl;
    }
    temp_vec.erase(temp_vec.begin() + currPlayer);
    char c;
    int n;
    int bid = (static_cast<Ownable*>(building))->getCost(); // !! can probably change this function to take in Ownable* instead to avoid static casting (also do we want to make it is that the player cannot make the bid higher than what they have in money??)
    cout << "****BEGIN AUCTION:****" << endl;
    cout << "Beginning action at: $" << (static_cast<Ownable*>(building))->getCost() << endl;

    while (temp_vec.size() > 1){

        for (int i = 0; i < temp_vec.size(); ++i){
            cout << "Dear " << temp_vec[i]->getName() << ", would you like to raise the current bid (b <new bid number>) or withdraw from the auction (w): " << endl;
            cin >> c;
            if (c == 'b') { //up the bid
                //cases:
                //1. less than or equal => invalid
                //2. greater
                //3. invalid
                cin >> n; //read in their bid amount
                while (true) { //or just cin >> n?
                    cout << n << endl;
                    if (n > temp_vec[i]->getMoney()) {
                        cout << "This bid is out of your price range, please enter again <number> (your balance is $" << temp_vec[i]->getMoney() << "): " << endl;
                        cin >> n;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore();
                        }
                    } else if (n > bid) {
                        bid = n;
                        cout << "THE NEW BID IS: $" << bid << endl;
                        break;
                    } else if (n <= bid) { //here
                        cout << "This bid is lower than or equal to the current bid, please enter a sum that is higher <number>: " << endl;
                        cin >> n;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore();
                        }
                        //break;
                    } else {
                        cout << "Invalid command entered. Please enter a sum that is higher <number>:" << endl;
                        cin >> n;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore();
                        }
                        //break;
                    }
                } 

            } else if (c == 'w') { //withdraw
                cout << "You have been withdrawn from the Auction." << endl;
                    temp_vec.erase(temp_vec.begin() + i); //removes the player from the auction vector 
                    if (temp_vec.size() != 1){
                        i--;
                    }
            } else { //invalid command
                cout << "Invalid command, auction proceeds to next contestant." << endl;
            }
        }

    }

    //maybe delete the following while loop
/*
    while (temp_vec.size() > 1){
        for (int i = 0; i < temp_vec.size(); ++i){
            cout << "Dear " << temp_vec[i]->getName() << ", would you like to raise the current bid (b <new bid number>) or withdraw from the auction (w): " << endl;
            cin >> c; 
            if (c == 'b'){
                bool lower = true;
                while (lower){
                //cin >> n; //added
                //while (n < temp_vec[i]->getMoney() &&  n > bid){
                    cin >> n;
                    if (n <= bid){
                        cout << "This bid is lower than or equal to the current bid, please enter a sum that is higher <number>: " << endl;
                        //fix logic here??
                    } else if (n > temp_vec[i]->getMoney()){
                        cout << "This bid is out of your price range, please enter again <number> (your balance is $" << temp_vec[i]->getMoney() << "): " << endl;
                        //after it is in this case, there is an issue
                        //lower = false;

                    } else {
                        bid = n;
                        lower = false;
                    } 
                }
                
                cout << "THE NEW BID IS: $" << bid << endl;
            } else if (c == 'w') {
                cout << "You have been withdrawn from the Auction." << endl;
                temp_vec.erase(temp_vec.begin() + i); //removes the player from the auction vector 
                if (temp_vec.size() != 1){
                    i--;
                }
            } else {
                cout << "Invalid command, auction proceeds to next contestant." << endl;
            }
        }
        cout << "temp_vec.size: " << temp_vec.size() << endl;
    }
*/

    // temp_vec is now one element who is the owner of the building 
    //if getOwner returns a nullptr then NO OWNER (BANK) 
    cout << "****AUCTION HAS ENDED.****" << endl;
    cout << "Congratulations " << temp_vec[0]->getName() << ", you are the last bidder! Would you like to buy " << building->getBName() << " for $" << bid << "? (y/n)" << endl;
    char ans;  
    bool okay = true;
    while (okay) {
        cin >> ans;
        if (ans == 'y'){
            if (temp_vec[0]->getMoney() >= bid){
                if (getOwner(building)){ //if the building had a previous owner 
                    removeOwner(building);
                    setOwner(building, temp_vec[0]);
                } else { //if the building was owned by the BANK previously
                    setOwner(building, temp_vec[0]);
                } 
                temp_vec[0]->setMoney(bid * -1);
                cout << "The property " << building->getBName() << " is yours for $" << bid << "." << endl;

            } else {
                //removeOwner(building);
                cout << "Sorry you do not have enough money to buy this property." << endl;
                if (getOwner(building) == nullptr){
                    cout << "This property remains unowned." << endl;
                } else {
                    removeOwner(building);
                    cout << "This property now has no owner." << endl;
                }
            }
            okay = false;
        } else if (ans == 'n'){
            //removeOwner(building);
            if (getOwner(building) == nullptr){
                    cout << "This property remains unowned." << endl;
            } else {
                removeOwner(building);
                cout << "This property now has no owner." << endl;
            }
            //cout << "Okay, this building remains unowned." << endl;
            okay = false;
        } else {
            cout << "Invalid comand please try again: " << endl;
        }
    }
    cout << "Continue your turn: " << endl;
}

Building* Board::getBuilding(string Bname){
    int i;
    for (i = 0; i < vec_buildings.size(); ++i){
        if (vec_buildings[i]->getBName() == Bname){
            return vec_buildings[i].get();
        }
    }
    cout << Bname << " is not a valid building name" << endl;
    return nullptr;
}


void Board::pay(Player *whoOwes, int howMuchOwed, Player *toWhoOwed){
   string com;
   bool bankruptcyStatus = false;
   
   while (whoOwes->getMoney() < howMuchOwed && !(bankruptcyStatus)) { 
       cout << "You need to pay $" << howMuchOwed << ", please choose any of the following commands - trade <name> <give> <receive>, improve <property> sell, mortgage <property>, or bankrupt: " <<endl;
       while (!(cin >> com)){
           cout << "invalid command, please chose any of - trade <name> <give> <receive>, improve <property> sell, mortgage <property>, or bankrupt: //assets and all  " << endl; //declare bankruptcy??
       }
       if (com == "trade") { //trade <name> <give> <receive>
           string name;
           string give;
           string receive;
           cin >> name >> give >> receive;
           bool playerExists = false;
            for (int i = 0; i < vec_players_selected.size(); ++i){
                if (vec_players_selected[i]->getName() == name){
                    playerExists = true;
                    break;
                }
            }
            if (playerExists){
                trade(name, give, receive, whoOwes);
            } else {
                cout << name << " is not a valid player name in this game. " << endl;
            }
       } else if (com == "improve") { //improve <property> sell/buy
           string propertyName;
           string status;
           cin >> propertyName >> status;
           Building *b = getBuilding(propertyName);
           bool validStatus = false; 
            if (status == "buy" || status == "sell"){
                validStatus = true;
            }
            if (b && validStatus) {
                academicImprovements(b, status, whoOwes);
            }else {
                cout << "Incorrect input." << endl;
            }
            printBoard();
       } else if (com == "mortgage") { // mortgage <property>
           string propertyName;
           cin >> propertyName;
           Building *b = getBuilding(propertyName);
           if (b) {
               mortgage(b, whoOwes); //whoOwes is player who is doing the mortgaging
           } else {
            cout << "Incorrect property name. " << endl;
           }
       } else if (com == "bankrupt"){
           bankruptcyStatus = bankrupt(whoOwes, howMuchOwed, toWhoOwed); //maybe do a double check if they really want to bankrupt bc it is irreversible if it works
           if (bankruptcyStatus == true){
                break;
           }
           //break;
       } else if (com == "assets") {
            whoOwes->printAssests();
       } else if (com == "all"){
            int cttt = 0;
            vec_players_selected[getCurrPlayer()]->printAssests(); // extra feature: prints the player who called assets before everyone else
            while (cttt < vec_players_selected.size()){
                if (cttt != getCurrPlayer()){
                    vec_players_selected[cttt]->printAssests();
                }
                ++cttt;
            }
       } else if (com == "total"){
            cout << "If you were to sell all your improvements and mortgage all your properties, you would have: $" << whoOwes->total_worth() << endl;
       }
       else {
           cout << "not a valid choice, please chose any of - trade <name> <give> <receive>, improve <property> sell, mortgage <property>, or bankrupt: " << endl; //declare bankruptcy??
       }
   }
   if (bankruptcyStatus){
        if (vec_players_selected.size() == 1){
            return;
        }
        cout << "It was nice having you in the game, now it is " << vec_players_selected[currPlayer]->getName() <<  "'s turn." << endl;
   } else {
        if (toWhoOwed != nullptr){
            whoOwes->setMoney((howMuchOwed * -1)); // removes the money owed from the player who landed on the space
            toWhoOwed->setMoney(howMuchOwed); //pays the owner the money owed
        } else {
            whoOwes->setMoney((howMuchOwed * -1)); // removes the money owed from the player who landed on the space
        }
        cout << "You have enough money, the rent has been paid. Your current balance is: " << whoOwes->getMoney() << endl;
        if (whoOwes->getJailStatusNum() != 0){
            whoOwes->setJailStatusNum(0);
        }
   }
}

Player* Board::getOwner(Building *b){ //if there is no owner then will return nullptr
    for (int i = 0; i < vec_players_selected.size(); ++i){
        if (vec_players_selected[i]->properties.size() != 0){
            for (int j = 0; j < vec_players_selected[i]->properties.size(); ++j){
                if (b->getBPos() == vec_players_selected[i]->properties[j]->getBPos()){
                    return vec_players_selected[i].get();
                }
            }
        }
    }
    return nullptr;
}

void Board::setOwner(Building *b, Player *p) {
    for (int i = 0; i < p->properties.size(); ++i) {
        if (b->getBName() == p->properties[i]->getBName()) {
            cout << p->getName() << " already owns this building" <<endl;
            return;
        }
    }
    Ownable *o = static_cast<Ownable*>(b);
    p->addOwnable(o);
}


void Board::removeOwner(Building *b) {

    Player *removeOwnership = getOwner(b);
    for (int i = 0; i < removeOwnership->properties.size(); ++i) {
        if (b->getBName() == removeOwnership->properties[i]->getBName()) {
            removeOwnership->properties.erase(removeOwnership->properties.begin() + i);
        }
    }
}

void Board::addBuildingINIT(string Bname, string block, int improvements, int pos, int pur, int imp, size_t z, size_t o, size_t t, size_t thr, size_t f, size_t fiv){
   unique_ptr<Building> b;
   if (pos == 12 || pos == 28){ //gym
       b = make_unique<Gym>(Bname, pos);
   } else if (pos == 5 || pos == 15 || pos == 25 || pos == 35){ //res
       b = make_unique<Residence>(Bname, pos);
   } else if (pos == 0 || pos == 2 || pos == 4 || pos == 7 || pos == 10 || pos == 17 || pos == 20 || pos == 22 || pos == 30 || pos == 33 || pos == 36 || pos == 38){ //unownable
       b = make_unique<Unownable>(Bname, pos);
   } else {
       unique_ptr<vector<size_t>> v = make_unique<vector<size_t>>(initializer_list<size_t>{z, o, t, thr, f, fiv});
       b = make_unique<Academic>(Bname, pos, 0, block, move(v), pur, imp, false);
   }
   vec_buildings.emplace_back(move(b)); //no access to board
}


void Board::squareProcessing(int sum_of_roll, bool fair_dice){
    int pos = vec_players_selected[getCurrPlayer()]->getPos();
    cout << "You landed on: " << vec_buildings[pos]->getBName() << endl;
    if (vec_buildings[pos]->getOwnableStatus()){ //means is an owneable building
        //check owenrship
        if (getOwner(vec_buildings[pos].get())){ //has an owner
            if(getOwner(vec_buildings[pos].get())->getName() == vec_players_selected[getCurrPlayer()]->getName()){ //owner by this player
                cout << "You own this property, nice!" << endl;
            } else { //owned by other player
                if (static_cast<Ownable*>(vec_buildings[pos].get())->getMortgageState() == false){
                    int owed = moneyOwed(vec_buildings[pos].get(), sum_of_roll);
                    cout << "This buliding is owned, please pay $" << owed << endl;
                    if (vec_players_selected[getCurrPlayer()]->getMoney() >= owed){ //moneyOwed is the owneable building's rent/tuiton (with monopoly and/or improvements IF ITS ACADEMIC etc) (moneyOwed will check if it is a RES or GYM - maybe consider adding a bool in buildings)
                        vec_players_selected[getCurrPlayer()]->setMoney((owed * -1)); // removes the money owed from the player who landed on the space
                        getOwner(vec_buildings[pos].get())->setMoney(owed); //pays thea owner the money owed
                        cout << "You have enough money, the rent has been paid. Your current balance is: $" << vec_players_selected[getCurrPlayer()]->getMoney() << endl;
                    } else {
                        pay(vec_players_selected[getCurrPlayer()].get(), owed, getOwner(vec_buildings[pos].get()));
                    }
                } else {
                    cout << "This building is mortgaged, no rent needs to be paid." << endl;
                }
            } 
        } else {
            //unowned (owner is nullptr) !!!
            cout << "This property costs $" << static_cast<Ownable*>(vec_buildings[vec_players_selected[getCurrPlayer()]->getPos()].get())->getCost() << " would you like to buy this property?: [YES or NO] " << endl;
            string ans;
            cin >> ans;
            bool temp = true;
            while(temp){
                if (ans == "YES"){
                    if (vec_players_selected[getCurrPlayer()]->getMoney() < static_cast<Ownable*>(vec_buildings[vec_players_selected[getCurrPlayer()]->getPos()].get())->getCost()){
                        cout << "You do not have enough money to get this building. Continue your turn: " << endl;
                    } else {
                        vec_players_selected[getCurrPlayer()]->setMoney((static_cast<Ownable*>(vec_buildings[vec_players_selected[getCurrPlayer()]->getPos()].get())->getCost() * -1)); //removes the money from the player who bought it
                        setOwner(vec_buildings[vec_players_selected[getCurrPlayer()]->getPos()].get(), vec_players_selected[getCurrPlayer()].get()); //sets the player to be the owner of the building
                        cout << "You bought this property, nice! You can continue your turn: " << endl;
                    }
                    temp = false;
                } else if (ans == "NO") {
                    auction(vec_buildings[vec_players_selected[getCurrPlayer()]->getPos()].get());
                    temp = false;
                } else {
                    cout << "Invalid choice, please enter again: " << endl;
                    cin >> ans;
                }
            }
        }                    
    } else { //unowneable properties
        bool slc = false;
        bool sentToLine = false;
        if (vec_players_selected[getCurrPlayer()]->getPos() == 2 || vec_players_selected[getCurrPlayer()]->getPos() == 17 || vec_players_selected[getCurrPlayer()]->getPos() == 33){ //means landed on SLC
            slc = true;
        }
        if (slc){
            stateOfBoardChange(); 
            printBoard(); 
        }
        if (vec_players_selected[getCurrPlayer()]->getPos() == 30) {
            sentToLine = true;
        }
        int trigger;
        trigger = static_cast<Unownable*>(vec_buildings[vec_players_selected[getCurrPlayer()]->getPos()].get())->triggerEvent(*vec_players_selected[getCurrPlayer()], fair_dice);
        if (trigger != 0 ){
            if (trigger <= 12 && trigger >=2){
                cout << "WOULD MEAN IN JAIL, SHOULD NOT GET THIS MESSAGE" << endl;
            } else {
                pay(vec_players_selected[getCurrPlayer()].get(), trigger, nullptr);
            }
        }
        if (sentToLine){
            stateOfBoardChange(); 
            printBoard(); 
            cout << "You can continue your turn, but you are in line and can't roll. Enter your next command: " << endl;
        }
        if (slc){
            stateOfBoardChange();
            printBoard(); 
            squareProcessing(sum_of_roll, fair_dice);
        } 
    }
}


void Board::reset() {
    vec_buildings.clear();
}

