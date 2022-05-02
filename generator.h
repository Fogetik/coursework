//
// Created by danil on 02.05.2022.
//

#ifndef KURSAH_GENERATOR_H
#define KURSAH_GENERATOR_H

#include <string>
#include "strings.h"

using std::string;

class FirstPage{
public:
    virtual void generatePage() = 0;
    virtual ~FirstPage(){};
};

class SecondPage{
public:
    virtual void generatePage() = 0;
    virtual ~SecondPage(){};
};

class GenerateTaxReport{
public:
    virtual FirstPage *generateFirstPage()const= 0;
    virtual SecondPage *generateSecondPage()const = 0;
    virtual ~GenerateTaxReport(){};
};


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

#endif //KURSAH_GENERATOR_H
