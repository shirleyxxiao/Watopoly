#ifndef DISPLAY_H
#define DISPLAY_H

#include "Board.h"    
#include "observer.h" 

#include <cstddef>     
#include <iostream>    
#include <string>      
#include <memory>

using namespace std;

class Display : public Observer {
    Board* b;

  public:
    Display(Board* b);
    void notify() override;
    ~Display() = default;

};

#endif
