#ifndef CAUGHTBYTIMS_H
#define CAUGHTBYTIMS_H

#include "Event.h"
#include "Player.h"
#include "prng.h"

#include <cstddef> // Defines size_t
#include <iostream>
#include <string>
#include <vector>

// #include "observer.h"
// #include "info.h"


class CaughtByTims : public Event {
    public:
        int execute(Player& player, bool fairDice) override;
};

#endif
