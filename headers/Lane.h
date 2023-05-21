//
// Created by Paula on 5/21/2023.
//

#ifndef OOP_LANE_H
#define OOP_LANE_H

#include "Erori.h"
#include <deque>
#include <cstdlib>
#include <iostream>

class Lane
{
protected:
    std::deque<int> cars; // 0=gol, 1=masina, 3=feelane -nu
    const int direction=rand()%2;
public:
    Lane(int width=10);
    virtual void move();
    int trackPosition(int pos);
    friend std::ostream& operator<<(std::ostream& out, const Lane& l);
    virtual ~Lane() = default;
};
class fastLane : public Lane
{
public:
    using Lane::Lane;
    void move() override;
    ~fastLane() override = default;
};

class freeLane : public Lane
{
public:
    freeLane(int width=10);
    void move() override;
    ~freeLane() override = default;
};

#endif //OOP_LANE_H