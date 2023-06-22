//
// Created by Paula on 5/21/2023.
//

#include "../headers/Meniu.h"
#include "../headers/Erori.h"




Meniu::Meniu(int _h, const std::string& pn):h(_h),player_name(pn),won(false), opened(false), ran(false){}

void Meniu::open() {
    won=false;
    opened=true;
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
    std::cout<<"\nYou know what's the fun part?\nYou get to choose your own prizes!\n";
    std::cout<<"Today I am Santa Claus, write me a list of up to 10 items of whatever you like!\n Could be a lucky number, an extravagant prime, a cat, a dog, a sum of money\n";
    std::cout<<"Type the numer of prizes, the type of prize (\"number\" or \"object\") and then your prizes below. All the prizes have to be the same type";
    do{
        ok=false;
        int l;
        std::string type;
        rlutil::setColor(rlutil::WHITE);
        std::cin>> l;
        rlutil::setColor(rlutil::LIGHTCYAN);
        if(l>10 || l<0){
            std::cout<<"wrong length!\n";
            ok=true;
        }
        else {
            std::cin>>type;
            while (type != "number" && type != "object") {
                std::cout << "wrong type, read instructions again\n";
                std::cin>>type;
            }
            if (type == "number") {
                std::vector<float> p;
                for (int i = 0; i < l; i++) {
                    float x;
                    std::cin >> x;
                    p.push_back(x);
                }
                Prizes<float> sume(p);
            } else {
                std::vector<std::string> p;
                for (int i = 0; i < l; i++) {
                    std::string x;
                    std::cin >> x;
                    p.push_back(x);
                }
                Prizes<std::string> sume(p);
                std::cout<<sume.getsize()<<"\n";
            }
        }
    }
    while(ok);
}
void Meniu::run(){
    if(opened==false){
        throw nu_incepem("Nu am citit inca datele!! Jocul nu poate incepe...\n");
    }
    ran=true;
    auto& joc=Game::get_game(10,h,player_name);
    bool ok;
    std::cout<<"\nwhen you think you're ready, type \"start\" and press enter.\n";
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

    won=joc.run();
}

void Meniu::premiere() {
    if(opened==false){
        throw nu_incepem("Nu am citit inca datele!! Nu putem afisa premiile...\n");
    }
    Prizes<float> p;
    Prizes<std::string> w;
    std::cout<<"AFISARE PREMII SELECTATE: [ ";
    if(p.getsize()>0) {
        for (auto e: p.get_p()) {
            std::cout << e << " ";
        }
    }else{
        for(auto e: w.get_p()){
            std::cout<<e<<" ";
        }
    }
    std::cout<<"]\n";
    if(won==true){
        if(p.getsize()>0) {
            p.winner(h);
        }else{
            w.winner(h);
        }
    }
    else if(ran==true){
        std::cout<<"Din pacate nu poti sa primesti premiile alese, dar iti voi da un premiu de consolare!";
        std::cout<<w;
    }
}