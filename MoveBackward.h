#ifndef MOVE_BACKWARD_H
#define MOVE_BACKWARD_H

#include "Event.h"
#include "Player.h"
#include "prng.h"

#include <cstddef> // Defines size_t
#include <iostream>
#include <string>
#include <vector>

class MoveBackward : public Event {
    int spaces;
    public:
        MoveBackward(int spaces);
        int execute(Player& player, bool fairDice) override;
};

#endif
