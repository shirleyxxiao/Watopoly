#include "LoseMoney.h"
// #include "observer.h"
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <memory>
#include <ctime>
#include <cstdint>
using namespace std;

LoseMoney::LoseMoney(int amount) : amount(amount) {}

int LoseMoney::execute(Player& player, bool fairDice) {
    if (activeCups < totalCups){
        // PRNG prng(12345);  // Initialize PRNG with a seed
        // PRNG prng;
        PRNG prng(static_cast<std::uint32_t>(std::time(0)));  // Seed with current time
        std::uint32_t randomCup = prng(99);  // Generate a random number in [0,99]
        if (randomCup == 0){
            activeCups += 1;
            player.winCup();
            cout << "You win a cup!" << endl;
        }
    }
    cout << "Lose money: $" << amount << endl;
    return player.loseMoney(amount); //if enough money will return 0, else will return the amount needed to pay 
}

