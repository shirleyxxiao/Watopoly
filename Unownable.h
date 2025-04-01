#ifndef UNOWNABLE_H
#define UNOWNABLE_H

#include "Player.h"
#include "Event.h"
#include "OnDcTimsLine.h"
#include "EventFactory.h"
#include "building.h"

#include <cstddef> // Defines size_t
#include <iostream>
#include <string>
#include <memory>



class Unownable : public Building {

  public:
    Unownable(std::string BName, size_t pos);
    void printLongName(int lineNum);
    int triggerEvent(Player& player, bool fairDice);
    virtual void printName() override;
    virtual void printLine(int lineNum) override;

};

#endif
