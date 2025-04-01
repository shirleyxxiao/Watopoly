#ifndef GAINMONEY_H
#define GAINMONEY_H

#include "Event.h"
#include "Player.h"
#include "prng.h"

#include <cstddef> // Defines size_t
#include <iostream>
#include <string>
#include <vector>



class GainMoney : public Event {
    int amount;
    public:
        GainMoney(int amount);
        int execute(Player& player, bool fairDice) override;
};

#endif
