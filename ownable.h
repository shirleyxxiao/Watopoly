#ifndef OWNABLE_H
#define OWNABLE_H

#include "building.h"

#include <cstddef> // Defines size_t
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Ownable: public Building {
    int propertyCost;
    bool isMortgaged;

    public:        
        Ownable( string name, size_t blockPosition, bool isOwnable, int propertyCost );
        virtual ~Ownable() override = default; 
        int getCost() const; 
        bool getMortgageState() const;
        void setMortgageState( bool mortgage );
        virtual char getBType() const = 0;
        virtual void printName() override;
        virtual void printLine(int lineNum) override;  
};

#endif
