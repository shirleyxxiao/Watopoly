#ifndef GYM_H
#define GYM_H

#include "ownable.h"
#include "building.h"

#include <cstddef> // Defines size_t
#include <iostream>
#include <string>

using namespace std;

class Gym: public Ownable {
    
    public:
        Gym(string name, size_t blockPosition);
        int usageFee(int diceSum, int numGymOwner);
        char getBType() const override;

        ~Gym() override = default;
        virtual void printName() override;
        virtual void printLine(int lineNum) override;

};

#endif
