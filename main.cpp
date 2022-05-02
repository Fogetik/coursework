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



////    string a = "�������","�������","��������","�����", "��������", "������", "�������", "��������", "�������", "�������",
////    "�������", "������", "��������", "�������", "�������", "������", "������", "������", "��������", "��������",
////    "�����", "�������", "�������", "�������", "�������", "������", "��������", "�������", "�������", "���������",
////    "�������", "��������", "�������", "�������", "������", "�����������",
//    char *a = "0,2234 37 �������� 0,2171 38 ������� 0,2083 39 ����� 0,2075 40 ������� 0,2070 41 ����� 0,2063 42 �������� 0,2059 43 ������� 0,2035 44 ������� 0,1998 45 ���������� 0,1996 46 ������� 0,1978 47 ����� 0,1964 48 �������� 0,1953 49 ������� 0,1928 50 ������� 0,1896 51 ����� 0,1894 52 ������� 0,1883 53 �������� 0,1827 54 ������� 0,1799 55 ������� 0,1767 56 ������ 0,1750 57 ��������� 0,1742 58 �������� 0,1706 59 ������ 0,1702 60 ������� 0,1695 61 ������� 0,1693 62 ����� 0,1646 63 ������ 0,1628 64 ������� 0,1625 65 ������ 0,1605 66 ������� 0,1605 67 ������ 0,1584 68 ������ 0,1579 69 ��������� 0,1567 70 ������� 0,1544 71 �������� 0,1540 72 ������� 0,1537 73 ������� 0,1528 74 ��������� 0,1516 75 ������� 0�������� �������� ����� ������ ������� �������� ������ ������� �������� ������� ������� ����� �������� �����  ������ ��������  ��������� ������� ������� ������ ������� ��������� ������� ��������� �������� ������ ������� �������� ���������� �������� ������ ������� ������� ���������� �������� ���������  ��������� ������ ����� ������  ������� ������� ������ �������� ������� ";
//    char *b = new char[1078], *c = new char[1078];
//    char *asd = " \"";
//    char *asd1 = "\", ";
//    char *asd2 = "�\", ";
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
//                c[k2++] = '�';
//                c[k2++] = '\"';
//                b[k1++] = ',';
//                c[k2++] = ',';
//                b[k1++] = ' ';
//                c[k2++] = ' ';
////                strcpy(b,asd1);
////                strcpy(c, asd2);
////                b += "\",";
////                c += "�\",";
//            }
//    }
//    cout << endl;
//    cout << a << endl <<  b << endl << c << endl;
}