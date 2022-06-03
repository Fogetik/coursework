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
    key = rand() % 78;
    if (male)
        return secondName1[key];
    else
        return secondName2[key];

}

string generateThirdName(bool male)
{
    int key;
    key = rand() % 31;
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
    auto *res = new string [8];
    res[0] = std::to_string(this->inn);
    res[1] = std::to_string(this->kpp);
    res[2] = std::to_string(this->year);
    res[3] = std::to_string(this->tax_authority_code);
    res[4] = std::to_string(this->phone_number);
    res[5] = this->fio[0];
    for (size_t i = res[5].length(); i < 15; i++)
        res[5] += " ";

    res[6] = this->fio[1];
    for (size_t i = res[6].length(); i < 15; i++)
        res[6] += " ";

    res[7] = this->fio[2];
    for (size_t i = res[7].length(); i < 19; i++)
        res[7] += " ";

    return res;
}

void SecondPageAddedProfit::generatePage() {
    this->city_birth = cities[rand()%39];
    this->current_city = cities[rand()%39];
    this->postal_code = 140000+rand()%10000;
    this->series = 4000 + rand()%1000;
    this->number = rand()%300000+200000;
    this->year_extradition = 1980 + rand()%20;
    this->amount_income = 1000000 + rand()%1000000;
    this->amount_income_no = rand()%200000 + 400000;
    this->amount_income_yes = this->amount_income - this->amount_income_no;
    this->bank_name = banks[rand()%7];
    this->bank_account = 4106400000000000 + rand()%10000*10000 + rand()%10000;
    this->amount_tax_deductions = rand()%26000 + 26000;
}

string* SecondPageAddedProfit::transformData() {
    auto *res = new string [12];
    res[0] = this->city_birth;
    for (size_t i = res[0].length(); i < 14; i++)
        res[0] += " ";

    res[1] = this->current_city;
    for (size_t i = res[1].length(); i < 14; i++)
        res[1] += " ";

    res[2] = std::to_string(this->postal_code);
    res[3] = std::to_string(this->series);
    res[4] = std::to_string(this->number);
    res[5] = std::to_string(this->year_extradition);
    res[6] = std::to_string(this->amount_income);
    res[7] = std::to_string(this->amount_income_no);
    res[8] = std::to_string(this->amount_income_yes);
    res[9] = bank_name;
    for (size_t i = res[9].length(); i < 15; i++)
        res[9] += " ";

    res[10] = std::to_string(this->bank_account);
    res[11] = std::to_string(this->amount_tax_deductions);
    return res;
}