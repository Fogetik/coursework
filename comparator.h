//
// Created by danil on 05.04.2022.
//

#ifndef KURSAH_COMPARATOR_H
#define KURSAH_COMPARATOR_H

template<class T>
class Comparator{
public:
    virtual bool compare(Node<T>& a, Node<T>& b) = 0;
    virtual bool compare(T& key, Node<T>& b) = 0;
    virtual bool equal(T& key, Node<T>& b) = 0;
    virtual bool equal(Node<T>& a, Node<T>& b) = 0;
    virtual ~Comparator()= default;
};

class ComparatorString : public Comparator<std::string>
{
public:
    ComparatorString()= default;

    bool compare(Node<std::string>& a, Node<std::string>& b)override {
        if (std::stoi(a.key) > std::stoi(b.key))
            return true;
        else
            return false;
    }

    bool compare(std::string& key, Node<std::string>& b)override {
        if (std::stoi(key) > std::stoi(b.key))
            return true;
        else
            return false;
    }

    bool equal(std::string& key, Node<std::string>& b)override
    {
        if (key == b.key)
            return true;
        else
            return false;
    }

    bool equal(Node<std::string>& a, Node<std::string>& b)override
    {
        if (a.key == b.key)
            return true;
        else
            return false;
    }
};

class ComparatorInt : public Comparator<int>
{
public:
    ComparatorInt()= default;
    bool compare(Node<int>& a, Node<int>& b)override {
        if (a.key > b.key)
            return true;
        else
            return false;
    }

    bool compare(int& key, Node<int>& b)override {
        if (key > b.key)
            return true;
        else
            return false;
    }

    bool equal(int& key, Node<int>& b)override
    {
        if (key == b.key)
            return true;
        else
            return false;
    }

    bool equal(Node<int>& a, Node<int>& b)override
    {
        if (a.key == b.key)
            return true;
        else
            return false;
    }
};

#endif //KURSAH_COMPARATOR_H
