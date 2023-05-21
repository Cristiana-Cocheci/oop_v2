//
// Created by Paula on 5/21/2023.
//


#ifndef OOP_BOOSTER_H
#define OOP_BOOSTER_H

#include <string>
#include <iostream>
#include <rlutil.h>
//#include "Game.h"

class Booster
{
protected:
    int x,y,noLanes, mapWidth;
    std::string name;
public:
    Booster(int _x, int _y,int _noLanes, int _mapWidth, const std::string& n);
    //virtual Booster* clone() const=0;
    virtual int getX() const;
    virtual int getY() const;
    virtual int use()=0;
    virtual std::string type()=0;
    virtual std::string getName()=0;
    //virtual void apply(Game &game, Player &player)=0;
    virtual void afisare()=0;
    virtual ~Booster() = default;
};
class Coin: virtual public Booster
{
protected:
    int value;
public:
    //virtual Booster* clone() const override{return new Coin(*this);;}
    Coin(const std::string& _name, int _noLanes, int _mapWidth);
    Coin& operator=(const Coin& other);
    std::string getName() override;
    int use() override;
    std::string type()override;
    //void apply (Game &game, Player &player) override;
    void afisare() override;
    ~Coin() override = default;
};

class JumpToken: virtual public Booster
{
public:
    //virtual Booster* clone() const override { return new JumpToken(*this);}
    JumpToken(const std::string& _name, int _noLanes, int _mapWidth);

    std::string type()override;
    int use()override;
    std::string getName() override;
    //void apply (Game &game, Player &player) override;
    void afisare() override;
    ~JumpToken() override = default;
};

class CoinJump: public Coin, public JumpToken{
public:
    CoinJump(const std::string& n, int h, int w);
    std::string type()override;
    std::string getName() override;
    //void apply (Game &game, Player &player) override;
    void afisare() override;
    int use() override;
};


#endif //OOP_BOOSTER_H