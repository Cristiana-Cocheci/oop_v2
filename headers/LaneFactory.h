//
// Created by Paula on 6/7/2023.
//

#ifndef OOP_LANEFACTORY_H
#define OOP_LANEFACTORY_H

#include <iostream>
#include <memory>
#include "Lane.h"

class LaneFactory {
public:
    static std::shared_ptr<Lane> LeftNormalLane ();
    static std::shared_ptr<Lane> RightNormalLane();
    static std::shared_ptr<fastLane> RightFastLane();
    static std::shared_ptr<fastLane> LeftFastLane();
    static std::shared_ptr<freeLane> ffreeLane();
    static std::shared_ptr<waterLane> wwaterLane();
};

#endif //OOP_LANEFACTORY_H
