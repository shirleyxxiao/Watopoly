#include "Board.h"
#include "Player.h"
#include "building.h"
#include "ownable.h"
#include "Unownable.h"
#include "gym.h"
#include "residence.h"
#include "academic.h"
#include "subject.h"
#include "observer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <map> 
#include <ctime>
using namespace std;

bool fair_dice = true;
bool load_game = false;

const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string RESET = "\033[0m"; // Reset to default color

void setBuildings(Board *B){
   B->reset();
   ifstream f("buildings.txt"); //all 40
   if (!f.is_open()){
       cout << "invalid file name." << endl;
   } else {
       string line;
       int pos = 0;
       string Bname;
       string block;
       int improvements, pur, imp, z, o, t, thr, fo, fiv;
       while (getline(f, line)){
           if (pos == 12 || pos == 28 || pos == 5 || pos == 15 || pos == 25 || pos == 35 || pos == 0 || pos == 2 || pos == 4 || pos == 7 || pos == 10 || pos == 17 || pos == 20 || pos == 22 || pos == 30 || pos == 33 || pos == 36 || pos == 38){
               B->addBuildingINIT(line, " ", 0, pos, 0,0,0,0,0,0,0,0);
           }else {
               istringstream iss(line);
               iss >> Bname >> block >> pur >> imp >> z >> o >> t >> thr >> fo >> fiv;
               B->addBuildingINIT(Bname, block, 0, pos, pur, imp, z, o, t, thr, fo, fiv);
           }
           ++pos;
       }
   }
   f.close();
}


void DiceRoll(vector<int> *v){
   srand(time(0));
   int dice1 = rand() % 6 + 1;
   cout << "Dice 1: " << dice1 << endl;
   int dice2 = rand() % 6 + 1;
   cout << "Dice 2: " << dice2 << endl;
   v->emplace_back(dice1);
   v->emplace_back(dice2);
}


void selectPlayers(int numPlayers, Board *b){
   if (load_game == false){
       cout << "Character select! Please choose your character, here are the options: <Name> <Char>" << endl;
       cout << BLUE << "---------------------------------------------------------------------------------------------------\n";
       cout << "| Name | Goose | GRT Bus | Tim Hortons Doughnut | Professor | Student | Money | Laptop | Pink Tie |\n";
       cout << "---------------------------------------------------------------------------------------------------\n";
       cout << "| Char |   G   |    B    |           D          |     P     |    S    |   $   |    L   |    T     |\n";
       cout << "---------------------------------------------------------------------------------------------------\n" << RESET;
  
       map<char,string> m {{'G', "Goose"}, {'B', "Bo"}, {'D', "Do"}, {'P', "Prof"}, {'S', "Stu"}, {'$', "Mon"}, {'L', "Laptop"}, {'T', "Pink"}};

       int ct = 0;
       string name;
       char chara;
       while (ct < numPlayers){
           cin.clear();
           cin.ignore();
           while (!(cin >> name)){
               cout << "Invalid input, please try again: " << endl;
           }
           cout << "Welcome, " << name << "!" << endl;
           while (true){   
               bool duplicate = false;
               while (!(cin >> chara)){
                   cout << "Invalid input, please try again: " << endl;
               }
               for (int i = 0; i < ct; ++i){ //need to check if the chara is already used
                   if (b->vec_players_selected[i]->getAcronym() == chara){
                       cout << "This token is already taken, please choose again: <Char>" << endl;
                       duplicate = true;
                       break;
                   }
               }
               if (!duplicate){
                   break;
               }
           }
           if (m.find(chara) == m.end()){ //not found
               cout << "Way to be unique! Your token is represented by: " << chara << endl;
           } else {
               cout << "Your token is represented by: " << chara << endl;
          }
           unique_ptr<Player> p = make_unique<Player>(name, chara, 0, 1500, 0, 0, 0);
           m.erase(chara);
           b->vec_players_selected.emplace_back(move(p));
           ++ct;
           cout << "You chose: " << b->vec_players_selected[ct-1]->getName() << " " << b->vec_players_selected[ct-1]->getAcronym() << endl;
       }
   }
}


