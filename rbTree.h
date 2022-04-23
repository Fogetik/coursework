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
    void balanceAdd(stack<Node<T>*>&);
public:
    Node<T>* smallTurnRight(Node<T>*, bool);
    Node<T>* smallTurnLeft(Node<T>*, bool);
    void addNode(Node<T>);
    void deleteNode(T k);
//    rbTree(Comparator<T>*, Node<T>&);
//    rbTree(Comparator<T>);
    void setComparator(Comparator<T>* comparator);

};

template<class T>
void rbTree<T>::setComparator(Comparator<T> *comparator) {
    this->compare = comparator;
}

template<class T>
Node<T>* rbTree<T>::smallTurnLeft(Node<T>* grandFather, bool rightSon){
    Node<T> *father,  *son;
    father = grandFather->rightNode;
    if (rightSon)
        son = father->rightNode;
    else{
        Node<T> *f = nullptr;
        son = father->leftNode;
        son->rightNode = father;
        father->leftNode = nullptr;
        f = father;
        father = son;
        son = f;
    }


    if (father->leftNode != nullptr)
        grandFather = father->leftNode;
    father->leftNode = grandFather;
    grandFather->rightNode = nullptr;
    return father;
}

template<class T>
Node<T>* rbTree<T>::smallTurnRight(Node<T>* grandFather, bool leftSon){
    Node<T> *father,  *son;
    father = grandFather->leftNode;
    if (leftSon)
        son = father->leftNode;
    else{
        Node<T> *f = nullptr;
        son = father->rightNode;
        son->leftNode = father;
        father->rightNode = nullptr;
        f = father;
        father = son;
        son = f;
    }


    if (father->rightNode != nullptr)
        grandFather = father->rightNode;
    father->rightNode = grandFather;
    grandFather->leftNode = nullptr;
    return father;
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
        if (this->compare->equal(node, point))
        {
            //todo: add throw about existence node
            return;
        }

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

    if (this->compare->compare(node, *point))
    {
        point->rightNode = new Node<T>;
        point->rightNode->copy(node);
        point->rightNode->drawRed();
        point = point->rightNode;
    }
    else
    {
        point->leftNode = new Node<T>;
        point->leftNode->copy(node);
        point->leftNode->drawRed();
        point = point->leftNode;
    }

    Node<T> *parent;
    parent = stack1.top();
    if (parent->isRed())
    {
        stack1.push(point);
        this->balanceAdd(stack1);
    }

}

