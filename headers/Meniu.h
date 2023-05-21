//
// Created by Paula on 5/21/2023.
//

#include <iostream>
#include <vector>
#include <ctime>
#include <memory>
#include <stdexcept>

#ifndef OOP_MENIU_H
#define OOP_MENIU_H

#include "Game.h"


class Meniu{
private:
    int w,h;
    std::string player_name;
public:
    static int citire_int();
    Meniu(int _w=10, int _h=10, const std::string& pn="unknown");
    void start();
};


#endif //OOP_MENIU_H
