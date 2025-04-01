#ifndef MOVE_FORWARD_H
#define MOVE_FORWARD_H

#include "Event.h"
#include "Player.h"
#include "prng.h"

#include <cstddef> // Defines size_t
#include <iostream>
#include <string>
#include <vector>


class MoveForward : public Event {
    int spaces;
    public:
        MoveForward(int spaces);
        int execute(Player& player, bool fairDice) override;
};

#endif
