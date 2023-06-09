//
// Created by Paula on 5/21/2023.
//

#ifndef OOP_LANE_H
#define OOP_LANE_H

#include "Erori.h"
#include <deque>
#include <cstdlib>
#include <iostream>
#include <memory>


class Lane
{
protected:
    std::deque<int> cars; // 0=gol, 1=masina, 3=feelane -nu
    int direction;
    int SpawnRate;
public:
    //virtual std::shared_ptr<Lane> clone();
    Lane(int width=10, int dir=0, int rate=10);
    virtual void move();
    int trackPosition(int pos);
    friend std::ostream& operator<<(std::ostream& out, const Lane& l);
    virtual ~Lane() = default;
};
class fastLane : public Lane
{
public:
    //std::shared_ptr<Lane> clone() override;
    using Lane::Lane;
    void move() override;
    ~fastLane() override = default;
};

class freeLane : public Lane
{
public:
    //std::shared_ptr<Lane> clone() override;
    freeLane(int width=10);
    void move() override;
    ~freeLane() override = default;
};
class waterLane : public freeLane{
public:
    //std::shared_ptr<Lane> clone() override;
    waterLane(int width=10);
    ~waterLane() override = default;
};



#endif //OOP_LANE_H