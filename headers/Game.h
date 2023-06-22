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
#include "LaneFactory.h"


class Game{
private:
    bool win;
    bool quit;
    int noLanes;
    int mapWidth;
    int score;
    int coins;
    std::string player_name;
    Player player;
    std::vector <std::shared_ptr<Lane>> map;
    std::vector <std::shared_ptr<Booster>> boosters;
    int no_boosters;
    std::vector <std::vector<bool>> b_activi;

    Game(int w=10, int h=10, const std::string& pn="unknown");
public:
    Game(const Game&)=delete;
    Game& operator=(const Game&)=delete;
    void increase_coins(int x);
    void increase_score(int x);
    //operator <<
    friend std::ostream& operator<<(std::ostream& out, const Game& g){
        out<<"Date de baza joc: numar benzi-"<<g.noLanes<<", latimea drumului-"<<g.mapWidth<<", scorul-"<<g.score<<"\n";
        return out;
    }

    void draw();
    void input();
    bool collected_b();
    void logic();
    bool run();

    static Game& get_game(int w,int h,std::string pn);
};



#endif //OOP_GAME_H
