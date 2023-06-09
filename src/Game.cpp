//
// Created by Paula on 5/21/2023.
//

#include "../headers/Game.h"


Game& Game::operator=(const Game &other) {
    std::cout << "op=\n";
    quit=other.quit;
    noLanes= other.noLanes;
    mapWidth= other.mapWidth;
    score=other.score;
    coins=other.coins;
    player_name=other.player_name;
    player=other.player;
    no_boosters=other.no_boosters;
    b_activi=other.b_activi;

    for(size_t i=0; i<map.size(); i++){
        map.push_back( other.map[i]->clone());
    }
    for(size_t i=0; i<boosters.size();i++){
        boosters.push_back(other.boosters[i]->clone());
    }

    return *this;
}

Game::Game(int w, int h, const std::string& pn)
        :quit(false), mapWidth(w), noLanes(h), player_name(pn)
{
    if(w<0 || h<0){
        throw nu_incepem("Jocul nu poate incepe");
    }
    score=coins=0;
    b_activi.resize(noLanes, std::vector<bool>(mapWidth,false));
    try {
        for (int i = 0; i < noLanes; i++) {

            if (i % 27 == 3) {
                try {
                    map.push_back(LaneFactory::RightFastLane());
                }
                catch (eroare_lane &err) { std::cout << err.what() << "\n"; }

            }
            if (i % 27 == 9) {
                map.push_back(LaneFactory::LeftFastLane());

            }
            if (i % 27 == 1 || i % 27 == 14) {
                map.push_back(LaneFactory::ffreeLane());
            } else if (i % 27 == 7) {
                map.push_back(LaneFactory::wwaterLane());
            } else {
                if (i % 2 == 0) {
                    map.push_back(LaneFactory::RightNormalLane());
                } else {
                    map.push_back(LaneFactory::LeftNormalLane());
                }

            }
        }
    }
    catch(eroare_lane & err){ std::cout << err.what() << "\n"; }
    player= Player(mapWidth, noLanes);
    no_boosters= (int) 1.8*noLanes;
    rlutil::setColor(rlutil::BROWN);
    for(int i=0;i<no_boosters;i++){
        if(i%3==0){
            std::string coin_type;
            int aux=std::rand();
            if(aux%3==0){coin_type="special";}
            else {coin_type="gold";}
            boosters.push_back(std::make_shared<Coin>(coin_type,noLanes,mapWidth));
        }
        else if(i%3==1){
            std::string jump_type;
            int aux=std::rand();
            if(aux%3==0){jump_type="short";}
            else if(aux%3==1){jump_type="long";}
            else {jump_type="back";}
            boosters.push_back(std::make_shared<JumpToken>(jump_type,noLanes,mapWidth));
        }
        else{
            boosters.push_back(std::make_shared<CoinJump>("coinjump",noLanes,mapWidth));
        }
        b_activi[boosters[i]->getY()][boosters[i]->getX()]=true;
    }
}
void Game::increase_coins(int x){coins+=x;}

void Game::input()
{
char current = std::tolower(rlutil::nb_getch());
if(current=='a'){player.MoveLeft();}
if(current=='w'){player.MoveDown();}
if(current=='s'){player.MoveUp();}
if(current=='d'){player.MoveRight();}
if(current=='q'){quit=true;}
}

void Game::draw()
{

    rlutil::setColor(rlutil::LIGHTBLUE);
    rlutil::cls();
    for(int i=0; i<noLanes; i++)
    {
        for(int j=0; j<mapWidth;j++)
        {
            if(i==0 && (j==0 || j==mapWidth-1)){std::cout<<"-";}
            if(i==0 && (j==1 || j==mapWidth-2)){std::cout<<"S";}
            if(i==noLanes-1 && (j==0 || j==mapWidth-1)){std::cout<<"F";}
            if(map[i]->trackPosition(j)==1 && i>0 && i<noLanes-1)
            {
                rlutil::setColor(rlutil::RED);
                std::cout << "<>";
                rlutil::setColor(rlutil::LIGHTBLUE);
            }
            else if(map[i]->trackPosition(j)==3 && i>0 && i<noLanes-1)//freelane
            {
                rlutil::setColor(rlutil::LIGHTGREEN);
                std::cout << "__";
                rlutil::setColor(rlutil::LIGHTBLUE);
            }
            else if(map[i]->trackPosition(j)==4 && i>0 && i<noLanes-1)//waterlane -- water
            {
                rlutil::setColor(rlutil:: BLUE);
                std::cout << "~~";
                rlutil::setColor(rlutil::LIGHTBLUE);
            }
            else if(map[i]->trackPosition(j)==5 && i>0 && i<noLanes-1)//waterlane -- lilypad
            {
                rlutil::setColor(rlutil:: GREEN);
                std::cout << "/\\";
                rlutil::setColor(rlutil::LIGHTBLUE);
            }
            else
            { std::cout<<"  "; }
            if(player.getX()==j && player.getY()==i)
            {
                rlutil::setColor(rlutil::BLUE);
                std::cout << "P ";
                rlutil::setColor(rlutil::LIGHTBLUE);
                for(int q=0;q<no_boosters;q++){
                    if(boosters[q]->getX()==j && boosters[q]->getY()==i && b_activi[boosters[q]->getY()][boosters[q]->getX()]==1){
                        b_activi[boosters[q]->getY()][boosters[q]->getX()]=false; //dezactivez booster;
                        boosters[q]->apply(*this, player);

                    }
                }
            }
            //afisare_booster
            for(int q=0;q<no_boosters;q++){
                if(boosters[q]->getX()==j && boosters[q]->getY()==i && b_activi[boosters[q]->getY()][boosters[q]->getX()]==1){
                    boosters[q]->afisare();

                }
            }
        }
        std::cout<<"\n";
    }
    std::cout <<"Score : "<<score<<"\n";
    std::cout <<"Coins : " <<coins<<"\n";
}

bool Game::collected_b(){
    for(int i=0;i<noLanes;i++){
        for(int j=0;j<mapWidth;j++){
            if(b_activi[i][j]==true){
                return false;
            }
        }
    }
    return true;
}

void Game::logic(){
    for(int i=1;i<noLanes-1;i++)
    {
        if(std::rand()%5==0) //sansele sa se miste lane ul
            map[i]->move();
        if(map[i]->trackPosition(player.getX())==1 && player.getY()==i) {
            quit = true;
            rlutil::setColor(rlutil::LIGHTCYAN);
            std::cout << "Sorry "<<player_name<<", but you lost, you were hit by a car ;-(\n";
        }
        else if(map[i]->trackPosition(player.getX())==4 && player.getY()==i) {
            quit = true;
            rlutil::setColor(rlutil::LIGHTCYAN);
            std::cout << "Sorry "<<player_name<<", but you lost, you fell into water ;-(\n";
        }
        ///daca s-au colectat toate boosterele
        if(collected_b()==1){
            rlutil::setColor(rlutil::LIGHTCYAN);
            std::cout << "Wow "<<player_name<<", you WON :D\n";
            quit=true;
            return;
        }
    }
    if(player.getY()==noLanes-1)
    {
        score++;
        player.reset();
    }
}

void Game::increase_score(int x) {
    score+=x;
}

void Game::run()
{
    while(!quit)
    {
    input();
    draw();
    logic();
    rlutil::msleep(100);
    }
}