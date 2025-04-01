#ifndef EVENTFACTORY_H
#define EVENTFACTORY_H

#include "Event.h"
#include "prng.h"
#include "MoveForward.h"
#include "MoveBackward.h"
#include "GainMoney.h"
#include "LoseMoney.h"
#include "CaughtByTims.h"
#include "GoToCollectOSAP.h"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>

using namespace std;
// #include "subject.h"
// #include "observer.h"
// #include "info.h"


class EventFactory {
    public:
        static std::unique_ptr<Event> createEvent(bool isSLC){
            // PRNG prng(12345);  // Initialize PRNG with a seed
            // PRNG prng;
            PRNG prng(static_cast<std::uint32_t>(std::time(0)));  // Seed with current time
            std::uint32_t prob = prng(72) + 1;  // Generate a random number in [1,72]
            if (isSLC){
                if (prob <= 9){
                    return std::make_unique<MoveBackward>(3);
                } else if (prob <= 21){
                    return std::make_unique<MoveBackward>(2);
                } else if (prob <= 33){
                    return std::make_unique<MoveBackward>(1);
                } else if (prob <= 42){
                    return std::make_unique<MoveForward>(1);
                } else if (prob <= 54){
                    return std::make_unique<MoveForward>(2);
                } else if (prob <= 66){
                    return std::make_unique<MoveForward>(3);
                } else if (prob <= 69){
                    return std::make_unique<CaughtByTims>();
                } else {
                    return std::make_unique<GoToCollectOSAP>();
                }
            } else {
                if (prob <= 4){
                    return std::make_unique<LoseMoney>(200);
                } else if (prob <= 12){
                    return std::make_unique<LoseMoney>(100);
                } else if (prob <= 24){
                    return std::make_unique<LoseMoney>(50);
                } else if (prob <= 48){
                    return std::make_unique<GainMoney>(25);
                } else if (prob <= 60){
                    return std::make_unique<GainMoney>(50);
                } else if (prob <= 68){
                    return std::make_unique<GainMoney>(100);
                } else {
                    return std::make_unique<GainMoney>(200);
                }
            }
        }
        virtual ~EventFactory() {}  
};

#endif 
