//
// Created by danil on 02.05.2022.
//

#ifndef KURSAH_GENERATOR_H
#define KURSAH_GENERATOR_H

#include <string>

using std::string;

string generateFirstName(bool male);

string generateSecondName(bool male);

string generateThirdName(bool male);


class FirstPage{
public:
    virtual void generatePage() = 0;
    virtual unsigned char* transformData() = 0;
    virtual ~FirstPage()= default;
};

class SecondPage{
public:
    virtual void generatePage() = 0;
    virtual ~SecondPage()= default;
};

class GenerateTaxReport{
public:
    virtual FirstPage *generateFirstPage()const= 0;
    virtual SecondPage *generateSecondPage()const = 0;
    virtual ~GenerateTaxReport()= default;;
};

class FirstPageAddedProfit : public FirstPage{
private:
    unsigned long long inn, kpp;
    bool male;
    unsigned int year;
    unsigned int tax_authority_code;
    unsigned long long phone_number;
    string fio[3];
public:
    FirstPageAddedProfit()= default;
    void generatePage() override;
    unsigned char* transformData() override;

    ~FirstPageAddedProfit() = default;
};

class SecondPageAddedProfit : public SecondPage{
public:
    void generatePage() override{

    }
    ~SecondPageAddedProfit() = default;
};

class GenerateTaxReportAddedProfit:public GenerateTaxReport{
public:
    FirstPage* generateFirstPage()const override{
        return new FirstPageAddedProfit();
    }
    SecondPage *generateSecondPage()const override{
        return new SecondPageAddedProfit();
    }
    ~GenerateTaxReportAddedProfit() = default;
};





#endif //KURSAH_GENERATOR_H
