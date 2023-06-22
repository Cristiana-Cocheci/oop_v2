//
// Created by Paula on 6/7/2023.
//

#ifndef OOP_MENIU_BUILDER_H
#define OOP_MENIU_BUILDER_H
#include "Meniu.h"

class Meniu_builder{
private:
    Meniu M;
public:
    Meniu_builder& open();
    Meniu_builder& run();
    Meniu_builder& premiere();
};

#endif //OOP_MENIU_BUILDER_H
