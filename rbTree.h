//
// Created by danil on 05.04.2022.
//

#ifndef KURSAH_RBTREE_H
#define KURSAH_RBTREE_H
#include "node.h"
#include "exception.h"
#include "comparator.h"
#include <iostream>
#include <stack>
#include <vector>

using std::cout;
using std::endl;
using std::stack;
using std::vector;

template<class T>
class rbTree{
private:
    Comparator<T>* compare;
    Node<T> *root = nullptr;

    void balanceAdd(stack<Node<T>*>&);

    void balanceDel(stack<Node<T>*>&, bool);

    void sim(Node<T> *node, int k){
        if (node == nullptr)
            return;
        count++;
        sim(node->leftNode, k);

        std::cout << node->key << "|";
        std::string* str = node->value;
        for (int i =0; i < k; i++)
            cout << str[i] << "|";

//        if (this->compare->compare(*this->root, *node))
//            cout << " true ";
//        else
//            cout << " false ";

        cout << std::endl;
        sim(node->rightNode, k);
    }

    void delete_private(Node<T> *node){
        if (node == nullptr)
            return;

        delete_private(node->leftNode);
        node->leftNode = nullptr;
        delete_private(node->rightNode);
        node->rightNode = nullptr;
        if (node == this->root){
            this->root = nullptr;
        }

        delete node;
    }

    void find_private(int position, T value, int count_column, Node<T>*& node){
        if (node == nullptr)
            return;

        find_private(position, value, count_column, node->leftNode);
        if (node->value[position] == value){
            this->line_search = new T[count_column];
            this->line_search[0] = node->key;
            for (int i = 1; i < count_column; i++){
                this->line_search[i] = node->value[i-1];
            }
            this->vector_search.push_back(this->line_search);
        }

        find_private(position, value, count_column, node->rightNode);
    }

    std::vector<T*> vector_search;
    T* line_search= nullptr;
    int count;

public:
    Node<T>* smallTurnRightDel(Node<T>*);
    Node<T>* smallTurnLeftDel(Node<T>*);
    bool existByKey(std::string key){
        Node<T>* current_node = this->root;
        while(true){
            if (this->compare->equal(key, *current_node))
                return true;
            else if (this->compare->compare(key, *current_node)){
                current_node = current_node->rightNode;
            }
            else{
                current_node = current_node->leftNode;
            }

            if (current_node == nullptr)
                return false;
        }

    }
    bool empty(){
        if (this->root == nullptr)
            return true;
        else
            return false;
    }
    void addNode(Node<T>);

    Node<T> findById(T id) const {
        Node<T> *currentNode = this->root;
        while(!this->compare->equal(id, *currentNode))
        {
            if (this->compare->compare(id, *currentNode))
                currentNode = currentNode->rightNode;
            else
                currentNode = currentNode->leftNode;

            if (currentNode == nullptr)
            {
                //todo: throw exception about missing node
//                cout << endl << endl << "i cannot find this node" << endl << endl;
                throw NodeNotFoundException();
            }
        }

        return *currentNode;
    }

    std::vector<T*> find(int position, T value, int count_column){
        this->vector_search.clear();
        Node<T>* node = this->root;
        find_private(position, value, count_column, node);
        return this->vector_search;
    }

    void deleteNode(T k);

    void show(int k){
        count = 0;
        sim(root, k);
        cout << endl << count << endl;
    }
//    rbTree(Comparator<T>*, Node<T>&);
//    rbTree(Comparator<T>);

    void setComparator(Comparator<T>* comparator);

    void deleteTree(){
        delete_private(this->root);
    }
};

template<class T>
void rbTree<T>::setComparator(Comparator<T> *comparator) {
    this->compare = comparator;
}

template<class T>
void rbTree<T>::addNode(Node<T> node) {
//    cout << "adding node..." << endl;
    stack<Node<T>*> stack1;
    Node<T> *father;
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
        if (this->compare->equal(node, *point))
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

    father = point;
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


    if (father->isRed())
        this->balanceAdd(stack1);


}

