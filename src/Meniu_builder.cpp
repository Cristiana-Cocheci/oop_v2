//
// Created by Paula on 6/7/2023.
//

#include "../headers/Meniu_builder.h"

Meniu_builder &Meniu_builder::open() {
    M.open();
    return *this;
}

Meniu_builder &Meniu_builder::run() {
    M.run();
    return *this;
}

Meniu_builder &Meniu_builder::premiere(){
    M.premiere();
    return *this;
}