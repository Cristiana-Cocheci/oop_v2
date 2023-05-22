//
//
// Created by Paula on 5/21/2023.
//

#include "../headers/Booster.h"
#include "../headers/Game.h"

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

Coin& Coin::operator=(const Coin &other) {
    std::cout << "op=coin\n";
    x = other.x;
    y = other.y;
    noLanes = other.noLanes;
    mapWidth = other.mapWidth;
    name=other.name;
    value=other.value;
    return *this;
}

void Coin::apply(Game &game, Player &player){
    game.increase_coins(value);
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

int Coin::use() {
    return value;
}
/*
std::string Coin::type() {
    return "coin";
}
*/
JumpToken::JumpToken(const std::string &_name, int _noLanes, int _mapWidth)
        : Booster(rand()%(_mapWidth-1)+1,rand()%(_noLanes-1)+1,_noLanes,_mapWidth, _name){}

        /*
std::string JumpToken::type() {
    return "JumpToken";
}*/

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
int JumpToken::use() {
    if(name=="short"){
        return 1;
    }
    if(name=="long"){
        return noLanes;
    }
    else{//if(name=="back"){
        return -1;
    }
}


CoinJump::CoinJump(const std::string &n, int h, int w)
        :Booster(rand()%(w-1)+1,rand()%(h-1)+1,h,w, n),Coin(n,h,w), JumpToken(n,h,w){
    value=10;
}
/*
std::string CoinJump::type() {
    return "CoinJump";
}*/


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
int CoinJump::use() {
    return value;
}