template<class T>
void rbTree<T>::balanceAdd(stack<Node<T>*>& st) {
    Node<T> *father, *grFather, *uncle;
    father = st.top();
    st.pop();
    grFather = st.top();
    st.pop();
    if (grFather->leftNode == father)
        uncle = grFather->rightNode;
    else
        uncle = grFather->leftNode;

    if (uncle == nullptr || uncle->isBlack()) {
        father->drawBlack();
        grFather->drawRed();
        if (st.empty()) {
            if (grFather->leftNode == father)
                root = smallTurnRightDel(grFather);
            else
                root = smallTurnLeftDel(grFather);
        } else {
            father->drawBlack();
            grFather->drawRed();
            Node<T> *grand_grand_father = st.top();
            if (grand_grand_father->leftNode == grFather) {
                if (grFather->leftNode == father)
                    grand_grand_father->leftNode = smallTurnRightDel(grFather);
                else
                    grand_grand_father->leftNode = smallTurnLeftDel(grFather);
            } else {
                if (grFather->leftNode == father)
                    grand_grand_father->rightNode = smallTurnRightDel(grFather);
                else
                    grand_grand_father->rightNode = smallTurnLeftDel(grFather);
            }
        }
    }else{
        father->drawBlack();
        uncle->drawBlack();
        if (this->root != grFather) {
            grFather->drawRed();
        }else{
            return;
        }

        Node<T> *grand_grand_father = st.top();
        if (grand_grand_father->isRed())
                this->balanceAdd(st);
    }


}

template<class T>
Node<T>* rbTree<T>::smallTurnLeftDel(Node<T>* grandFather){
    Node<T> *father,  *son_left;
    father = grandFather->rightNode;
    if (father->leftNode != nullptr)
        son_left = father->leftNode;
    else
        son_left = nullptr;


    father->leftNode = grandFather;
    grandFather->rightNode = son_left;
    return father;
}

template<class T>
Node<T>* rbTree<T>::smallTurnRightDel(Node<T>* grandFather){
    Node<T> *father,  *son_right;
    father = grandFather->leftNode;
    if (father->rightNode != nullptr)
        son_right = father->rightNode;
    else
        son_right = nullptr;


    father->rightNode = grandFather;
    grandFather->leftNode = son_right;
    return father;
}

