#include <iostream>
#include <vector>
#include <deque>
#include <rlutil.h>
#include <ctime>
#include <memory>
#include <stdexcept>

class eroare_generala : public std::logic_error{
public:
    explicit eroare_generala(const std::string &err) noexcept : std::logic_error(err){};
};
class eroare_dimensiuni : public eroare_generala{
public:
    explicit eroare_dimensiuni(const std::string &err) noexcept: eroare_generala(err){
    }
};

class Lane
{
protected:
    std::deque<int> cars; // 0=gol, 1=masina, 3=feelane -nu
    int direction=rand()%2;
public:
    Lane(int width=20)
    {
        for(int i=0; i<width;i++)
        {
            cars.push_front(0);
        }
    }
    virtual void move(){
        int c; //masina ==1
        if(rand()%10==1) //10% sanse sa intre o masina pe drum
            c=1;
        else
            c=0;
        if(direction==0){ //stanga-dreapta
            cars.push_front(c);
            cars.pop_back();
        }
        else { //dreapta-stanga
            cars.push_back(c);
            cars.pop_front();
        }

    }
    int trackPosition(int pos){return cars[pos];}
    friend std::ostream& operator<<(std::ostream& out, const Lane& l){
        out<<"Afisare dimensiune banda: ";
        out<<l.cars.size()<<"\n";
        return out;
    }
    virtual ~Lane(){}
};
class fastLane : public Lane
{
public:
    fastLane(int _width):Lane(_width){};
    void move() override{
        int c; //masina
        if(rand()%10==0) //10% sanse sa intre o masina de dimensiune 3 pe drum, practic se misca mai repede lane-ul
            c=1;
        else
            c=0;
        if(direction==0){ //stanga-dreapta
            for(int aux=0;aux<3;aux++){
                cars.push_front(c);
                cars.pop_back();
            }
        }
        else { //dreapta-stanga
            for(int aux=0;aux<3;aux++) {
                cars.push_back(c);
                cars.pop_front();
            }
        }

    }
};

class freeLane : public Lane
{
public:
    using Lane::Lane;
    //freeLane(int _width):Lane(_width){};
    void move() override{
        //nimic
        cars.push_back(3);
        cars.pop_front();
    }
};


class Booster
{
protected:
    int x,y,noLanes, mapWidth;
public:
    Booster(int _x, int _y,int _noLanes, int _mapWidth): x(_x),y(_y), noLanes(_noLanes), mapWidth(_mapWidth){};
    virtual int getX() const{return x;}
    virtual int getY() const{return y;}
};
class Coin: public Booster
{
private:
    std::string name;
    int value;
public:
    /*Coin(std::string _name,int _x,int _y,int _noLanes, int _mapWidth):Booster(_x,_y,_noLanes,_mapWidth){
        name=_name;
        if(_name=="gold"){value=3;}
        else if(name=="silver"){value=2;}
        else if(name=="rusty"){value=-1;}
    }*/
    Coin(std::string _name, int _noLanes, int _mapWidth):Booster(rand()%_mapWidth,rand()%_noLanes,_noLanes,_mapWidth){
        if(_name=="special"){
            int chance=rand()%10;
            if(chance<5){name="silver";} //50% sanse sa fie siver coin
            else if(chance<8){name="gold";} //30% sanse sa fie gold coin
            else{name="rusty";}//20% sanse sa fie rusty coin
        }
        else{name=_name;}
        if(name=="gold"){value=3;}
        else if(name=="silver"){value=2;}
        else if(name=="rusty"){value=-1;}

    }
    Coin& operator=(const Coin& other) {
        std::cout << "op=coin\n";
        x = other.x;
        y = other.y;
        noLanes = other.noLanes;
        mapWidth = other.mapWidth;
        name=other.name;
        value=other.value;
        return *this;
    }
};
/*
class Token: public Booster
{
public:

};*/

class Player{
private:
    int x,y, noLanes, mapWidth;
public:
    Player(int width=20, int height=10){x=width/2;y=0, noLanes=height, mapWidth=width;}
    Player(const Player& other): x(other.x),y(other.y), noLanes(other.noLanes), mapWidth(other.mapWidth){ std::cout<<"cc\n";};
    Player& operator=(const Player& other) {
        std::cout << "op=\n";
        x = other.x;
        y = other.y;
        noLanes = other.noLanes;
        mapWidth = other.mapWidth;
        return *this;
    }
    ~Player(){std::cout<<"destr\n";}

    int getX() const{return x;}
    int getY() const{return y;}
    void MoveLeft(){if(x>0)x--;}
    void MoveRight(){if(x<mapWidth-1)x++;}
    void MoveUp(){if(y<noLanes-1)y++;}
    void MoveDown(){if(y>0)y--;}
    void reset(){y=0;x=mapWidth/2;}

