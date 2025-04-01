#ifndef ON_DC_TIMS_LINE_H
#define ON_DC_TIMS_LINE_H

#include "Event.h"
#include "Player.h"
#include "prng.h"

#include <cstddef> // Defines size_t
#include <iostream>
#include <string>
#include <vector>


class OnDcTimsLine : public Event {
    public:
        int execute(Player& player, bool fairDice) override;
};

#endif
