//
// Created by Paula on 6/7/2023.
//

#include "../headers/LaneFactory.h"

std::shared_ptr<Lane> LaneFactory::LeftNormalLane() {
    return std::make_shared<Lane> (10, 1, 10);
}

std::shared_ptr<Lane> LaneFactory::RightNormalLane() {
    return std::make_shared<Lane> (10,0,10);
}

std::shared_ptr<fastLane> LaneFactory::RightFastLane() {
    return std::make_shared<fastLane> (10,0,5);
}

std::shared_ptr<fastLane> LaneFactory::LeftFastLane() {
    return std::make_shared<fastLane> (10,1,5);
}

std::shared_ptr<freeLane> LaneFactory::ffreeLane() {
    return std::make_shared<freeLane>(10);
}

std::shared_ptr<waterLane> LaneFactory::wwaterLane() {
    return std::make_shared<waterLane>(10);
}