bool loadGame(string filename, Board *B){ //need to have info on ownable buildings to implement
   ifstream f(filename);
   if (!f.is_open()){
       return false;
   } else {
       string line;
       int n;
       getline(f,line);
       istringstream iss(line);
       iss >> n;
       while (n > 0){
           getline(f, line);
           istringstream iss(line);
           string player1;
           char c;
           int TimsCups;
           int money;
           int position;
           int jail = 0;
           int turns = 0;
           iss >> player1 >> c >> TimsCups >> money >> position;
           if (position == 10){
               iss >> jail;
               if (jail == 1) {
                   iss >> turns;
               }
           }
           unique_ptr<Player> p = make_unique<Player>(player1, c, TimsCups, money, position, jail, turns);
           B->vec_players_selected.emplace_back(move(p));
           --n;
       } //added all the players
        cout << endl;
        cout << "WELCOME TO " << endl;
        cout << endl;
        cout << RED << "W   W   AAA   TTTTT   OOO   PPPP    OOO   L      Y   Y  " << endl;
        cout << "W   W  A   A    T    O   O  P   P  O   O  L       Y Y   " << endl;
        cout << "W W W  AAAAA    T    O   O  PPPP   O   O  L        Y    " << endl;
        cout << "WW WW  A   A    T    O   O  P      O   O  L        Y    " << endl;
        cout << "W   W  A   A    T     OOO   P       OOO   LLLLL    Y    " << RESET <<  endl;
        cout << endl;
        cout << "All the players have been added!" << endl;
       string buildingName;
       string owner;
       int improvements;
       while (getline(f, line)){
           istringstream iss(line);
           iss >> buildingName >> owner >> improvements;
           for (int i = 0; i < B->vec_buildings.size(); ++i){
               if (B->vec_buildings[i]->getBName() == buildingName){
                    if (improvements == -1){
                        (static_cast<Ownable*>(B->vec_buildings[i].get()))->setMortgageState(true);
                        if ((static_cast<Ownable*>(B->vec_buildings[i].get()))->getBType() == 'A'){
                            static_cast<Academic*>(B->vec_buildings[i].get())->setImprovments(0);
                        }
                    }
                    if ((static_cast<Ownable*>(B->vec_buildings[i].get()))->getBType() == 'A'){
                        if (improvements != -1){
                            static_cast<Academic*>(B->vec_buildings[i].get())->setImprovments(improvements);
                        }
                    }
                   if (owner != "BANK"){
                       for (int j = 0; j < B->getNumPlayers(); ++j){
                           if (B->vec_players_selected[j]->getName() == owner){
                               B->vec_buildings[i]->setOwnable(true);
                               B->setOwner(B->vec_buildings[i].get(), B->vec_players_selected[j].get());
                               break;
                           }
                       }
                   }
                   break;
               }
           }
       }
       f.close();
   }
   return true;
}


