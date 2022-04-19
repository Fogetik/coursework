//
// Created by danil on 05.04.2022.
//

#ifndef KURSAH_COMPARATOR_H
#define KURSAH_COMPARATOR_H

template<class T>
class Comparator{
public:
    virtual bool compare(Node<T>& a, Node<T>& b) = 0;
    virtual ~Comparator()= default;
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
};

#endif //KURSAH_COMPARATOR_H
