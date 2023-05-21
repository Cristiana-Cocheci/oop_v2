//
// Created by Paula on 5/21/2023.
//


#include "../headers/Player.h"

Player::Player(int width, int height) {x=width/2;y=0, noLanes=height, mapWidth=width;}

Player::Player(const Player &other) : x(other.x),y(other.y), noLanes(other.noLanes), mapWidth(other.mapWidth){ std::cout<<"cc\n";};

Player& Player::operator=(const Player &other) {
    std::cout << "op=\n";
    x = other.x;
    y = other.y;
    noLanes = other.noLanes;
    mapWidth = other.mapWidth;
    return *this;
}

Player::~Player() {std::cout<<"destr\n";}

int Player::getX() const {
    return x;
}
int Player::getY() const {
    return  y;
}

void Player::MoveLeft() {
    if(x>0)x--;
}
void Player::MoveRight() {if(x<mapWidth-1)x++;}
void Player::MoveUp() {if(y<noLanes-1)y++;}
void Player::MoveDown() {if(y>0)y--;}
void Player::reset() {y=0;x=mapWidth/2;}

std::ostream& operator<<(std::ostream &out, const Player &p) {
    out<<"Coordonatle x,y: "<<p.x<<" "<<p.y<<"\n";
    return out;
}