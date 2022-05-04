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
    if (male){
        return secondName1[key];
    }
    else{
        return secondName2[key];
    }
}

string generateThirdName(bool male)
{
    int key;
    key = rand() % 32;
    if (male){
        return thirdName1[key];
    }
    else{
        return thirdName2[key];
    }
}

void FirstPageAddedProfit::generatePage() {
    int general_inn_kpp = rand()%100;
    this->inn = 7700000000+ general_inn_kpp * 100000 + rand()%1'000'000;
    this->kpp = 770001001 + general_inn_kpp * 100000;
    this->male = (bool)(rand()%2);
    this->fio[0] = generateSecondName(male);
    this->fio[1] = generateFirstName(male);
    this->fio[2] = generateThirdName(male);
    this->year = 2010 + rand()%13;
    this->tax_authority_code = (rand()%90+10)*100 + rand()%100;
    this->phone_number = (79 * 100 + rand()%100);
    this->phone_number *= 10'000'000;
    this->phone_number += rand()%10'000'000;
}

unsigned char* FirstPageAddedProfit::transformData() {
    unsigned char *data, *data_ptr;
    data = new unsigned char[43 + this->fio[0].length() + 1 + this->fio[1].length() + 1 + this->fio[2].length() + 1 + 1];
    data_ptr = data;
    char*number = new char[10];
    ulltoa(this->inn, number, 10);
    for(int i = 0; i < 10; i++){
        *data_ptr = *number;
        number++;
        data_ptr++;
    }
    number-=10;
    delete[] number;

    *data_ptr = '|';
    data_ptr++;

    number = new char[9];
    ulltoa(this->kpp, number, 10);
    for(int i = 0; i < 9; i++){
        *data_ptr = *number;
        number++;
        data_ptr++;
    }
    number -=9;
    delete[] number;

    *data_ptr = '|';
    data_ptr++;

    number = new char[4];
    _itoa(this->year, number, 10);
    for(int i = 0; i < 4; i++){
        *data_ptr = *number;
        number++;
        data_ptr++;
    }
    number-=4;
    delete[] number;

    *data_ptr = '|';
    data_ptr++;

    number = new char[4];
    _itoa(this->tax_authority_code, number, 10);
    for(int i = 0; i < 4; i++){
        *data_ptr = *number;
        number++;
        data_ptr++;
    }
    number-=4;
    delete[] number;

    *data_ptr = '|';
    data_ptr++;

    number = new char[11];
    ulltoa(this->phone_number, number, 10);
    for(int i = 0; i < 11; i++){
        *data_ptr = *number;
        number++;
        data_ptr++;
    }
    number-=11;
    delete[] number;


    *data_ptr = '|';
    data_ptr++;
    for(int choice = 0; choice < 3; choice++) {
        for (char i: fio[choice]) {
            *data_ptr = i;
            data_ptr++;
        }

        *data_ptr = '|';
        data_ptr++;
    }
    *data_ptr = '\0';
    return data;
}
