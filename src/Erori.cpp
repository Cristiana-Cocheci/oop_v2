//
// Created by Paula on 5/21/2023.
//


#include "../headers/erori.h"

eroare_generala::eroare_generala(const std::string &err) noexcept: std::logic_error(err){};

eroare_dimensiuni::eroare_dimensiuni(const std::string &err) noexcept :eroare_generala(err){}

nu_incepem::nu_incepem(const std::string &err) noexcept :eroare_generala(err){}

eroare_lane::eroare_lane(const std::string &err) noexcept :eroare_generala(err){}

eroare_lane1::eroare_lane1(const std::string &err) noexcept :eroare_lane(err){}

eroare_lane2::eroare_lane2(const std::string &err) noexcept :eroare_lane(err){}