//
// Created by Paula on 5/21/2023.
//

#include "../headers/Game.h"

std::shared_ptr<Game> Game::clone(){
    return std::make_shared<Game>(*this);
}

Game::Game(int w, int h, const std::string& pn)
        :quit(false), noLanes(h), mapWidth(w), player_name(pn)
{
    if(w<0 || h<0){
        throw nu_incepem("Jocul nu poate incepe");
    }
    score=coins=0;
    b_activi.resize(noLanes, std::vector<bool>(mapWidth,false));
    for(int i=0;i<noLanes;i++) {

        if(i%27==3 || i%27==17) { //
            //fastLane *fl= new fastLane(mapWidth);
            try{
                map.push_back(std::make_shared<fastLane>(mapWidth));
            }
            catch(eroare_lane &err){std::cout<< err.what()<< "\n";}

        }
        if(i%27==1 || i%27==14){
            //freeLane *free= new freeLane(mapWidth);
            map.push_back(std::make_shared<freeLane>(mapWidth));
        }
        else {
            try{
                map.push_back(std::make_shared<Lane>(mapWidth));
            }
            catch(eroare_lane &err){std::cout<< err.what()<< "\n";}

        }
    }
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
                        /*
                        if(boosters[q]->type()=="coin"){
                            coins+=boosters[q]->use();
                        }
                        else if(boosters[q]->type()=="JumpToken"){
                            int distance=boosters[q]->use();
                            if(distance==-1){player.MoveDown();}
                            else{
                                if(distance==noLanes){distance=noLanes-j+1;}
                                for(int aux=0;aux<distance;aux++){player.MoveUp();}

                            }
                        }
                        else if(boosters[q]->type()=="CoinJump"){
                            coins+=boosters[q]->use();
                            player.reset();
                            score++;
                        }*/
                    }
                }
            }
            //afisare_booster
            for(int q=0;q<no_boosters;q++){
                if(boosters[q]->getX()==j && boosters[q]->getY()==i && b_activi[boosters[q]->getY()][boosters[q]->getX()]==1){
                    boosters[q]->afisare();
                    /*if(boosters[q]->type()=="coin"){
                        if(boosters[q]->getName()=="gold"){ //gold coin
                            rlutil::setColor(rlutil::YELLOW);
                            std::cout << "* ";
                            rlutil::setColor(rlutil::LIGHTBLUE);
                        }
                        else if(boosters[q]->getName()=="special"){ //special coin
                            rlutil::setColor(rlutil::WHITE);
                            std::cout << "* ";
                            rlutil::setColor(rlutil::LIGHTBLUE);
                        }

                    }
                    else if(boosters[q]->type()=="JumpToken"){
                        if(boosters[q]->getName()=="short"){
                            rlutil::setColor(rlutil::LIGHTRED);
                            std::cout << "J ";
                            rlutil::setColor(rlutil::LIGHTBLUE);
                        }
                        else if(boosters[q]->getName()=="long"){
                            rlutil::setColor(rlutil::LIGHTMAGENTA);
                            std::cout << "J ";
                            rlutil::setColor(rlutil::LIGHTBLUE);
                        }
                        else if(boosters[q]->getName()=="back"){
                            rlutil::setColor(rlutil::WHITE);
                            std::cout << "J ";
                            rlutil::setColor(rlutil::LIGHTBLUE);
                        }
                    }
                    else if(boosters[q]->type()=="CoinJump"){
                        rlutil::setColor(rlutil::LIGHTGREEN);
                        std::cout << "$$";
                        rlutil::setColor(rlutil::LIGHTBLUE);
                    }
                    */
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
            std::cout << "Sorry "<<player_name<<", but you lost ;-(\n";
        }
        ///daca s-au colectat toate boosterele
        if(collected_b()==1){
            quit=true;
            rlutil::setColor(rlutil::LIGHTCYAN);
            std::cout << "Wow "<<player_name<<", you WON :D\n";
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