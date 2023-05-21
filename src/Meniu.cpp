//
// Created by Paula on 5/21/2023.
//

#include "../headers/Meniu.h"
#include "../headers/Erori.h"

int Meniu::citire_int(){
    int a;
    std::cin>>a;
    return a;
}

Meniu::Meniu(int _w, int _h, const std::string& pn):w(_w),h(_h),player_name(pn){}

void Meniu::start(){
    rlutil::setColor(rlutil::LIGHTCYAN);
    std::cout<<"hello there, what is your name?\n";
    rlutil::setColor(rlutil::WHITE);
    std::cin>>player_name;
    rlutil::setColor(rlutil::LIGHTCYAN);
    std::cout<<"Your goal is to cross the road as many times as possible, while collecting boosters\nWhen you finished collecting boosters, you win!";
    std::cout<<"\nBe careful tho, when you get hit by a car it's Game Over for you. You only live once ;)\n\n";
    std::cout<<"ok, "<<player_name<<", you now have to pick the shape of your street\n";
    std::cout<<"choose two numbers between 6 and 15 for your street's width and height\n";
    bool ok;
    do{
        ok=false;
        std::cout<<"width=";
        w=citire_int();
        std::cout<<"height=";
        h=citire_int();
        if(!(w>=6 && w<=15) || !(h>=6 && h<=15)) {
            std::cout << "Dimensiuni gresite!!";
            ok = true; //se citeste din nou
        }

    }
    while(ok);

    Game joc(w,h,player_name);
    std::cout<<"when you think you're ready, type \"start\" and press enter.\n";
    do{
        ok=false;
        std::string aux;
        rlutil::setColor(rlutil::WHITE);
        std::cin>> aux;
        rlutil::setColor(rlutil::LIGHTCYAN);

        if(aux!="start"){
            std::cout<<"take your time !\nRemeber, to start type \"start\" and press enter!\n";
            ok=true;
        }


    }
    while(ok);

    joc.run();
}
