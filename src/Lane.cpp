//
// Created by Paula on 5/21/2023.
//

#include "../headers/Lane.h"

Lane::Lane(int width) {
    if(width>15){
        throw eroare_lane1("Esti prea ambitios, latime mai mica!");
    }
    if(width<5){
        throw eroare_lane2("Fii mai ambitios! Latime mai mare!");
    }
    for(int i=0; i<width;i++)
    {
        cars.push_front(0);
    }
}

void Lane::move() {
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

freeLane::freeLane(int width) {

    for(int i=0; i<width;i++)
    {
        cars.push_front(3);
    }
}

void freeLane::move() {
    //nimic
    //sta pe loc
}