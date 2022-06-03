#include <iostream>
#include "rbTree.h"
#include "generator.h"
#include "database.h"
#include <string>
#include <cstdlib>
#include <clocale>
#include <forward_list>
#include <windows.h>
#include <chrono>
#include <utility>

using std::string;
using std::cout;
using std::cin;

void test();

void test1();
string* merge(string *a, int, string *b, int);
int absolute_frequency(DataBase&, string, string);
double relative_frequency(DataBase&, string, string);

int main() {
/*    rbTree<int> tree;
    tree.setComparator(new ComparatorInt());
    Node<int> a;
    a.key = 4;
    tree.addNode(a);
    a.key = 5;
    tree.addNode(a);
    a.key = 3;
    tree.addNode(a);
    a.key = 2;
    tree.addNode(a);

    tree.deleteNode(3);

//    a.key = 6;
//    tree.addNode(a);*/
    setlocale(LC_ALL, "rus");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    try {
        //test1();
        test();
    }catch(std::exception& e){
        cout << e.what() << endl;
    }
    return 0;
}

void test() {
    srand(time(nullptr));
    GenerateTaxReportAddedProfit reportAddedProfit;
    FirstPage* firstPage = reportAddedProfit.generateFirstPage();
    SecondPage* secondPage = reportAddedProfit.generateSecondPage();
    DataBaseRBT db(20);
    string n[] = {"inn" , "kpp", "year", "tax_authority_code", "phone_number", "second_name", "first_name", "third_name",
                  "city_birth", "current_city", "postal_code", "series", "number", "year_extradition", "amount_income",
                  "amount_income_no", "amount_income_yes", "bank_name", "bank_account", "amount_tax_deductions"};
    db.setNameColumns(n);

    auto begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 1000; i++) {
        firstPage->generatePage();
        secondPage->generatePage();
        db.insert(merge(firstPage->transformData(), 8, secondPage->transformData(), 12));
    }

    vector<string*>vector1 = db.find("first_name", "Danila");

    if (!vector1.empty()){
        cout << "-----------" << endl;
        for (auto str_ptr : vector1){
            for (int i = 0; i < db.getCountColumns(); i++)
                cout << str_ptr[i] << " | ";

            cout << endl;
        }
    }
    else
        cout << "pizdec"<<endl;

    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed.count() << " ms\n";
//    begin = std::chrono::steady_clock::now();
////    db.show();
//    cout << "---" << endl;
//    vector<string*> a = db.find("year", "2009");
//    end = std::chrono::steady_clock::now();
//    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
//    std::cout << "The time: " << elapsed.count() << " ms\n";
//    begin = std::chrono::steady_clock::now();
//    for (string* line : a){
//        db.remove(line[0] );
////        delete[]line;
//    }
//    cout << "---" << endl;
//
//    std::cout << "The time: " << elapsed.count() << " ms\n";
//    db.drop();




    /*
    srand(time(nullptr));
    DataBaseRBT db(8);
    string n[] = {"inn", "kpp", "year", "tax_authority_code", "phone_number", "second_name", "first_name",
                  "third_name"};
    GenerateTaxReportAddedProfit reportAddedProfit;
    FirstPage *firstPage = reportAddedProfit.generateFirstPage();
    db.setNameColumns(n);
    auto begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 250; i++) {
        firstPage->generatePage();
        db.insert(firstPage->transformData());
    }
//    db.show();
    vector<string*>vector1 = db.find("year", "1975");

    if (!vector1.empty()){
        cout << "-----------" << endl;
        for (auto str_ptr : vector1){
            for (int i = 0; i < db.getCountColumns(); i++)
                cout << str_ptr[i] << " | ";

            cout << endl;
        }
    }
    else
        cout << "pizdec"<<endl;

    vector1 = db.find("id", "201");

    if (!vector1.empty()){
        cout << "-----------" << endl;
        for (auto str_ptr : vector1){
            for (int i = 0; i < db.getCountColumns(); i++)
                cout << str_ptr[i] << " | ";

            cout << endl;
        }
    }


//    db.remove(std::to_string(28));
//    db.remove(std::to_string(0));
//    db.remove(std::to_string(3));
//    db.remove(std::to_string(45));
//    db.show();
//    db.remove(std::to_string(20));
//    db.show();

//    srand(time(nullptr));
//    for (int i = 0; i < 250; i++){
////        cout << "---------------------------------------------------------------------------" << endl;
//        int index = rand() % count;
////        cout << "remove id: " << index << endl << endl;
//        db.remove(std::to_string(index));
////        cout << endl;
//        count--;
//    }

//    db.show();
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed.count() << " ms\n";*/
}

void test1(){
    srand(time(nullptr));
    GenerateTaxReportAddedProfit reportAddedProfit;
    FirstPage* firstPage = reportAddedProfit.generateFirstPage();
    DataBaseList db(8);
    string n[] = {"inn" , "kpp", "year", "tax_authority_code", "phone_number", "second_name", "first_name", "third_name"};
    db.setNameColumns(n);
    string answers, name_column;
    int count;
    vector<string*> vector1;
    while(true) {
        cout << ">";
        cin >> answers;
        if (answers == "exit")
            break;

        if (answers == "show"){
            db.show();
        }
        else if (answers == "remove"){
            cout << "id:";
            cin >> answers;
            db.remove(answers);
        }
        else if (answers == "generate"){
            firstPage->generatePage();
            db.insert(firstPage->transformData());
        }
        else if (answers == "generate_n"){
            cout << "count:";
            cin >> count;
            for(int i = 0; i < count; i++){
                firstPage->generatePage();
                db.insert(firstPage->transformData());
            }
        }
        else if (answers == "find"){
            cout << "name of column:";
            cin >> name_column;
            cout << "the word to search for:";
            cin >> answers;
            cout << endl;
            vector1 = db.find(name_column, answers);
            if (!vector1.empty()){
                for (auto str_ptr : vector1){
                    for (int i = 0; i < db.getCountColumns(); i++)
                        cout << str_ptr[i] << " | ";

                    cout << endl;
                }
            }
        }
        else if (answers == "absolute"){
            cout << "name of column:";
            cin >> name_column;
            cout << "the word to search for:";
            cin >> answers;
            cout << endl;
            cout << "absolute frequency:" << absolute_frequency(db, name_column, answers) << endl;
        }
        else if (answers == "relative"){
            cout << "name of column:";
            cin >> name_column;
            cout << "the word to search for:";
            cin >> answers;
            cout << endl;
            cout << "relative frequency:" << relative_frequency(db, name_column, answers) << endl;
        }
        else{
            cout << "incorrect input..." << endl;
        }

    }

    db.drop();
}

string* merge(string *a, int count_a, string *b, int count_b){
    string* result = new string[count_a+count_b];
    for (int i = 0; i < count_a; i++){
        result[i] = a[i];
    }

    for (int i = 0; i < count_b; i++){
        result[i + count_a] = b[i];
    }

    delete []a;
    delete []b;
    return result;
}


int absolute_frequency(DataBase& db, string name_column, string word){
    int count = 0;
    vector<string*> vector1 = db.find(std::move(name_column), std::move(word));
    if (!vector1.empty()){
        for ([[maybe_unused]] auto str_ptr : vector1)
            count++;
    }

    return count;
}

double relative_frequency(DataBase& db, string name_column, string word){
    double count = 0, all;
    vector<string*> vector1 = db.find(std::move(name_column), std::move(word));
    if (!vector1.empty()){
        for ([[maybe_unused]] auto str_ptr : vector1)
            count++;
    }

    all = db.getCountStr();
    return (count / all);
}