    //operator <<
    friend std::ostream& operator<<(std::ostream& out, const Player& p){
        out<<"Coordonatle x,y: "<<p.x<<" "<<p.y<<"\n";
        return out;
    }

};
class Game{
private:
    bool quit;
    int noLanes;
    int mapWidth;
    int score;
    int coins;
    Player player;
    ///Coin special_coin= Coin("special", noLanes, mapWidth);
    std::vector <std::shared_ptr<Lane>> map;
public:
    Game(int w=20, int h=10, int score_=0, int coins_=0)
    {
        score=score_;
        noLanes=h;
        mapWidth=w;
        quit=false;
        coins=coins_;
        //map=std::vector<Lane>(h);

        for(int i=0;i<noLanes;i++) {

            if(i%27==3 || i%27==17) { //
                //fastLane *fl= new fastLane(mapWidth);
                map.push_back(std::make_shared<fastLane>(mapWidth));
            }
            if(i%27==1 || i%27==14){
                //freeLane *free= new freeLane(mapWidth);
                map.push_back(std::make_shared<freeLane>(mapWidth));
            }
            else {
                map.push_back(std::make_shared<Lane>(mapWidth));
            }
        }
        player= Player(mapWidth, noLanes);

    }
    //operator <<
    friend std::ostream& operator<<(std::ostream& out, const Game& g){
        out<<"Date de baza joc: numar benzi-"<<g.noLanes<<", latimea drumului-"<<g.mapWidth<<", scorul-"<<g.score<<"\n";
        return out;
    }
    void draw()
    {
        /*system("cls");*/
        rlutil::cls();
        for(int i=0; i<noLanes; i++)
        {
            for(int j=0; j<mapWidth;j++)
            {
                if(i==0 && (j==0 || j==mapWidth-1)){std::cout<<"-";}
                if(i==0 && (j==1 || j==mapWidth-2)){std::cout<<"S";}
                if(i==noLanes-1 && (j==0 || j==mapWidth-1)){std::cout<<"F";}
                if(map[i]->trackPosition(j)==1 && i>0 && i<noLanes-1)
                { std::cout << "<>"; }
                else if(map[i]->trackPosition(j)==3 && i>0 && i<noLanes-1)//freelane
                { std::cout<<"__";}
                else
                { std::cout<<"  "; }
                if(player.getX()==j && player.getY()==i)
                { std::cout <<"P "; }

            }
            std::cout<<"\n";
        }
        std::cout <<"Score "<<score<<"\n";
    }
    void input()
    {
        char current = std::tolower(rlutil::nb_getch());
        if(current=='a'){player.MoveLeft();}
        if(current=='w'){player.MoveDown();}
        if(current=='s'){player.MoveUp();}
        if(current=='d'){player.MoveRight();}
        if(current=='q'){quit=true;}
    }
    void logic(){
        for(int i=1;i<noLanes-1;i++)
        {
            if(std::rand()%3==0) //sansele sa se miste lane ul
                map[i]->move();
            if(map[i]->trackPosition(player.getX())==1 && player.getY()==i) {
                quit = true;
                std::cout << "YOU LOSE ;-(\n";
            }
        }
        if(player.getY()==noLanes-1)
        {
            /*quit=true;
            std::cout<< "YOU WIN!!!!\n";*/
            score++;
            player.reset();
            ///special_coin=Coin("special", noLanes, mapWidth);
        }
    }
    void run()
    {
        while(!quit)
        {
            input();
            draw();
            logic();
            rlutil::msleep(100);
        }
    }
};

class Meniu{
private:
    int w,h;
    std::string player_name;
public:
    int citire_int(){
        int a;
        std::cin>>a;
        return a;
    }

    void start(){
        std::cout<<"hello there, what is your name?\n";
        std::cin>>player_name;
        std::cout<<"ok, "<<player_name<<", you now have to pick the shape of your street\n";
        std::cout<<"choose two numbers between 3 and 20 for your street's width and height\n";
        bool ok;
        do{
            ok=0;
            std::cout<<"width=";
            w=citire_int();
            std::cout<<"height=";
            h=citire_int();
            try{
                if(!(w>=3 && w<=20) || !(h>=3 && h<=20))
                {
                    throw eroare_dimensiuni("Dimensiuni gresite!!");
                }
            }
            catch (eroare_dimensiuni &e)
            {
                std::cout<<e.what()<<"\n";
                ok=1; //se citeste din nou
            }
        }
        while(ok);

        Game joc(w,h);
        std::cout<<"when you think you're ready, type start and enter";
        std::string aux;
        std::cin>> aux;
        joc.run();
    }

};


int main() {

    srand(time(nullptr));
    Meniu m;
    m.start();
    return 0;
}
