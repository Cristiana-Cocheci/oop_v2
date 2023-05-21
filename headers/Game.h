//
// Created by Paula on 5/21/2023.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <iostream>
#include <vector>
#include <deque>
#include <ctime>
#include <memory>
#include "Player.h"
#include "Lane.h"
#include "Booster.h"


class Game{
private:
    bool quit;
    int noLanes;
    int mapWidth;
    int score;
    int coins;
    std::string player_name;
    Player player;
    ///Coin special_coin= Coin("special", noLanes, mapWidth);
    std::vector <std::shared_ptr<Lane>> map;
    std::vector <std::shared_ptr<Booster>> boosters;
    int no_boosters;
    std::vector <std::vector<bool>> b_activi;
public:
    std::shared_ptr<Game> clone();
    void increase_coins(int x);
    void increase_score(int x);
    Game(int w=20, int h=10, const std::string& pn="unknown");

    //operator <<
    friend std::ostream& operator<<(std::ostream& out, const Game& g){
        out<<"Date de baza joc: numar benzi-"<<g.noLanes<<", latimea drumului-"<<g.mapWidth<<", scorul-"<<g.score<<"\n";
        return out;
    }
    void draw();
    void input();
    bool collected_b();
    void logic();
    void run();

};



#endif //OOP_GAME_H
