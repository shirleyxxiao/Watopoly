#ifndef EVENT_H
#define EVENT_H

#include "Player.h"
#include "prng.h"

#include <cstddef> // Defines size_t
#include <cstdint>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

class Event {
    protected:
        const int totalCups = 4;
        int activeCups = 0;

    public:
        virtual int execute(Player& player, bool fairDice) = 0;  // Abstract method to execute event effect
        virtual ~Event() = default;
};

#endif
