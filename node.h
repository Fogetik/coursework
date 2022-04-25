//
// Created by danil on 05.04.2022.
//

#ifndef KURSAH_NODE_H
#define KURSAH_NODE_H

//using ull = unsigned long long;

enum class Color{
    Black, Red
};

template<class T>
struct Node{
    T key;
    T value;
    Color colorNode = Color::Red;
    Node<T> *leftNode = nullptr;
    Node<T> *rightNode = nullptr;

    void drawRed()noexcept{
        this->colorNode = Color::Red;
    }

    void drawBlack()noexcept{
        this->colorNode = Color::Black;
    }

    void redrawNode()
    {
        if (this->colorNode == Color::Red)
            this->colorNode = Color::Black;
        else
            this->colorNode = Color::Red;
    }

    bool isBlack()noexcept{
        if (this->colorNode == Color::Black)
            return true;
        else
            return false;
    }

    bool isRed()noexcept{
        if (this->colorNode == Color::Red)
            return true;
        else
            return false;
    }

    void copy(const Node<T>& node){
        this->key = node.key;
        this->value = node.value;
        this->colorNode = node.colorNode;
        this->leftNode = node.leftNode;
        this->rightNode = node.rightNode;
    }

};

template <class T>
void redrawNodes(Node<T>& a, Node<T>& b)
{
    bool blackFirstNode = a.isBlack();

    if (b.isBlack())
        a.drawBlack();
    else
        a.drawRed();

    if (blackFirstNode)
        b.drawBlack();
    else
        b.drawRed();
}

template<class T>
void changeNodes(Node<T>& a, Node<T>& b)
{
    T value, key;

    key = a.key;
    a.key = b.key;
    b.key = key;

    value = a.value;
    a.value = b.value;
    b.value = value;
}

#endif //KURSAH_NODE_H
