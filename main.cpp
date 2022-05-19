#include <iostream>
#include "node.h"
#include "rbTree.h"
#include "generator.h"
#include "comparator.h"
#include "database.h"
#include <cstring>
#include <string>
#include <cstdlib>
#include <locale.h>
#include <forward_list>
#include <windows.h>
#include <fstream>
#include <chrono>
#include <utility>

using std::string;
using std::cout;
using std::cin;

void test();

void test1();

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
    test();
//    test1();
    return 0;
}

void test() {
    /*srand(time(nullptr));
    GenerateTaxReportAddedProfit reportAddedProfit;
    FirstPage* firstPage = reportAddedProfit.generateFirstPage();
    DataBaseList db(8);
    string n[] = {"inn" , "kpp", "year", "tax_authority_code", "phone_number", "second_name", "first_name", "third_name"};
    db.setNameColumns(n);
    for (int step = 1; step <= 10; step++) {
        auto begin = std::chrono::steady_clock::now();
        for (int i = 0; i < 2'000'000; i++) {
            firstPage->generatePage();
            db.insert(firstPage->transformData());
        }

        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::cout << "The time: " << elapsed.count() << " ms\n";
        db.drop();
    }*/
    DataBaseRGT db(8);
    string n[] = {"inn", "kpp", "year", "tax_authority_code", "phone_number", "second_name", "first_name",
                  "third_name"};
    GenerateTaxReportAddedProfit reportAddedProfit;
    FirstPage *firstPage = reportAddedProfit.generateFirstPage();
    db.setNameColumns(n);
    int count = 50;
    for (int i = 0; i < count; i++) {
        firstPage->generatePage();
        db.insert(firstPage->transformData());
    }
    db.show();

//    db.remove(std::to_string(28));
//    db.remove(std::to_string(0));
//    db.remove(std::to_string(3));
//    db.remove(std::to_string(45));
//    db.show();
//    db.remove(std::to_string(20));
//    db.show();

    srand(time(nullptr));
    for (int i = 0; i < 20; i++){
        cout << "---------------------------------------------------------------------------" << endl;
        int index = rand() % count;
        cout << "remove id: " << index << endl << endl;
        db.remove(std::to_string(index));
        db.show();
        cout << endl;
        count--;
    }

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
