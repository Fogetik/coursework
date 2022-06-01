//
// Created by danil on 04.05.2022.
//
#include "database.h"
#include "comparator.h"
#define size_line 108

DataBaseList::DataBaseList(int count) {
    if (count < 0)
        cout << "lol";
    //todo: throw exception
    id = 0;
    this->count_entry = 0;
    this->count_delete = 0;
    this->start_file = 0;
    this->end_file = 0;
    this->count_columns = count;
    this->max_entry = 10;
    this->file.open("db.txt", std::ios::in | std::ios_base::out | std::ios_base::ate);

    //this->file.open("db.txt", std::ios_base::out | std::ios_base::ate | std::ios_base::app);
}

int DataBaseList::getCountStr()const{
    return(this->count_entry);
}

void DataBaseList::insert(string *new_item){
    string* new_item_copy = new string[count_columns+1];
    new_item_copy[0] = std::to_string(this->id++);
    for (int i = new_item_copy[0].length(); i < 10; i++){
        new_item_copy[0] += " ";
    }

    for (int i = 0; i < count_columns; i++){
        new_item_copy[i+1] = new_item[i];
    }

    string line;
    for (int i = 0; i <= count_columns; i++){
        line += new_item_copy[i];
        line += "|";
    }

    file << line << endl;

    if (count_entry < this->max_entry) {
        this->last_id = this->id-1;
        this->end_file += size_line;
        this->list.push_front(new_item_copy);
        this->count_entry++;
    }
}

void DataBaseList::remove(string id) {
    forward_list<string*>::iterator father_ptr;
    string *remove_string;
    bool exist = false;
    int remove_id = std::stoi(id);
    int node_id;
    for (auto list_ptr = this->list.begin(); list_ptr != this->list.end(); list_ptr++){
        node_id = std::stoi((*list_ptr)[0]);
        if (node_id == remove_id){
            remove_string = *list_ptr;
            exist = true;
            break;
        }

        father_ptr = list_ptr;
    }


    string line, id_line_str;
    if (this->file.seekp(0, std::ios::end).tellp() < size_line * std::stoi(id)) {
        cout << "cannot find this id..." << endl;
        //todo: throw exception about id higher than max id in file
    }

    this->count_delete++;
    file.seekg(size_line * std::stoi(id));
    file << "|";
    if (exist) {
        this->count_entry--;
        this->list.erase_after(father_ptr);
        delete[] remove_string;
        if (end_file/size_line == this->count_entry + this->count_delete){
            file.seekg(0, std::ios::end);
            return;
        }

        string *line = new string[count_columns+1];
        int a = 0;
        string line_file;
        do{
            this->end_file += size_line;
            file.seekg(size_line * (++this->last_id));
            getline(file, line_file);
        }while(line_file[0]=='|');

        for (int i = 0; i < count_columns+1; i++){
            while(line_file[a] != '|'){
                line[i] += line_file[a];
                a++;
            }
            a++;
        }

        this->list.push_front(line);
        file.seekg(0, std::ios::end);
    }


}

vector<string*> DataBaseList::find(string name_column, string find_str)  {
    int number_column = 0;
    vector<string*> vector_string;
    string *line_ptr;
    string line;
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

    exist = false;
    for (auto list_ptr : this->list){
        if (list_ptr[number_column] == find_str){
            line_ptr = new string[this->count_columns + 1];
            for(int i = 0; i < this->count_columns+1; i++){
                line_ptr[i] = list_ptr[i];
            }

            vector_string.push_back(line_ptr);
        }
    }

    file.seekg(this->end_file);
    for (auto list_ptr : this->list) {
        delete[]list_ptr;
    }

    this->list.clear();
    this->count_entry = 0;
    int a;
    while (!file.eof()){
        getline(file, line);
        if (line[0] == '|')
            continue;
        else{
            a = 0;
            line_ptr = new string[this->count_columns + 1];
            for (int i = 0; i < count_columns+1; i++){
                while(line[a] != '|'){
                    line_ptr[i] += line[a];
                    a++;
                }

                a++;
            }

            this->list.push_front(line_ptr);
            this->count_entry++;
        }

        if (this->count_entry == this->max_entry){
            //search
            for (auto list_ptr : this->list){
                if (list_ptr[number_column] == find_str){
                    line_ptr = new string[this->count_columns + 1];
                    for(int i = 0; i < this->count_columns+1; i++){
                        line_ptr[i] = list_ptr[i];
                    }

                    vector_string.push_back(line_ptr);
                }
            }

            //delete
            for (auto list_ptr : this->list) {
                delete[]list_ptr;
            }

            this->list.clear();
            this->count_entry = 0;
        }
    }

    if (!list.empty()){
        for (auto list_ptr : this->list){
            if (list_ptr[number_column] == find_str){
                line_ptr = new string[this->count_columns + 1];
                for(int i = 0; i < this->count_columns+1; i++){
                    line_ptr[i] = list_ptr[i];
                }

                vector_string.push_back(line_ptr);
            }
        }

        for (auto list_ptr : this->list) {
            delete[]list_ptr;
        }

        this->list.clear();
        this->count_entry = 0;
    }

    file.clear();
    file.seekg(0, std::ios::beg);
    while(this->count_entry < this->max_entry && !file.eof()){
        getline(file, line);
        if (line[0] == '|')
            continue;
        else{
            a = 0;
            line_ptr = new string[this->count_columns + 1];
            for (int i = 0; i < count_columns+1; i++){
                while(line[a] != '|'){
                    line_ptr[i] += line[a];
                    a++;
                }

                a++;
            }

            this->list.push_front(line_ptr);
            this->count_entry++;
        }

    }

    return vector_string;
}

void DataBaseList::drop(){
    for (auto str : this->list)
        delete[] str;

    this->count_entry = 0;
    this->list.clear();
    this->file.close();
    this->file.open("db.txt", std::ios_base::out | std::ios_base::trunc);
    this->file.close();
}


DataBaseRBT::DataBaseRBT(int count) {
    if (count < 0)
        cout << "lol";
    //todo: throw exception
    id = 0;
    this->count_str = 0;
    this->count_columns = count;

    this->tree.setComparator(new ComparatorString());
}

int DataBaseRBT::getCountStr()const{
    return(this->count_str);
}

void DataBaseRBT::insert(string *new_item){
    string id_str = std::to_string(this->id++);
    Node<string> node;
    node.key = id_str;
    node.value = new_item;
    this->tree.addNode(node);
    this->count_str++;
}

void DataBaseRBT::remove(string id) {
    this->tree.deleteNode(id);
}

vector<string*> DataBaseRBT::find(string name_column, string find_string){
    vector<string*> result;
    string* line = new string[this->count_columns + 1];
    Node<string> find_node;
    if (name_column == "id"){
        find_node = this->tree.findById(find_string);
        line[0] = find_string;
        for (int i = 0; i < this->count_columns; i++){
            line[i+1] = find_node.value[i];
        }

        result.push_back(line);
        return result;

    }else{
        int position = -1;
        for (int i = 0; i < this->count_columns; i++){
            if (name_column == this->name_columns[i+1]){
                position=i;
                break;
            }
        }

        if (position == -1){
            throw ColumnNotFoundException();
        }

        vector<string*> a;

        return this->tree.find(position, find_string, this->count_columns+1);

    }
}


void DataBaseRBT::drop(){
    tree.deleteTree();
}
