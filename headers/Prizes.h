//
// Created by Paula on 6/19/2023.
//

#ifndef OOP_PRIZES_H
#define OOP_PRIZES_H
#include <vector>
#include <iostream>


template <typename T> class Prizes{
    static std::vector<T> prizes;
    std::vector<T> aux;
    static bool ok;
    const std::string consolare = "\n(\\_/)\n"
                        "( -,-)\n"
                        "(\")_(\")\n";
public:
    Prizes(){}
    explicit Prizes(const std::vector<T> &arr);
    static std::vector<T> get_p();
    int getsize();
    friend std::ostream& operator<<(std::ostream& o,const Prizes<T> &obj){
        o<<obj.consolare;
        return o;
    }
    void winner(int h){
        if(h<10){ // "dificultate mai scazuta", unul din premii va fi scos
            prizes.pop_back();
        }
    }
};

template<typename T>
int Prizes<T>::getsize() {
    return prizes.size();
}

template<typename T>
std::vector<T> Prizes<T>::get_p() {
    return prizes;
}

template<typename T>
Prizes<T>::Prizes(const std::vector<T> &arr):aux(arr){
    if(ok==0){
        ok=1;
        prizes=aux;
    }
}

template<typename T> std::vector<T> Prizes<T>::prizes;
template<typename T> bool Prizes<T>::ok=0;
#endif //OOP_PRIZES_H
