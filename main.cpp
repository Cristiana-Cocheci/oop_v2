#include <ctime>

#include "headers/Meniu_builder.h"

int main() {

    srand(time(nullptr));
    Meniu_builder mb;
    try{
        mb.open().run();

    }
    catch(nu_incepem &err){std::cout<< err.what()<< "\n";}

    return 0;
}
