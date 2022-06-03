//
// Created by danil on 04.05.2022.
//

#ifndef KURSAH_DATABASE_H
#define KURSAH_DATABASE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <forward_list>
#include "rbTree.h"

using std::endl;
using std::cout;
using std::vector;
using std::string;
using std::fstream;
using std::forward_list;

class DataBase{
public:
    virtual int getCountStr()const = 0;
    virtual void insert(string*) = 0;
    virtual void remove(string) = 0;
    virtual vector<string*> find(string, string)  = 0;
    virtual void update(string) = 0;
    virtual void drop() = 0;
    virtual ~DataBase() = default;
};


class DataBaseList: public DataBase{
private:
    int start_file, end_file;
    fstream file;
    forward_list<string*> list;
    int count_columns, id, count_entry, max_entry, count_delete, last_id;
    string* name_columns;
public:
    explicit DataBaseList(int count);

    void setCountColumns(int s){
        this->count_columns = s;
    }

    int getCountColumns()const{
        return this->count_columns+1;
    }

    int getCountStr()const override;

    void setNameColumns(string* f){
        this->name_columns = new string[count_columns+1];
        this->name_columns[0] = "id";
        for (int i = 1; i < count_columns+1;i++)
            this->name_columns[i] = f[i-1];
    }

    void insert(string*)override;

    void remove(string)override;

    vector<string*> get(){
        vector<string*> result;
        for (auto str_ptr : this->list)
            result.push_back(str_ptr);

        std::reverse(result.begin(), result.end());
        return result;
    }

    void show(){
        for (int i =0; i < this->count_columns + 1; i++)
            cout << this->name_columns[i] << " | ";

        cout << endl;

        for (auto str_ptr : this->list){
            for (int i =0; i < this->count_columns + 1; i++)
                cout << str_ptr[i] << "|";

            cout << endl;
        }
    }

    vector<string*> find(string, string) override;

    void update(string)override{
    }

    void drop()override;
};


class DataBaseRBT: public DataBase{
private:
    rbTree<string> tree;

    string* name_columns;
    int start_file, end_file;
    fstream file;
    int count_columns, id, count_entry, max_entry, count_delete, last_id;
public:
    explicit DataBaseRBT(int count);

    void setCountColumns(int s){
        this->count_columns = s;
    }

    int getCountColumns()const{
        return this->count_columns+1;
    }

    int getCountStr()const override;

    void setNameColumns(string* f){
        this->name_columns = new string[count_columns+1];
        this->name_columns[0] = "id";
        for (int i = 1; i < count_columns+1;i++)
            this->name_columns[i] = f[i-1];
    }

    void insert(string*)override;

    void remove(string)override;

    //todo:suka blyat'
    /*vector<string*> get(){
        return nullptr;
    }*/

    void show(){
        for (int i =0; i < this->count_columns + 1; i++)
            cout << this->name_columns[i] << " | ";

        cout << endl;
        this->tree.show(this->count_columns);
    }

    vector<string*> find(string name_column, string find_line) override;

    void update(string)override{
        return;
    }

    void drop()override;
};
#endif //KURSAH_DATABASE_H