int main(int argc, char* argv[]){
    try {
        Board boardMain;
        boardMain.reset(); 
        setBuildings(&boardMain); //initializes all buildings
        if (argc > 1 ) {
            int ct = 1;
            while (ct < argc) {
                string argCommand = argv[ct];
                if (argCommand == "-load") { 
                    ++ct;
                    argCommand = argv[ct];
                    string filename = argCommand;
                    if (loadGame(filename, &boardMain)) {//get info from the file
                        //cout << boardMain.getNumPlayers() << endl;
                    } else {
                        cout << "invalid filename, exiting program" << endl;
                        return 0; //exit program
                    }
                    load_game = true;
                    ++ct;
                } else if (argCommand == "-testing"){
                    //switch boolean to start calling the testing dice not the regular dice;
                    fair_dice = false;
                    ++ct;
                } else {
                    cout << "not valid argument line command. Exiting." << endl;
                    ++ct; 
                    return 0;
                }
            }     
        } 
        if (load_game == false) {
            cout << "Hello!! Welcome to " << endl;
            cout << endl;
            cout << RED << "W   W   AAA   TTTTT   OOO   PPPP    OOO   L      Y   Y  " << endl;
            cout << "W   W  A   A    T    O   O  P   P  O   O  L       Y Y   " << endl;
            cout << "W W W  AAAAA    T    O   O  PPPP   O   O  L        Y    " << endl;
            cout << "WW WW  A   A    T    O   O  P      O   O  L        Y    " << endl;
            cout << "W   W  A   A    T     OOO   P       OOO   LLLLL    Y    " << RESET <<  endl;

            cout << endl;
            cout << "Please enter the number of players (between 2 and 6): " << endl;
            int n; //numPlayers
            while(!(cin >> n) || n < 2 || n > 6) {
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore();
                    cout << "Thats not a number please enter a valid number between 2 and 6: " << endl;
                } else {
                    if (n < 2){
                        cout << "Cannot have less than two players, please enter again: " << endl;
                    }
                    if (n > 6){
                        cout << "Cannot have more than six players, please enter again: " << endl;
                    }
                }
            }
            // n is numer of players
            selectPlayers(n, &boardMain);
            
        }// else for the player selection
        cout << MAGENTA << "****The players chosen are:****" << RESET << endl;
        for (int i = 0; i < boardMain.getNumPlayers(); ++i){
            cout << i << ".         " << boardMain.vec_players_selected[i]->getName() << " " << boardMain.vec_players_selected[i]->getAcronym() << endl;
        }
        cout << MAGENTA << "*******************************" << RESET << endl;
        cout << "It is now " << boardMain.vec_players_selected[boardMain.getCurrPlayer()]->getName() << "'s turn!" << endl;
        bool didntRoll = true;
        string command;
        while (cin >> command){
            if (boardMain.vec_players_selected.size() == 1){ // indicates end of game
                cout << "Congratulations " << boardMain.vec_players_selected[0]->getName() << "!! You have won the game and dominated Watopoly, thank you for playing:)" << endl;
                cout << "Game made by: Sasha Boruk, Shirley Xiao, and Jiayi Zhao. 2025" << endl;
                cout << "*************************************************************" << endl;
                boardMain.reset();
                return 0;
            }
           
            cout << "You entered: " << command << endl; 
            if (command == "roll" && didntRoll && boardMain.vec_players_selected[boardMain.getCurrPlayer()]->getJailStatusNum() == 0){ 
                int sum_of_roll = 0;
                vector<int> v;
                    if (fair_dice){
                        DiceRoll(&v);
                        sum_of_roll = v[0] + v[1];
                        if (v[0] == v[1]) { //if rolled doubles, can roll again
                            didntRoll = true;
                        } else {
                            didntRoll = false;
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
                        sum_of_roll = x + y;
                        if (x == y) { //if rolled doubles, can roll again
                            didntRoll = true;
                        } else {
                            didntRoll = false;
                        }
                    }
                cout << "your dice sum is: " << sum_of_roll << endl;
                boardMain.vec_players_selected[boardMain.getCurrPlayer()]->setPos(sum_of_roll); //updates the player position
                
                if (boardMain.vec_players_selected[boardMain.getCurrPlayer()]->getPos() >= 40){ 
                    boardMain.vec_players_selected[boardMain.getCurrPlayer()]->setPos(-40);
                }
                cout << "new position: " << boardMain.vec_players_selected[boardMain.getCurrPlayer()]->getPos() << endl;
                boardMain.stateOfBoardChange(); 
                boardMain.printBoard(); 
                
                boardMain.squareProcessing(sum_of_roll, fair_dice);
                //didntRoll = false;
            } else if (command == "save"){ // save <filename>
                boardMain.stateOfBoardChange(); 
                string filename;
                cin >> filename;
                while (filename == "") {
                    cout << "Not a valid filename, please input the filename again: " << endl;
                    cin >> filename;
                } 
                ofstream f{filename};
                f << boardMain.vec_players_selected.size() << endl; 
                for (int i = 0; i < boardMain.vec_players_selected.size(); ++i){
                    f << boardMain.vec_players_selected[i]->getName() << " " << boardMain.vec_players_selected[i]->getAcronym() << " " << boardMain.vec_players_selected[i]->getRimCups() << " " << boardMain.vec_players_selected[i]->getMoney() << " " << boardMain.vec_players_selected[i]->getPos();
                    if (boardMain.vec_players_selected[i]->getPos() == 10){
                        if (boardMain.vec_players_selected[i]->getJailStatusNum() != 0){
                            f << " " << 1 << " " << boardMain.vec_players_selected[i]->getJailTurns();
                        } else {
                            f << " " << 0;
                        }
                    }
                    f << endl;
                }
                for (int i = 0; i < boardMain.vec_buildings.size(); ++i){
                    if (i != 0 && i != 2 && i != 4 && i != 7 && i != 10 && i != 17 && i != 20 && i != 22 && i != 30 && i != 33 && i != 36 && i != 38){
                        f << boardMain.vec_buildings[i]->getBName() << " ";
                        if (boardMain.getOwner(boardMain.vec_buildings[i].get())){
                            f << boardMain.getOwner(boardMain.vec_buildings[i].get())->getName();
                        } else{
                            f << "BANK";
                        }
                        if (static_cast<Ownable*>(boardMain.vec_buildings[i].get())->getBType() == 'A'){
                            if (static_cast<Ownable*>(boardMain.vec_buildings[i].get())->getMortgageState() == true){
                                f << " " << -1;
                            } else {
                                f << " " << static_cast<Academic*>(boardMain.vec_buildings[i].get())->getLevel();
                            }
                        } else {
                            if (static_cast<Ownable*>(boardMain.vec_buildings[i].get())->getMortgageState() == true){
                                f << " " << -1;
                            } else {
                                f << " " << 0;
                            }
                        }
                        if (i != boardMain.vec_buildings.size() - 1){
                            f << endl;
                        }
                    }
                }
                f.close();
            } else if (command == "next"){ // next
                
                int numPlayers = boardMain.getNumPlayers();
                boardMain.setCurrPlayer(boardMain.getCurrPlayer() + 1); 
                if (boardMain.getCurrPlayer() > (numPlayers - 1)){ //gives turn back to the first player after the last player calls "next"
                    boardMain.setCurrPlayer(0);
                }
                if (boardMain.vec_players_selected.size() == 1){ // indicates end of game
                    cout << "Congratulations " << boardMain.vec_players_selected[0]->getName() << "!! You have won the game and dominated Watopoly, thank you for playing:)" << endl;
                    cout << "Game made by: Sasha Boruk, Shirley Xiao, and Jiayi Zhao. 2025" << endl;
                    boardMain.reset();
                    return 0;
                } else {
                    cout << "It is now " << boardMain.vec_players_selected[boardMain.getCurrPlayer()]->getName() << "'s turn!" << endl;
                    if (boardMain.vec_players_selected[boardMain.getCurrPlayer()]->getJailStatusNum() != 0){ //player in jail
                        int jail_return_num;
                        jail_return_num = static_cast<Unownable*>(boardMain.vec_buildings[boardMain.vec_players_selected[boardMain.getCurrPlayer()]->getPos()].get())->triggerEvent(*boardMain.vec_players_selected[boardMain.getCurrPlayer()], fair_dice);
                        if (jail_return_num == 0){
                            cout << "You can continue your turn, but you are in line and can't roll. Enter your next command: " << endl;
                        } 
                        if (jail_return_num >= 2 && jail_return_num <= 12){ //player left jail and moved that many 
                            boardMain.squareProcessing(jail_return_num, fair_dice);
                        }
                        if (jail_return_num == 50) { // player cannot pay $50 to exit 
                            boardMain.pay(boardMain.vec_players_selected[boardMain.getCurrPlayer()].get(), 50, nullptr);
                        }
                        if (boardMain.vec_players_selected.size() == 1){ // indicates end of game
                            cout << "Congratulations " << boardMain.vec_players_selected[0]->getName() << "!! You have won the game and dominated Watopoly, thank you for playing:)" << endl;
                            cout << "Game made by: Sasha Boruk, Shirley Xiao, and Jiayi Zhao. 2025" << endl;
                            boardMain.reset();
                            return 0;
                        }
                        if (boardMain.vec_players_selected[boardMain.getCurrPlayer()]->getJailStatusNum() == 0){ //not in jail anymore
                            boardMain.stateOfBoardChange();
                            boardMain.printBoard();   
                            cout << "You can continue your turn: " << endl; 
                        }
                    } 
                }
                didntRoll = true;
            }else if (command == "trade"){ // trade <name> <give> <receive>
                string name, give, receive;
                cin >> name >> give >> receive;
                bool playerExists = false;
                for (int i = 0; i < boardMain.vec_players_selected.size(); ++i){
                    if (boardMain.vec_players_selected[i]->getName() == name){
                        playerExists = true;
                        break;
                    }
                }
                if (playerExists){
                    boardMain.trade(name, give, receive, boardMain.vec_players_selected[boardMain.getCurrPlayer()].get());
                } else {
                    cout << name << " is not a valid player name in this game. Continue your turn: " << endl;
                }
            }else if (command == "improve"){ // improve <property> buy/sell
                string propertyName,status;
                cin >> propertyName >> status;
                bool validStatus = false; 
                if (status == "buy" || status == "sell"){
                    validStatus = true;
                }
                Building *b = boardMain.getBuilding(propertyName);
                if (b && validStatus) {
                    boardMain.academicImprovements(b, status, boardMain.vec_players_selected[boardMain.getCurrPlayer()].get());
                } else {
                    cout << "Incorrect input, continue your turn: " << endl;
                }
                boardMain.printBoard();
            }else if (command == "mortgage"){ // mortgage <property>
                string propertyName;
                cin >> propertyName;
                Building *b = boardMain.getBuilding(propertyName);
                if (b) {
                    boardMain.mortgage(b, boardMain.vec_players_selected[boardMain.getCurrPlayer()].get());
                }else {
                    cout << "Incorrect building name, continue your turn: " << endl;
                }
            } else if (command == "bankrupt"){
                cout << "You currently do not need to pay more money than you have, this is not a valid command please enter again: " << endl;
            } else if (command == "unmortgage"){ // unmortgage <property>
                string propertyName;
                cin >> propertyName;
                Building *b = boardMain.getBuilding(propertyName);
                if (b) {
                    boardMain.unmortgage(b, boardMain.vec_players_selected[boardMain.getCurrPlayer()].get());
                }else {
                    cout << "Incorrect building name, continue your turn: " << endl;
                }
            } else if (command == "assets"){ // assets
                boardMain.vec_players_selected[boardMain.getCurrPlayer()]->printAssests();
            } else if (command == "all"){ // all
                int cttt = 0;
                boardMain.vec_players_selected[boardMain.getCurrPlayer()]->printAssests(); // extra feature: prints the player who called assets before everyone else
                while (cttt < boardMain.vec_players_selected.size()){
                    if (cttt != boardMain.getCurrPlayer()){
                        boardMain.vec_players_selected[cttt]->printAssests();
                    }
                    ++cttt;
                }
            } else if (command == "print"){
                boardMain.stateOfBoardChange();
                boardMain.printBoard();          
            }else if (command == "total"){
                cout << "If you were to sell all your improvements and mortgage all your properties, you would have: $" << boardMain.vec_players_selected[boardMain.getCurrPlayer()]->total_worth() << endl;
            } else if (command == "roll" && didntRoll == false){ //NEED TO ADD CASE WHEN ROLLING DOUBLES
                if (fair_dice == false){
                    int x;
                    int y;
                    cin >> x >> y;
                }
                cout << "You have already rolled, please try another command: " << endl;
            } else if (command == "roll" && boardMain.vec_players_selected[boardMain.getCurrPlayer()]->getJailStatusNum() != 0){
                if (fair_dice == false){
                    int x;
                    int y;
                    cin >> x >> y;
                }
                cout << "You are in Line, you cannot move. Enter again." << endl;
            } else {
                cout << "Not a valid command, please try again: " << endl;
            }
        } // while
    } catch (...){
        cerr << "Invalid input, please check your spelling." << endl;
        return 0;
    }
}
