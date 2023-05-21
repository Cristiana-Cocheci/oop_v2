//
// Created by Paula on 5/21/2023.
//


#ifndef OOP_ERORI_H
#define OOP_ERORI_H

#include <stdexcept>

class eroare_generala : public std::logic_error{
public:
    explicit eroare_generala(const std::string &err) noexcept;
};
class eroare_dimensiuni : public eroare_generala{
public:
    explicit eroare_dimensiuni(const std::string &err) noexcept;
};
class nu_incepem :public eroare_generala{
public:
    explicit nu_incepem(const std::string &err) noexcept;
};
class eroare_lane: public eroare_generala{
public:
    explicit eroare_lane(const std::string &err) noexcept;
};
class eroare_lane1: public eroare_lane{
public:
    explicit eroare_lane1(const std::string &err) noexcept;
};
class eroare_lane2: public eroare_lane{
public:
    explicit eroare_lane2(const std::string &err) noexcept;
};


#endif //OOP_ERORI_H