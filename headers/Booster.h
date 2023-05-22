//
// Created by Paula on 5/21/2023.
//


#ifndef OOP_BOOSTER_H
#define OOP_BOOSTER_H

#include <string>
#include <iostream>
#include <rlutil.h>
#include <memory>
class Game;
class Player;

class Booster
{
protected:
    int x,y,noLanes, mapWidth;
    std::string name;
public:
    virtual std::shared_ptr<Booster> clone()=0;
    Booster(int _x, int _y,int _noLanes, int _mapWidth, const std::string& n);
    virtual int getX() const;
    virtual int getY() const;
    virtual void apply(Game &game, Player &player)=0;
    virtual void afisare()=0;
    virtual ~Booster() = default;
};
class Coin: virtual public Booster
{
protected:
    int value;
public:
    std::shared_ptr<Booster> clone() override;
    Coin(const std::string& _name, int _noLanes, int _mapWidth);
    void apply (Game &game, Player &player) override;
    void afisare() override;
    ~Coin() override = default;
};

class JumpToken: virtual public Booster
{
public:
    std::shared_ptr<Booster> clone() override;
    JumpToken(const std::string& _name, int _noLanes, int _mapWidth);
    void apply (Game &game, Player &player) override;
    void afisare() override;
    ~JumpToken() override = default;
};

class CoinJump: public Coin, public JumpToken{
public:
    std::shared_ptr<Booster> clone() override;
    CoinJump(const std::string& n, int h, int w);
    void apply (Game &game, Player &player) override;
    void afisare() override;
};


#endif //OOP_BOOSTER_H