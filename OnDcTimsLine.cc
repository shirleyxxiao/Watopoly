#include "OnDcTimsLine.h"
// #include "observer.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <memory>

using namespace std;

int OnDcTimsLine::execute(Player& player, bool fairDice) { //will return 0 if player doesnt leave the line, will return 50 if need to pay 50 but not enough money, will return a num 2-12 if left line(not neccesarly doubles) and need to move
    if (player.ifInJail()){     
        cout << "Your " << player.timesInJail() + 1 << " attempt to leave the line" << endl; 
        if (player.timesInJail() == 2){
            size_t steps;
            int cannotAfford;
            if (player.cups() > 0){
                char response;
                while (true){
                    std::cout << "Choose a way to leave the line: Roll dices (r), Pay $50 (p), Use a Roll UP the Rim Cup (c)" << std::endl;
                    std::cin >> response;
                    switch (response) {
                        case 'r': 
                            steps = player.rollDouble(fairDice);
                            if (steps <= 12){
                                player.move(steps, true);
                                player.setFree();
                                std::cout << "You leave the line!" << std::endl;
                                return steps;
                            } else {
                                std::cout << "Choose a way to leave the line: Pay $50 (p), Use a Roll UP the Rim Cup (c)" << std::endl;
                                std::cin >> response;
                                while (true){
                                    switch (response) {
                                        case 'p': 
                                            cannotAfford = player.loseMoney(50);
                                            if (cannotAfford == 50){
                                                cout << "Oops! You cannot afford to leave the line!" << endl;
                                                return 50;
                                            } else {
                                                player.move(steps - 12, true);
                                                player.setFree();
                                                std::cout << "You leave the line!" << std::endl;
                                                return steps - 12;
                                            }
                                            break;
                                        case 'c': 
                                            player.loseCup();
                                            activeCups -= 1;
                                            player.move(steps - 12, true);
                                            player.setFree();
                                            std::cout << "You leave the line!" << std::endl;
                                            return steps - 12;
                                            break;
                                        default:
                                            std::cout << "Invalid input!" << std::endl;
                                            std::cout << "Choose a way to leave the line: Pay $50 (p), Use a Roll UP the Rim Cup (c)" << std::endl;
                                            std::cin >> response;
                                            continue;
                                    }
                                }
                            }
                            break;
                        case 'p': 
                            cannotAfford = player.loseMoney(50);
                            if (cannotAfford == 50){
                                cout << "Oops! You cannot afford to leave the line!" << endl;
                                return 50;
                            }
                            steps = player.rollDice(fairDice);
                            player.move(steps, true);
                            player.setFree();
                            std::cout << "You leave the line!" << std::endl;
                            return steps;
                            break;
                        case 'c': 
                            player.loseCup();
                            activeCups -= 1;
                            steps = player.rollDice(fairDice);
                            player.move(steps, true);
                            player.setFree();
                            std::cout << "You leave the line!" << std::endl;
                            return steps;
                            break;
                        default:
                            std::cout << "Invalid input!" << std::endl;
                            continue;
                    }
                    break;
                }
            } else {
                char response;
                while (true){
                    std::cout << "Choose a way to leave the line: Roll dices (r), Pay $50 (p)" << std::endl;
                    std::cin >> response;
                    switch (response) {
                        case 'r': 
                            steps = player.rollDouble(fairDice);
                            if (steps <= 12){
                                player.move(steps, true);
                                player.setFree();
                                std::cout << "You leave the line!" << std::endl;
                                return steps;
                            } else {
                                std::cout << "You have to pay $50 to leave the line!" << std::endl;
                                cannotAfford = player.loseMoney(50);
                                if (cannotAfford == 50){
                                    cout << "Oops! You cannot afford to leave the line!" << endl;
                                    return 50;
                                } else {
                                    player.move(steps - 12, true);
                                    player.setFree();
                                    std::cout << "You leave the line!" << std::endl;
                                    return steps - 12;
                                }
                            }
                            break;
                        case 'p': 
                            cannotAfford = player.loseMoney(50);
                            if (cannotAfford == 50){
                                cout << "Oops! You cannot afford to leave the line!" << endl;
                                return 50;
                            }
                            steps = player.rollDice(fairDice);
                            player.move(steps, true);
                            player.setFree();
                            std::cout << "You leave the line!" << std::endl;
                            return steps;
                            break;
                        default:
                            std::cout << "Invalid input!" << std::endl;
                            continue;
                    }
                    break;
                }
            } 
        } else {
            size_t steps;
            int cannotAfford;
            if (player.cups() > 0){
                char response;
                while (true){
                    std::cout << "Choose a way to leave the line: Roll dices (r), Pay $50 (p), Use a Roll UP the Rim Cup (c)" << std::endl;
                    std::cin >> response;
                    switch (response) {
                        case 'r': 
                            steps = player.rollDouble(fairDice);
                            if (steps <= 12){
                                player.move(steps, true);
                                player.setFree();
                                std::cout << "You leave the line!" << std::endl;
                                return steps;
                            } else {
                                player.incJailTurn();
                                std::cout << "Failed to leave the line!" << std::endl;
                                return 0;
                            }
                            break;
                        case 'p': 
                            cannotAfford = player.loseMoney(50);
                            if (cannotAfford == 50){
                                cout << "Oops! You cannot afford to leave the line!" << endl;
                                return 50;
                            }
                            steps = player.rollDice(fairDice);
                            player.move(steps, true);
                            player.setFree();
                            std::cout << "You leave the line!" << std::endl;
                            return steps;
                            break;
                        case 'c': 
                            player.loseCup();
                            steps = player.rollDice(fairDice);
                            player.move(steps, true);
                            player.setFree();
                            std::cout << "You leave the line!" << std::endl;
                            return steps;
                            break;
                        default:
                            std::cout << "Invalid input!" << std::endl;
                            continue;
                    }
                    break;
                }
            } else {
                char response;
                while (true){
                    std::cout << "Choose a way to leave the line: Roll dices (r), Pay $50 (p)" << std::endl;
                    std::cin >> response;
                    switch (response) {
                        case 'r': 
                            steps = player.rollDouble(fairDice);
                            if (steps <= 12){
                                player.move(steps, true);
                                player.setFree();
                                std::cout << "You leave the line!" << std::endl;
                                return steps;
                            } else {
                                player.incJailTurn();
                                std::cout << "Failed to leave the line!" << std::endl;
                                return 0;
                            }
                            break;
                        case 'p': 
                            cannotAfford = player.loseMoney(50);
                            if (cannotAfford == 50){
                                cout << "Oops! You cannot afford to leave the line!" << endl;
                                return 50;
                            }
                            std::cout << "You leave the line!" << std::endl;
                            steps = player.rollDice(fairDice);
                            player.move(steps, true);
                            player.setFree();
                            
                            return steps;
                            break;
                        default:
                            std::cout << "Invalid input!" << std::endl;
                            continue;
                    }
                    break;
                }
            } 
        }
    } else {
        cout << "You are not in Line! You can continue!" << endl;
        return 0;
    }
}
