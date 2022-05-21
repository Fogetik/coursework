//
// Created by danil on 24.04.2022.
//

#ifndef KURSAH_EXCEPTION_H
#define KURSAH_EXCEPTION_H

#include <iostream>

class NodeNotFoundException:public std::exception
{
    const char* what()const throw () {
        return ("Node not found in tree");
    }


};

class ColumnNotFoundException:public std::exception
{
    const char* what()const throw () {
        return ("Column not found in database");
    }


};

#endif //KURSAH_EXCEPTION_H
