#ifndef BUILDING_H
#define BUILDING_H

#include <vector>
#include <string>
#include <cstddef>

using namespace std;


class Building {
    string name;
    size_t blockPosition;
    std::vector<char> playerOn;
    bool isOwnable;

    public:
        Building(string name, size_t blockPosition, bool isOwnable); //ctor
        string getBName() const; 
        size_t getBPos() const; 
        bool getOwnableStatus() const;
        void setOwnable(bool b);
        virtual ~Building() = default; 
        
        virtual void printBottom();
        virtual void printName() = 0;
        virtual void printLine(int lineNum) = 0;
        void emptyRow();
        void printPlayer();
        void attachPlayer(char token);
        void clearPlayer();
        bool ifOwnable();
};

#endif
