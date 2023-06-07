//
// Created by Paula on 5/21/2023.
//

#include "../headers/Lane.h"

std::shared_ptr<Lane> Lane::clone(){
    return std::make_shared<Lane>(*this);
}
std::shared_ptr<Lane> fastLane::clone(){
    return std::make_shared<fastLane>(*this);
}
std::shared_ptr<Lane> freeLane::clone(){
    return std::make_shared<freeLane>(*this);
}
std::shared_ptr<Lane> waterLane::clone(){
    return std::make_shared<waterLane>(*this);
}

Lane::Lane(int width, int dir, int rate): direction(dir), SpawnRate(rate) {
    if(width!=10 || dir!=0 && dir!=1 || rate<0 && rate>100){
        throw eroare_lane("Latime gresita?");
    }
    for(int i=0; i<width;i++)
    {
        cars.push_front(0);
    }
}

void Lane::move() {
    int c; //masina ==1
    if(rand()%100<SpawnRate) //sanse sa intre o masina pe drum
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

int Lane::trackPosition(int pos) {
    return cars[pos];
}

std::ostream& operator<<(std::ostream& out, const Lane &l) {
    out<<"Afisare dimensiune banda: ";
    out<<l.cars.size()<<"\n";
    return out;
}

void fastLane::move()  {
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

freeLane::freeLane(int width){

    for(int i=0; i<width;i++)
    {
        cars.push_front(3);
    }
}

void freeLane::move() {
    //nimic
    //sta pe loc
}
waterLane::waterLane(int width) {
    for(int i=0; i<width;i++)
    {
        if(i%2==1){
            cars.push_front(5);
        }
        else{
            cars.push_front(4);
        }

    }
}
