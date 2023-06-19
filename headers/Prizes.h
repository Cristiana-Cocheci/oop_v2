//
// Created by Paula on 6/19/2023.
//

#ifndef OOP_PRIZES_H
#define OOP_PRIZES_H
#include <vector>

/*
template <typename T> requires (!std::convertible_to<T, std::string>)
friend std::ostream & operator<<(std::ostream& out, const T& obj){
    out<< "AFISARE: [";
    for(const auto& elem: obj){
        out<< elem<< " ";
    }
    out<< "]\n";
    return out;

}
*/

template <typename T> class Prizes{
    std::vector<T> prizes;
    int size;
public:
    Prizes(const std::vector<T> arr, int l):prizes(arr), size(l){}
};


#endif //OOP_PRIZES_H
