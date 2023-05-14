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
    explicit eroare_dimensiuni(const std::string &err) noexcept: eroare_generala(err){}
};
class nu_incepem :public eroare_generala{
public:
    explicit nu_incepem(const std::string &err) noexcept: eroare_generala(err){}
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
    using Lane::Lane;
    //fastLane(int _width):Lane(_width){};
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
    ~fastLane() override{}
};

class freeLane : public Lane
{
public:
    freeLane(int width=20){
        for(int i=0; i<width;i++)
        {
            cars.push_front(3);
        }
    }
    void move() override{
        //nimic
        //sta pe loc
    }
    ~freeLane() override{}
};


class Booster
{
protected:
    int x,y,noLanes, mapWidth;
    std::string name;
public:
    Booster(int _x, int _y,int _noLanes, int _mapWidth, std::string n): x(_x),y(_y), noLanes(_noLanes), mapWidth(_mapWidth), name(n){};
    virtual int getX() const{return x;}
    virtual int getY() const{return y;}
    virtual int use()=0;
    virtual std::string type()=0;
    virtual std::string getName()=0;
    virtual ~Booster(){}
};
class Coin: virtual public Booster
{
protected:
    int value;
public:
    Coin(const std::string& _name, int _noLanes, int _mapWidth):Booster(rand()%(_mapWidth-1)+1,rand()%(_noLanes-1)+1,_noLanes,_mapWidth,_name){
        if(_name=="special"){
            int chance=rand()%10;
            if(chance<5){value=2;} //50% sanse sa fie siver coin
            else if(chance<8){value=3;} //30% sanse sa fie gold coin
            else{value=-1;}//20% sanse sa fie rusty coin
        }
        else if(name=="gold"){value=3;}
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
    std::string getName() override {return name;}
    int use() override{return value;}
    std::string type()override{return "coin";}
    ~Coin() override{}
};

class JumpToken: virtual public Booster
{
public:
    JumpToken(const std::string& _name, int _noLanes, int _mapWidth)
        : Booster(rand()%(_mapWidth-1)+1,rand()%(_noLanes-1)+1,_noLanes,_mapWidth, _name){}

    std::string type()override{return "JumpToken";}
    int use()override{
        if(name=="short"){
            return 1;
        }
        if(name=="long"){
            return noLanes;
        }
        else{//if(name=="back"){
            return -1;
        }
    }
    std::string getName() override {return name;}
    ~JumpToken() override{}
};

class CoinJump: public Coin, public JumpToken{
public:
    CoinJump(const std::string& n, int h, int w)
        :Booster(rand()%(w-1)+1,rand()%(h-1)+1,h,w, n),Coin(n,h,w), JumpToken(n,h,w){
        value=10;
    }
    std::string type()override{return "CoinJump";}
    std::string getName() override {return name;}
    int use() override{
        return value;
    }
};

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
    std::string player_name;
    Player player;
    ///Coin special_coin= Coin("special", noLanes, mapWidth);
    std::vector <std::shared_ptr<Lane>> map;
    std::vector <std::shared_ptr<Booster>> boosters;
    int no_boosters;
    std::vector <std::vector<bool>> b_activi;
public:
    Game(int w=20, int h=10, const std::string& pn="unknown", int score_=0, int coins_=0)
        :quit(false), noLanes(h), mapWidth(w), score(score_), coins(coins_), player_name(pn)
    {

        b_activi.resize(noLanes, std::vector<bool>(mapWidth,false));
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
        no_boosters= (int) 1.8*noLanes;
        rlutil::setColor(rlutil::BROWN);
        for(int i=0;i<no_boosters;i++){
            if(i%3==0){
                std::string coin_type;
                if(i%3==0){coin_type="special";}
                else {coin_type="gold";}
                boosters.push_back(std::make_shared<Coin>(coin_type,noLanes,mapWidth));
            }
            else if(i%3==1){
                std::string jump_type;
                if(i%3==0){jump_type="short";}
                else if(i%3==1){jump_type="long";}
                else {jump_type="back";}
                boosters.push_back(std::make_shared<JumpToken>(jump_type,noLanes,mapWidth));
            }
            else{
                boosters.push_back(std::make_shared<CoinJump>("coinjump",noLanes,mapWidth));
            }
            b_activi[boosters[i]->getY()][boosters[i]->getX()]=true;
        }
    }
    //operator <<
    friend std::ostream& operator<<(std::ostream& out, const Game& g){
        out<<"Date de baza joc: numar benzi-"<<g.noLanes<<", latimea drumului-"<<g.mapWidth<<", scorul-"<<g.score<<"\n";
        return out;
    }
    void draw()
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
                                int distance=noLanes-j+1;
                                for(int aux=0;aux<distance;aux++){player.MoveUp();}
                            }
                        }
                    }
                }
                //afisare_booster
                for(int q=0;q<no_boosters;q++){
                    if(boosters[q]->getX()==j && boosters[q]->getY()==i && b_activi[boosters[q]->getY()][boosters[q]->getX()]==1){
                        if(boosters[q]->type()=="coin"){
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

                    }
                }
            }
            std::cout<<"\n";
        }
        std::cout <<"Score : "<<score<<"\n";
        std::cout <<"Coins : " <<coins<<"\n";
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
    bool collected_b(){
        for(int i=0;i<noLanes;i++){
            for(int j=0;j<mapWidth;j++){
                if(b_activi[i][j]==true){
                    return false;
                }
            }
        }
        return true;
    }
    void logic(){
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
    static int citire_int(){
        int a;
        std::cin>>a;
        return a;
    }
    Meniu(int _w=10, int _h=10, const std::string& pn="unknown"):w(_w),h(_h),player_name(pn){}
    void start(){
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
            try{
                if(!(w>=6 && w<=15) || !(h>=6 && h<=15))
                {
                    throw eroare_dimensiuni("Dimensiuni gresite!!");
                }
            }
            catch (eroare_dimensiuni &e)
            {
                std::cout<<e.what()<<"\n";
                ok=true; //se citeste din nou
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
            try{
                if(aux!="start"){
                    throw nu_incepem("take your time !\nRemeber, to start type \"start\" and press enter!\n");
                }
            }
            catch(nu_incepem &err){
                std::cout<<err.what()<<"\n";
                ok=true;
            }


        }
        while(ok);

        joc.run();
    }

};


int main() {

    srand(time(nullptr));
    Meniu m;
    m.start();
    return 0;
}
