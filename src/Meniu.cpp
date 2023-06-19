//
// Created by Paula on 5/21/2023.
//

#include "../headers/Meniu.h"
#include "../headers/Erori.h"




Meniu::Meniu(int _h, const std::string& pn):h(_h),player_name(pn){}

void Meniu::open() {
    rlutil::setColor(rlutil::LIGHTCYAN);
    std::cout << "hello there, what is your name?\n";
    rlutil::setColor(rlutil::WHITE);
    std::cin >> player_name;
    rlutil::setColor(rlutil::LIGHTCYAN);
    std::cout
            << "Your goal is to cross the road as many times as possible, while collecting boosters\nWhen you finished collecting boosters, you win!";
    std::cout << "\nBe careful tho, when you get hit by a car it's Game Over for you. You only live once ;)\n\n";
    std::cout << "ok, " << player_name << ", you now have to pick the shape of your street\n";
    std::cout << "choose one number between 6 and 12 for your street's height\n";
    bool ok;
    do {
        ok = false;
        std::cout << "height=";
        std::cin >> h;
        if (!(h >= 6 && h <= 12)) {
            std::cout << "Dimensiuni gresite!!";
            ok = true; //se citeste din nou
        }

    } while (ok);
}
void Meniu::run(){
    auto& joc=Game::get_game(12,h,player_name);
    std::cout<<"\nYou know what's the fun part?\nYou get to choose your own prizes!\n";
    std::cout<<"Today I am Santa Claus, write me a list of up to 10 items of whatever you like!\n Could be a lucky number, an extravagant prime, a cat, a dog, a sum of money\n";
    std::cout<<"If you don't choose 10 items, I'm gonna send you surprises!\nType the numer of prizes, the type of prize (\"number\" or \"object\") and then your prizes below. All the prizes have to be the same type";
    bool ok;
    do{
        ok=false;
        int l;
        std::string type;
        rlutil::setColor(rlutil::WHITE);
        std::cin>> l>>type;
        rlutil::setColor(rlutil::LIGHTCYAN);
        if(l>10 || l<0){
            std::cout<<"wrong length!\n";
            ok=true;
        }
        else if(type!="number" && type!="object"){
            std::cout<<"wrong type, read instructions again\n";
            ok=true;
        }
        else{
            if(type=="number"){
                std::vector<float> p;
                for(int i=0;i<l;i++){
                    float x;
                    std::cin>>x;
                    p.push_back(x);
                }
                Prizes<float> sume(p,l);
            }
            else{
                std::vector<std::string> p;
                for(int i=0;i<l;i++){
                    std::string x;
                    std::cin>>x;
                    p.push_back(x);
                }
                Prizes<std::string> sume(p,l);
            }
        }

    }
    while(ok);
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