template<class T>
void rbTree<T>::deleteNode(T key)
{
    stack<Node<T>*> st;
    if (this->root == nullptr){
        //todo: throw exception about missing root
        return;
    }

    if (this->compare->equal(key, this->root))
    {

    }

    Node<T> *currentNode = this->root;
    while(!this->compare->equal(key, currentNode))
    {
        st.push(currentNode);
        if (this->compare->compare(key, currentNode))
            currentNode = currentNode->rightNode;
        else
            currentNode = currentNode->leftNode;

        if (currentNode == nullptr)
        {
            //todo: throw exception about missing node
            return;
        }
    }

    //red node without sons
    if(currentNode->isRed() && currentNode->rightNode == nullptr && currentNode->leftNode == nullptr)
    {
        currentNode = st.top();
        if (this->compare->compare(key, currentNode))
        {
            delete currentNode->rightNode;
            currentNode->rightNode = nullptr;
        }
        else
        {
            delete currentNode->leftNode;
            currentNode->leftNode = nullptr;
        }
    }
    //black node with one son
    else if (currentNode->isBlack() && (currentNode->rightNode != nullptr ^ currentNode->leftNode != nullptr))
    {
        if (currentNode->rightNode != nullptr)
        {
            Node<T> *f = currentNode->rightNode;
            currentNode = st.top();
            if (this->compare->compare(key, currentNode))
            {
                delete currentNode->rightNode;
                currentNode->rightNode = f;
                f->drawBlack();
            }
            else
            {
                delete currentNode->leftNode;
                currentNode->leftNode = f;
                f->drawBlack();
            }
        }
        else
        {
            Node<T> *f = currentNode->leftNode;
            currentNode = st.top();
            if (this->compare->compare(key, currentNode))
            {
                delete currentNode->rightNode;
                currentNode->rightNode = f;
                f->drawBlack();
            }
            else
            {
                delete currentNode->leftNode;
                currentNode->leftNode = f;
                f->drawBlack();
            }
        }

    }
    else if (currentNode->rightNode != nullptr && currentNode->leftNode != nullptr)// red/black node with two sons
    {
        Node<T>*deleteNode = currentNode;
        Node<T>*fatherDeleteNode = st.top();
        Node<T>*fatherCurrentNode;
        Node<T>*f = nullptr;
        bool blackDeleteNode = deleteNode->isBlack();
        st.push(currentNode);
        currentNode = currentNode->rightNode;
        while(currentNode->leftNode != nullptr)
        {
            st.push(currentNode);
            currentNode = currentNode->leftNode;
        }

        st.pop();
        fatherCurrentNode = st.top();

        //redraw currentNode
        if (currentNode->isBlack())
            deleteNode->drawBlack();
        else
            deleteNode->drawRed();

        //redraw deleteNode
        if (blackDeleteNode)
            currentNode->drawBlack();
        else
            currentNode->drawRed();


        //change leftNode of currentNode and deleteNode
        currentNode->leftNode = deleteNode->leftNode;
        deleteNode->leftNode = nullptr;

        if (deleteNode->rightNode != currentNode)
        {
            f = deleteNode->rightNode;
            deleteNode->rightNode = currentNode->rightNode;
            currentNode->rightNode = f;
        }
        else
        {
            if (fatherDeleteNode->leftNode == currentNode)
                f = fatherCurrentNode->leftNode;
            else
                f = fatherCurrentNode->rightNode;

            deleteNode->rightNode = currentNode->rightNode;
            currentNode->rightNode = f;
        }


    }
}

template<class T>
void rbTree<T>::balanceAdd(stack<Node<T>*>& st) {
    Node<T> *son = nullptr, *father = nullptr, *grFather = nullptr, *uncle = nullptr;
    son = st.top();
    st.pop();
    father = st.top();
    st.pop();
    grFather = st.top();
    st.pop();
    if (st.empty()){
        if (grFather->leftNode == father)
            uncle = grFather->rightNode;
        else
            uncle = grFather->leftNode;


        if (uncle == nullptr || uncle->isBlack())
        {

            if (grFather->leftNode == father)
                this->root = smallTurnRight(grFather, bool(father->leftNode == son));
            else
                this->root = smallTurnLeft(grFather, father->rightNode == son);


        }
        else
        {
            uncle->drawBlack();
            father->drawBlack();
            grFather->drawBlack();//this is root, because st is empty
            st.push(grFather);
        }
    }
    else{
        if (grFather->leftNode == father)
            uncle = grFather->rightNode;
        else
            uncle = grFather->leftNode;

        Node<T>*grGrFather = st.top();
        st.pop();
        if (uncle == nullptr || uncle->isBlack())
        {
            if (grFather->leftNode == father)
                if (grGrFather->leftNode == grFather)
                    grGrFather->leftNode = smallTurnRight(grFather, father->leftNode == son);
                else
                    grGrFather->rightNode = smallTurnRight(grFather, father->leftNode == son);

            else
                if (grGrFather->leftNode == grFather)
                    grGrFather->leftNode = smallTurnLeft(grFather, father->rightNode == son);
                else
                    grGrFather->rightNode = smallTurnLeft(grFather, father->rightNode == son);


        }
        else
        {
            uncle->drawBlack();
            father->drawBlack();
            grFather->drawRed();
            st.push(grFather);
            this->balanceAdd(st);
        }
    }


}


#endif //KURSAH_RBTREE_H
