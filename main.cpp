#include <ctime>

#include "headers/Meniu.h"

int main() {

    srand(time(nullptr));
    Meniu m;
    try{
        m.start();
    }
    catch(nu_incepem &err){std::cout<< err.what()<< "\n";}

    return 0;
}
