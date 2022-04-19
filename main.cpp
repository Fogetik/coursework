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
    a.key = 1;
    tree.addNode(a);
    a.key = 2;
    tree.addNode(a);
    a.key = 0;
    tree.addNode(a);
    return 0;
}
