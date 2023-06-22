//
//
// Created by Paula on 5/21/2023.
//

#include "../headers/Booster.h"
#include "../headers/Game.h"
/*
std::shared_ptr<Booster> Coin::clone(){
    return std::make_shared<Coin>(*this);
}
std::shared_ptr<Booster> CoinJump::clone(){
    return std::make_shared<CoinJump>(*this);
}
std::shared_ptr<Booster> JumpToken::clone(){
    return std::make_shared<JumpToken>(*this);
}
*/
Booster::Booster(int _x, int _y, int _noLanes, int _mapWidth, const std::string &n) : x(_x),y(_y), noLanes(_noLanes), mapWidth(_mapWidth), name(n){};

int Booster::getX() const {
    return x;
}

int Booster::getY() const {
    return y;
}

Coin::Coin(const std::string &_name, int _noLanes, int _mapWidth) :Booster(rand()%(_mapWidth-1)+1,rand()%(_noLanes-1)+1,_noLanes,_mapWidth,_name){
    if(_name=="special"){
        int chance=rand()%10;
        if(chance<5){value=2;} //50% sanse sa fie siver coin
        else if(chance<8){value=3;} //30% sanse sa fie gold coin
        else{value=-1;}//20% sanse sa fie rusty coin
    }
    else if(name=="gold"){value=3;}
    else if(name=="silver"){value=2;}
    else if(name=="rusty"){value=-1;}
}


void Coin::apply(Game &game, Player &player){
    game.increase_coins(value);
    player.MoveUp();
    player.MoveDown();
}

void Coin::afisare(){
    if(name=="gold"){ //gold coin
        rlutil::setColor(rlutil::YELLOW);
        std::cout << "* ";
        rlutil::setColor(rlutil::LIGHTBLUE);
    }
    else if(name=="special"){ //special coin
        rlutil::setColor(rlutil::WHITE);
        std::cout << "* ";
        rlutil::setColor(rlutil::LIGHTBLUE);
    }
}

JumpToken::JumpToken(const std::string &_name, int _noLanes, int _mapWidth)
        : Booster(rand()%(_mapWidth-1)+1,rand()%(_noLanes-1)+1,_noLanes,_mapWidth, _name){}



void JumpToken::apply(Game &game, Player &player){
    player.reset();
    game.increase_score(1);
}

void JumpToken::afisare(){
    if(name=="short"){
        rlutil::setColor(rlutil::LIGHTRED);
        std::cout << "J ";
        rlutil::setColor(rlutil::LIGHTBLUE);
    }
    else if(name=="long"){
        rlutil::setColor(rlutil::LIGHTMAGENTA);
        std::cout << "J ";
        rlutil::setColor(rlutil::LIGHTBLUE);
    }
    else if(name=="back"){
        rlutil::setColor(rlutil::WHITE);
        std::cout << "J ";
        rlutil::setColor(rlutil::LIGHTBLUE);
    }
}

CoinJump::CoinJump(const std::string &n, int h, int w)
        :Booster(rand()%(w-1)+1,rand()%(h-1)+1,h,w, n),Coin(n,h,w), JumpToken(n,h,w){
    value=10;
}



void CoinJump::apply(Game &game, Player &player){
    game.increase_coins(value);
    game.increase_score(1);
    player.reset();
}

void CoinJump::afisare(){
    rlutil::setColor(rlutil::LIGHTGREEN);
    std::cout << "$$";
    rlutil::setColor(rlutil::LIGHTBLUE);
}
