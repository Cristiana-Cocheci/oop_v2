#include <bits/stdc++.h>
#include <rlutil.h>
#include <time.h>

class Car{

};
class Lane
{
private:
    std::deque<bool> cars;
public:
    Lane(int width)
    {
        for(int i=0; i<width;i++)
        {
            cars.push_front(false);
        }
    }
    void move()
    {
        if(rand()%10==1)
        {
            cars.push_front(true);
        }
        else
        {
            cars.push_front(false);
        }
        cars.pop_back();
    }
    bool trackPosition(int pos){return cars[pos];}
};
class Player{
private:
    int x,y, noLanes, mapWidth;
public:
    Player(int width, int height){x=width/2;y=0, noLanes=height, mapWidth=width;}
    Player(const Player& other): x(other.x),y(other.y){};
    Player& operator=(const Player& other)
    {
        x=other.x;
        y=other.y;
        return *this;
    }
    int getX() const{return x;}
    int getY() const{return y;}
    void MoveLeft(){if(x>0)x--;}
    void MoveRight(){if(x<mapWidth-1)x++;}
    void MoveUp(){if(y<noLanes-1)y++;}
    void MoveDown(){if(y>0)y--;}
    void reset(){y=0;x=mapWidth/2;}

};
class Game{
private:
    bool quit;
    int noLanes;
    int mapWidth;
    int score;
    Player *player;
    std::vector <Lane*> map;
public:
    Game(int w=20, int h=10, int score_=0)
    {
        score=score_;
        noLanes=h;
        mapWidth=w;
        quit=false;
        for(int i=0;i<noLanes;i++) {
            map.push_back(new Lane(mapWidth));
        }
        player= new Player(mapWidth, noLanes);

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
                if(map[i]->trackPosition(j) && i>0 && i<noLanes-1)
                { std::cout << "c "; }
                else if(player->getX()==j && player->getY()==i)
                { std::cout <<"P "; }
                else
                { std::cout<<" "; }
            }
            std::cout<<"\n";
        }
        std::cout <<"Score "<<score<<"\n";
    }
    void input()
    {
        if(kbhit())
        {
            char current = getch();
            if(current=='a'){player->MoveLeft();}
            if(current=='w'){player->MoveUp();}
            if(current=='s'){player->MoveDown();}
            if(current=='d'){player->MoveRight();}
            if(current=='q'){quit=true;}
        }
    }
    void logic(){
        for(int i=1;i<noLanes-1;i++)
        {
            if(rand()%10==1)
            {
                map[i]->move();
            }
            if(map[i]->trackPosition(player->getX()) && player->getY()==i) {
                quit = true;
                std::cout << "YOU LOSE ;-(\n";
            }
        }
        if(player->getY()==noLanes-1)
        {
            /*quit=true;
            std::cout<< "YOU WIN!!!!\n";*/
            score++;
            player->reset();
        }
    }
    void run()
    {
        while(!quit)
        {
            input();
            draw();
            logic();
        }
    }
};

int main() {
    srand(time(NULL));
    Game joc(30,5);
    joc.run();
    std::string aux;
    std::cin>>aux;
    return 0;
}
