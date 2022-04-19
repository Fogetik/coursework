//
// Created by danil on 05.04.2022.
//

#ifndef KURSAH_RBTREE_H
#define KURSAH_RBTREE_H
#include "node.h"
#include "comparator.h"
#include <iostream>
#include <stack>

using std::cout;
using std::endl;
using std::stack;

template<class T>
class rbTree{
private:
    Comparator<T>* compare;
    Node<T> *root = nullptr;
//    void balance();
public:
    void addNode(Node<T>);
//    rbTree(Comparator<T>*, Node<T>&);
//    rbTree(Comparator<T>);
    void setComparator(Comparator<T>* comparator);

};

template<class T>
void rbTree<T>::setComparator(Comparator<T> *comparator) {
    this->compare = comparator;
}

template<class T>
void rbTree<T>::addNode(Node<T> node) {
    cout << "adding node..." << endl;
    stack<Node<T>*> stack1;
    if (this->root == nullptr)
    {
        //todo: think use operator= or use self equal
        this->root = new Node<T>;
        node.drawBlack();
        root->copy(node);
        return;
    }

    Node<T> *point = this->root;
    while (true) {
        stack1.push(point);
        if (this->compare->compare(node, *point)) {
            if (point->rightNode == nullptr)
                break;

            point = point->rightNode;
        }
        else {
            if (point->leftNode == nullptr)
                break;

            point = point->leftNode;
        }
    }

    stack1.push(point);
    if (this->compare->compare(node, *point))
    {
        point->rightNode = new Node<T>;
        point = point->rightNode;
    }
    else
    {
        point->leftNode = new Node<T>;
        point = point->leftNode;
    }

    point->copy(node);
    point->drawRed();

    Node<T> *parent;
    parent = stack1.top();
    stack1.pop();
    if (parent->isRed())
    {
        Node<T>* grandgrandParent, *grandParent, * uncle;
        grandParent = stack1.top();
        if (grandParent->isBlack()){
            parent->drawRed();
            grandParent->drawBlack();
            //todo:make small turn

        }




    }


}



#endif //KURSAH_RBTREE_H
