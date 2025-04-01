#ifndef GOTO_COLLECT_OSAP_H
#define GOTO_COLLECT_OSAP_H

#include "Event.h"
#include "Player.h"
#include "prng.h"

#include <cstddef> // Defines size_t
#include <iostream>
#include <string>
#include <vector>


class GoToCollectOSAP : public Event {
    public:
        int execute(Player& player, bool fairDice) override;
};

#endif
