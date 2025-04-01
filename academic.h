#ifndef ACADEMIC_H
#define ACADEMIC_H

#include "ownable.h"

#include <cstddef> 
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Academic: public Ownable {
    
    size_t improvementLevel;
    string monopolyBlock;
    unique_ptr<vector<size_t>> tuition;
    int purchaseCost;
    int improvementCost;
    bool hasMonopoly;

    public:
        Academic(string name,  size_t blockPosition, size_t improvementLevel, string monopolyBlock, unique_ptr<vector<size_t>> tuition, int purchaseCost, int improvementCost, bool hasMonopoly);
        vector<Ownable*> BlockGroupMembers;

        ~Academic() override = default;
        int getLevel() const;
        void setImprovments(size_t n);
        size_t getTuition() const;
        void buyImprovement();
        void sellImprovement();
        int getImprovementCost() const;
        char getBType() const override;
        string getMonopolyBlock() const;
        
        virtual void printName() override;
        void printImpr();
        virtual void printLine(int lineNum) override;
        void setHasMonopoly(bool b);
        bool getHasMonopoly();
};

#endif
