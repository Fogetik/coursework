#include <iostream>
#include "node.h"
#include "comparator.h"
#include "rbTree.h"
#include <cstring>
#include <string>
#include <cstdlib>
#include <locale.h>
#include <forward_list>

using std::string;
using std::cout;
using std::cin;

string generateFirstName(bool);

string generateSecondName(bool);

string generateThirdName(bool);

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


    setlocale(LC_CTYPE, "rus");
    test();
    return 0;
}



void test(){
    srand(time(NULL));
    for (int i = 0; i < 30; i++)
    {
        cout << generateFirstName(true) << " " <<generateSecondName(true) << " " << generateThirdName(true) << endl;
        cout << generateFirstName(false) << " " <<generateSecondName(false) << " " << generateThirdName(false) << endl;
    }



////    string a = "Иванова","Смирнов","Кузнецов","Попов", "Васильев", "Петров", "Соколов", "Михайлов", "Новиков", "Федоров",
////    "Морозов", "Волков", "Алексеев", "Лебедев", "Семенов", "Егоров", "Павлов", "Козлов", "Степанов", "Николаев",
////    "Орлов", "Андреев", "Макаров", "Никитин", "Захаров", "Зайцев", "Соловьев", "Борисов", "Яковлев", "Григорьев",
////    "Романов", "Воробьев", "Сергеев", "Кузьмин", "Фролов", "Александров",
//    char *a = "0,2234 37 Дмитриев 0,2171 38 Королев 0,2083 39 Гусев 0,2075 40 Киселев 0,2070 41 Ильин 0,2063 42 Максимов 0,2059 43 Поляков 0,2035 44 Сорокин 0,1998 45 Виноградов 0,1996 46 Ковалев 0,1978 47 Белов 0,1964 48 Медведев 0,1953 49 Антонов 0,1928 50 Тарасов 0,1896 51 Жуков 0,1894 52 Баранов 0,1883 53 Филиппов 0,1827 54 Комаров 0,1799 55 Давыдов 0,1767 56 Беляев 0,1750 57 Герасимов 0,1742 58 Богданов 0,1706 59 Осипов 0,1702 60 Сидоров 0,1695 61 Матвеев 0,1693 62 Титов 0,1646 63 Марков 0,1628 64 Миронов 0,1625 65 Крылов 0,1605 66 Куликов 0,1605 67 Карпов 0,1584 68 Власов 0,1579 69 Мельников 0,1567 70 Денисов 0,1544 71 Гаврилов 0,1540 72 Тихонов 0,1537 73 Казаков 0,1528 74 Афанасьев 0,1516 75 Данилов 0Савельев Тимофеев Фомин Чернов Абрамов Мартынов Ефимов Федотов Щербаков Назаров Калинин Исаев Чернышев Быков  Маслов Родионов  Коновалов Лазарев Воронин Климов Филатов Пономарев Голубев Кудрявцев Прохоров Наумов Потапов Журавлев Овчинников Трофимов Леонов Соболев Ермаков Колесников Гончаров Емельянов  Никифоров Грачев Котов Гришин  Ефремов Архипов Громов Кириллов Малышев ";
//    char *b = new char[1078], *c = new char[1078];
//    char *asd = " \"";
//    char *asd1 = "\", ";
//    char *asd2 = "а\", ";
//    char *sym = new char[1];
//    bool as = false;
//    int k1 = 0, k2 = 0;
//    for (int i = 0; a[i]!= '\0'; i++){
//        sym[0] = a[i];
//        cout << sym[0];
//        if ((sym[0] >= '0' && sym[0] <= '9')||sym[0] == ','){
//            continue;
//        }
//        if (sym[0]!=' ')
//        {
//            if (!as){
//                as = true;
//                b[k1++] = ' ';
//                c[k2++] = ' ';
//                b[k1++] = '\"';
//                c[k2++] = '\"';
////                strcpy(b,asd);
////                strcpy(c, asd);
////                b += " \"";
////                c += " \"";
//            }
//            b[k1++] = sym[0];
//            c[k2++] = sym[0];
////            strcpy(b, sym[0]);
////            strcpy(c, sym[0]);
////            b += sym;
////            c += sym;
//        }
//        else
//            if (as){
//                as = false;
//                b[k1++] = '\"';
//                c[k2++] = 'а';
//                c[k2++] = '\"';
//                b[k1++] = ',';
//                c[k2++] = ',';
//                b[k1++] = ' ';
//                c[k2++] = ' ';
////                strcpy(b,asd1);
////                strcpy(c, asd2);
////                b += "\",";
////                c += "а\",";
//            }
//    }
//    cout << endl;
//    cout << a << endl <<  b << endl << c << endl;
}