template<class T>
void rbTree<T>::deleteNode(T key)
{
    stack<Node<T>*> st;
    if (this->root == nullptr){
        //todo: throw exception about missing root
        return;
    }

//    if (this->compare->equal(key, *this->root))
//    {
//        //todo: delete the root
//    }

    Node<T> *currentNode = this->root;
    while(!this->compare->equal(key, *currentNode))
    {
        st.push(currentNode);
        if (this->compare->compare(key, *currentNode))
            currentNode = currentNode->rightNode;
        else
            currentNode = currentNode->leftNode;

        if (currentNode == nullptr)
        {
            //todo: throw exception about missing node
            cout << endl << endl << "i cannot find this node" << endl << endl;
            return;
        }
    }

    //red node without sons
    if(currentNode->isRed() && currentNode->rightNode == nullptr && currentNode->leftNode == nullptr)
    {
    redWithoutSons:
        if (st.empty()){
            delete this->root;
            this->root = nullptr;
        }
        else {
            currentNode = st.top();
            if (this->compare->compare(key, *currentNode)) {
                delete currentNode->rightNode;
                currentNode->rightNode = nullptr;
            } else {
                delete currentNode->leftNode;
                currentNode->leftNode = nullptr;
            }
        }
    }
    //black node with one son
    else if (currentNode->isBlack() && ((currentNode->rightNode != nullptr) ^ (currentNode->leftNode != nullptr)))
    {
    blackOneSon:
        if (currentNode->rightNode != nullptr)
        {
            Node<T> *f = currentNode->rightNode;
            bool st_empty = false;
            if (!st.empty())
                currentNode = st.top();
            else
                st_empty = true;

            if (st_empty){
                delete this->root;
                this->root = f;
            }
            else if (this->compare->compare(f->key, *currentNode))
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
            bool st_empty = false;
            if (!st.empty())
                currentNode = st.top();
            else
                st_empty = true;

            if (st_empty){
                delete this->root;
                this->root = f;
            }
            else if (this->compare->compare(f->key, *currentNode))
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
    // red/black node with two sons
    else if (currentNode->rightNode != nullptr && currentNode->leftNode != nullptr)
    {
        Node<T>*f = currentNode;
        st.push(currentNode);
        currentNode = currentNode->rightNode;
        while(currentNode->leftNode != nullptr)
        {
            st.push(currentNode);
            currentNode = currentNode->leftNode;
        }

        changeNodes(*f, *currentNode);
        if (currentNode->isRed())
            goto redWithoutSons;
        else if (currentNode->isBlack() && currentNode->rightNode != nullptr)
            goto blackOneSon;
        else// black node without sons
        {
            auto father = st.top();
            bool left_delete_node;
            if (father->leftNode == currentNode){
                left_delete_node = true;
                delete currentNode;
                father->leftNode = nullptr;
            }
            else{
                left_delete_node = false;
                delete currentNode;
                father->rightNode = nullptr;
            }

            this->balanceDel(st, left_delete_node);
        }

    }
    // black node without sons
    else{
        auto father = st.top();
        bool left_delete_node;
        if (father->leftNode == currentNode){
            left_delete_node = true;
            delete currentNode;
            father->leftNode = nullptr;
        }
        else{
            left_delete_node = false;
            delete currentNode;
            father->rightNode = nullptr;
        }

        this->balanceDel(st, left_delete_node);
    }


}

template<class T>
void rbTree<T>::balanceDel(stack<Node<T>*>& st, bool left_delete_node) {
    Node<T>*grand_father, *father, *brother;
start_balance:
    father = st.top();
    st.pop();
    if (left_delete_node) {
        brother = father->rightNode;
        if (brother->isBlack()) {
            if (brother->rightNode != nullptr && brother->rightNode->isRed()) {
                brother_black_sonright_red:
                if (father->isBlack()) brother->drawBlack();
                else brother->drawRed();

                brother->rightNode->drawBlack();
                if(st.empty()){
                    root = smallTurnLeftDel(father);
                }else {
                    grand_father = st.top();
                    if (grand_father->leftNode == father)
                        grand_father->leftNode = smallTurnLeftDel(father);
                    else
                        grand_father->rightNode = smallTurnLeftDel(father);
                }

            }
            else if (brother->leftNode != nullptr && brother->leftNode->isRed()
            && (brother->rightNode == nullptr || brother->rightNode->isBlack())) {
                brother->drawRed();
                brother->leftNode->drawBlack();
                father->rightNode = smallTurnRightDel(brother);

                goto brother_black_sonright_red;
            }
            else if ((brother->leftNode == nullptr || brother->leftNode->isBlack())
            && (brother->rightNode == nullptr ||brother->rightNode->isBlack())) {
                brother->drawRed();
                if (father->isRed()) {
                    father->drawBlack();
                    return;
                } else {
                    if (st.empty())
                        return;

                    grand_father = st.top();
                    if (grand_father->rightNode == father)
                        left_delete_node = false;

                    goto start_balance;//todo:check
                }
            }
        } else {
            father->drawRed();
            brother->drawBlack();
            if (st.empty()){
                root = smallTurnLeftDel(father);
                return;
            }

            grand_father = st.top();
            if (grand_father->leftNode == father) {
                grand_father->leftNode = smallTurnLeftDel(father);
            } else {
                grand_father->rightNode = smallTurnLeftDel(father);
            }

            st.push(brother);
            st.push(father);
            goto start_balance;
        }
    }
    else{
        brother = father->leftNode;
        if (brother->isBlack()) {
            if (brother->leftNode != nullptr && brother->leftNode->isRed()) {
                brother_black_sonleft_red:
                if (father->isBlack()) brother->drawBlack();
                else brother->drawRed();

                brother->leftNode->drawBlack();
                grand_father = st.top();
                if (grand_father->leftNode == father)
                    grand_father->leftNode = smallTurnRightDel(father);
                else
                    grand_father->rightNode = smallTurnRightDel(father);

            }
            else if (brother->rightNode != nullptr && brother->rightNode->isRed()
            && (brother->leftNode == nullptr || brother->leftNode->isBlack())) {
                brother->drawRed();
                brother->rightNode->drawBlack();
                father->leftNode = smallTurnLeftDel(brother);

                goto brother_black_sonleft_red;
            }
            else if ((brother->leftNode == nullptr || brother->leftNode->isBlack())
            && (brother->rightNode == nullptr || brother->rightNode->isBlack())) {
                brother->drawRed();
                if (father->isRed()) {
                    father->drawBlack();
                    return;
                } else {
                    if (st.empty())
                        return;

                    grand_father = st.top();
                    if (grand_father->leftNode == father)
                        left_delete_node = true;

                    goto start_balance;//todo:check
                }
            }
        } else {

            father->drawRed();
            brother->drawBlack();
            if (st.empty()){
                root = smallTurnRightDel(father);
                return;
            }

            grand_father = st.top();
            if (grand_father->leftNode == father) {
                grand_father->leftNode = smallTurnRightDel(father);
            } else {
                grand_father->rightNode = smallTurnRightDel(father);
            }

            st.push(brother);
            st.push(father);

            goto start_balance;
        }
    }
}

#endif //KURSAH_RBTREE_H
