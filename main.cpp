#include <iostream>
#include "node.h"
#include "comparator.h"
#include "rbTree.h"

using std::cout;
using std::cin;

int main() {

    std::cout << "Hello, World!" << std::endl;
    rbTree<int> tree;
    tree.setComparator(new ComparatorInt());
    Node<int> a;
    a.key = 4;
    tree.addNode(a);
    a.key = 5;
    tree.addNode(a);
    a.key = 6;
    tree.addNode(a);
    return 0;
}
