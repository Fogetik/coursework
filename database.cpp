//
// Created by danil on 04.05.2022.
//
#include "database.h"
#include "comparator.h"
DataBaseList::DataBaseList(int count) {
    if (count < 0)
        cout << "lol";
    //todo: throw exception
    id = 0;
    this->count_str = 0;
    this->count_columns = count;
}

int DataBaseList::getCountStr()const{
    return(this->count_str);
}

void DataBaseList::insert(string *new_item){
    auto* new_item_copy = new string[count_columns+1];
    new_item_copy[0] = std::to_string(this->id++);
    for (int i = 0; i < count_columns; i++){
        new_item_copy[i+1] = new_item[i];
    }
    this->list.push_front(new_item_copy);
    this->count_str++;
}

void DataBaseList::remove(string id) {
    forward_list<string*>::iterator father_ptr;
    string *remove_string;
    bool exist = false;
    for (auto list_ptr = this->list.begin(); list_ptr != this->list.end(); list_ptr++){
        if ((*list_ptr)[0] == id){
            remove_string = *list_ptr;
            exist = true;
            break;
        }

        father_ptr = list_ptr;
    }

    if (!exist){
        cout << "there is no data under this id..." << endl;
        return;
    }

    this->count_str--;
    this->list.erase_after(father_ptr);
    delete[] remove_string;
}

vector<string*> DataBaseList::find(string name_column, string find_str) const {
    int number_column = 0;
    vector<string*> vector_string;
    bool exist = false;
    for (int i = 0; i < count_columns+1; i++){
        if (this->name_columns[i] == name_column) {
            exist = true;
            break;
        }
        number_column++;
    }

    if (!exist){
        cout << "there is no column with this name..." << endl;
        return vector_string;
    }

//    exist = false;
    for (auto list_ptr : this->list){
        if (list_ptr[number_column] == find_str){
            vector_string.push_back(list_ptr);
        }
    }

    return vector_string;
}

void DataBaseList::drop(){
    for (auto str : this->list)
        delete[] str;

    this->count_str = 0;
    this->list.clear();
}


DataBaseRGT::DataBaseRGT(int count) {
    if (count < 0)
        cout << "lol";
    //todo: throw exception
    id = 0;
    this->count_str = 0;
    this->count_columns = count;

    this->tree.setComparator(new ComparatorString());
}

int DataBaseRGT::getCountStr()const{
    return(this->count_str);
}

void DataBaseRGT::insert(string *new_item){
    string id_str = std::to_string(this->id++);
    Node<string> node;
    node.key = id_str;
    node.value = new_item;
    this->tree.addNode(node);
    this->count_str++;
}

void DataBaseRGT::remove(string id) {
    this->tree.deleteNode(id);
}
