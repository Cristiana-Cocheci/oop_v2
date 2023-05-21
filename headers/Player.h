//
// Created by Paula on 5/21/2023.
//

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include <iostream>

class Player{
private:
    int x,y, noLanes, mapWidth;
public:
    Player(int width=20, int height=10);
    Player(const Player& other);
    Player& operator=(const Player& other);
    ~Player();

    int getX() const;
    int getY() const;
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();
    void reset();

    //operator <<
    friend std::ostream& operator<<(std::ostream& out, const Player& p);

};

#endif //OOP_PLAYER_H