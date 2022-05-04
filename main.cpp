#include <iostream>
#include "node.h"
#include "rbTree.h"
#include "generator.h"
#include "comparator.h"
#include <cstring>
#include <string>
#include <cstdlib>
#include <locale.h>
#include <forward_list>
#include <windows.h>
#include <fstream>
#include <chrono>

using std::string;
using std::cout;
using std::cin;

void test();

int main() {
    /*rbTree<int> tree;
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
    test();
    return 0;
}



void test(){
    srand(time(NULL));
    GenerateTaxReportAddedProfit reportAddedProfit;
    FirstPage* firstPage = reportAddedProfit.generateFirstPage();
    std::fstream file;
    for (int step = 1; step <= 10; step++) {
        file.open("db.txt", std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);
        auto begin = std::chrono::steady_clock::now();

        for (int i = 0; i < 1'000'000; i++) {
            firstPage->generatePage();
            file << firstPage->transformData() << endl;
        }


        auto end = std::chrono::steady_clock::now();

        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

        std::cout << "The time: " << elapsed.count() << " ms\n";
        file.close();
    }
}