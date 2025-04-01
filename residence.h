#ifndef RESIDENCE_H
#define RESIDENCE_H

#include "ownable.h"

#include <cstddef>
#include <iostream>
#include <string>

using namespace std;

class Residence: public Ownable {

    public:
        Residence(string name, size_t blockPosition);
        ~Residence() override = default;
        int calcResCost(int ownedNum);
        char getBType() const override;
        virtual void printName() override;
        virtual void printLine(int lineNum) override;
};

#endif
