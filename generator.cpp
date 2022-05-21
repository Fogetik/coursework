//
// Created by danil on 03.05.2022.
//
#include "generator.h"
#include "strings.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
using std::cout;

string generateFirstName(bool male)
{
    int key;
    if (male){
        key = rand() % 33;
        return firstName1[key];
    }
    else{
        key = rand() % 40;
        return firstName2[key];
    }
}

string generateSecondName(bool male)
{
    int key;
    key = rand() % 81;
    if (male)
        return secondName1[key];
    else
        return secondName2[key];

}

string generateThirdName(bool male)
{
    int key;
    key = rand() % 32;
    if (male)
        return thirdName1[key];
    else
        return thirdName2[key];

}

void FirstPageAddedProfit::generatePage() {
    int general_inn_kpp = rand()%100;
    this->inn = 7700000000+ general_inn_kpp * 100000 + rand()%1'000'000;
    this->kpp = 770001001 + general_inn_kpp * 100000;
    this->male = (bool)(rand()%2);
    this->fio[0] = generateSecondName(male);
    this->fio[1] = generateFirstName(male);
    this->fio[2] = generateThirdName(male);
    this->year = 2000 + rand()%23;
    this->tax_authority_code = (rand()%90+10)*100 + rand()%100;

    this->phone_number = (79 * 100 + rand()%100);
    this->phone_number *= 10'000'000;
    this->phone_number += rand()%10'000'000;
}

string* FirstPageAddedProfit::transformData() {
    string *res = new string [8];
    res[0] = std::to_string(this->inn);
    res[1] = std::to_string(this->kpp);
    res[2] = std::to_string(this->year);
    res[3] = std::to_string(this->tax_authority_code);
    res[4] = std::to_string(this->phone_number);
    res[5] = this->fio[0];
    res[6] = this->fio[1];
    res[7] = this->fio[2];
    return res;
}
