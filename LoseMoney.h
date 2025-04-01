#ifndef LOSE_MONEY_H
#define LOSE_MONEY_H

#include "Event.h"
#include "Player.h"
#include "prng.h"

#include <cstddef> // Defines size_t
#include <iostream>
#include <string>
#include <vector>

// #include "observer.h"
// #include "info.h"


class LoseMoney : public Event {
    int amount;
    public:
        LoseMoney(int amount);
        int execute(Player& player, bool fairDice) override;
};

#endif
