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
#include "Prizes.h"


class Meniu{
private:
    int h;
    std::string player_name;
    bool won,opened,ran;
public:
    Meniu(int _h=10, const std::string& pn="unknown");
    void open();
    void run();
    void premiere();

    friend class Meniu_builder;
};


#endif //OOP_MENIU_H
