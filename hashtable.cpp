#include "hashtable.hpp"

//----------------Ht_item-------------------------
Ht_item::Ht_item(){

    this->id = 0;
    this->key = nullptr;
    this->count = 0;

    this->next_item = nullptr;
    //this->last_item = nullptr;
}

Ht_item::Ht_item(std::string key){
    this->key = key;
    this->id = 0;
    this->count = 0;

    this->next_item = nullptr;
    //this->last_item = nullptr;
}

Ht_item::Ht_item(std::string key, unsigned int id){

    this->key = key;
    this->id = id;
    this->count = 0;

    this->next_item = nullptr;
    //this->last_item = nullptr;
}


Ht_item::Ht_item(std::string key, unsigned int id, std::shared_ptr<Ht_item> item){


    this->key = key;
    this->id = id;
    this->count = 0;

    this->next_item = item;
    //this->last_item = item;
}


//Ht_item::Ht_item(std::string key, unsigned int id, std::shared_ptr<Ht_item> last_item, std::shared_ptr<Ht_item> next_item){
//    this->key = key;
//    this->id = id; mama papa

//    this->next_item = last_item;
//    //this->last_item = next_item;
//}


Ht_item& Ht_item::operator=(const Ht_item& second){
    this->key = second.key;
    this->id = second.id;

    return *this;
}

void Ht_item::output(){
    std::cout<<"| id: "<<this->id<<" | key: "<<this->key<<" | count: "<< this->count <<std::endl;
}
//-----------------------------------------------


//----------------Ht_box-------------------------
Ht_box::Ht_box(){
    this->item_amount = 0;

    this->fkey = nullptr;
    this->lkey = nullptr;
    this->curkey = nullptr;
}

Ht_box& Ht_box::operator=(const Ht_box& second){

    this->item_amount = second.item_amount;
    
    this->fkey = second.fkey;
    this->lkey = second.lkey;    

    return *this;
}


void Ht_box::add(std::string key, unsigned int id){


    if(this->item_amount == 0){
        this->fkey = std::make_shared<Ht_item>(key, id);
        this->lkey = this->fkey;

        this->item_amount++;
    }
    else{
        if(this->search(key) == false){
            this->lkey->next_item = std::make_shared<Ht_item>(key, id);

            this->lkey = this->lkey->next_item;

            this->item_amount++;
        }
    }
}

void Ht_box::add(std::shared_ptr<Ht_item> add){
    
    if(this->item_amount == 0){
        this->fkey = add;
        this->lkey = add;

        this->item_amount++;
    }
    else{
        if(this->search(add)==false){

            this->curkey = this->lkey;
            this->curkey->next_item = add;
            this->lkey = add;
//            this->lkey->last_item = this->curkey;

            this->item_amount++;
        }
        else{
               
        }
    }
}

// Функция для добавки
bool Ht_box::search(std::string key){

    if(this->item_amount == 0){ return false;}

    std::shared_ptr<Ht_item> search = std::make_shared<Ht_item>(key);

    for(unsigned int i=0; i < this->item_amount; i++){
        if( i == 0 ){ this->curkey = this->fkey; }
        else{ this->curkey = this->curkey->next_item; }

        if(this->curkey->key == search->key){
            this->curkey->count++;
            return true;
        }
    }

    return false;
}

// Для поиска
bool Ht_box::search(std::shared_ptr<Ht_item> search){

    if(this->item_amount == 0){ return false;}

    for(unsigned int i=0; i < this->item_amount; i++){
        if( i == 0 ){ this->curkey = this->fkey; }
        else{ this->curkey = this->curkey->next_item; }

        if(this->curkey->key == search->key){
            return true;
        }
        else if(i == this->item_amount-1 && this->lkey != search){ return false;}
    }

    return false;
}

void Ht_box::pop(std::string key){

    std::shared_ptr<Ht_item> tmp = std::make_shared<Ht_item>(key);
    std::shared_ptr<Ht_item> tmpl = std::make_shared<Ht_item>(key);

    for(unsigned int i=0; i< this->item_amount; i++){

        if(i==0){ this->curkey = this->fkey; tmpl = this->fkey;}
        else{ tmpl = this->curkey; this->curkey = this->curkey->next_item; }

        std::cout<<"--5--\n";   

        if(this->curkey->key == tmp->key){

            if(i==0 && this->item_amount > 1){
                this->curkey = this->curkey->next_item;
                this->fkey = this->curkey;
            }
            else if(i==0 && this->item_amount == 1){ 
                this->fkey = nullptr; this->lkey = nullptr;
            }
            else if(i>0 && i < this->item_amount-1){

                this->curkey = tmpl;
                this->curkey->next_item = this->curkey->next_item->next_item;

            }
            else{

                this->curkey = tmpl;
                this->curkey->next_item = nullptr;
                this->lkey = this->curkey;
            }
            this->item_amount--;

            break;
        }
    }
}


void Ht_box::output(){

    for(unsigned int i=0; i<this->item_amount; i++){
        if( i==0 ){ this->curkey = this->fkey;}
        else{ this->curkey = this->curkey->next_item; }

        this->curkey->output();
    }
}
//--------------------------------------------------

//----------------HashTable-------------------------
HashTable::HashTable(){
    this->size_of_table = 0;
    this->amount_of_elem = 0;

    this->table = nullptr;
}

HashTable::HashTable(unsigned int size_table){

    this->size_of_table = size_table;
    this->amount_of_elem = 0;

    this->table = std::make_unique<Ht_box[]>(size_of_table);

    for(unsigned int i=0; i<this->size_of_table; i++){
        this->table[i] = Ht_box();
    }
}

void HashTable::reconstruct(unsigned int size){
    this->delete_table();
    this->size_of_table = size;
    this->table = std::make_unique<Ht_box[]>(size);
}

unsigned int HashTable::hash_function(std::string key){

    unsigned int id=0;

    for(unsigned int i=0, j=1; i < key.size(); i++){
        id += key[i]*j;
        j++;
    }

    if(this->size_of_table > 0){
        id %= this->size_of_table;
    }
    else{
        id %= 5;
    }

    return id;
}

void HashTable::add(std::string key){

    if(this->size_of_table == 0){
        this->table = std::make_unique<Ht_box[]>(5);
        this->size_of_table = 5;
    }

    if(this->search(key) == false){
        if(this->amount_of_elem == this->size_of_table){
            
            unsigned int tmp_size = this->size_of_table;
            this->size_of_table *= 2;

            std::unique_ptr<Ht_box[]> TMP = std::make_unique<Ht_box[]>(tmp_size*2);

            for(unsigned int i=0; i < tmp_size; i++){

                if(this->table[i].item_amount == 0){ continue; }

                for(unsigned int j=0; j<this->table[i].item_amount; j++){

                    if( j == 0 ){ this->table[i].curkey = this->table[i].fkey; }
                    else{ this->table[i].curkey = this->table[i].curkey->next_item; }

                    unsigned int id = this->hash_function(this->table[i].curkey->key);

                    TMP[id].add(this->table[i].curkey->key, id);
                }
            }
            this->table = move(TMP);
        }
        unsigned int id = this->hash_function(key);

        this->table[id].add(key, id);
        this->amount_of_elem++;
    }
}

void HashTable::pop(std::string pop){

    if(this->search(pop)==true){
        std::cout<<"\n\n-- DELETED --\n\n";
        unsigned int id = this->hash_function(pop);

        this->table[id].pop(pop);
        this->amount_of_elem--;
    }
}

bool HashTable::search(std::string key){

    std::shared_ptr<Ht_item> tmp = std::make_shared<Ht_item>(key);

    unsigned int id = this->hash_function(key);

    if(this->size_of_table == 0 || this->amount_of_elem == 0){ return false; }
    else if(this->table[id].search(tmp) == true ){ return true;}
    else{ return false; }
}

void HashTable::output(){

    for(unsigned int i=0; i<this->size_of_table; i++){
        table[i].output();
    }
}

void HashTable::delete_table(){
    this->table = nullptr;
    this->size_of_table = 0;
}

//-----------------------------------------------------

void reading_from_file(std::ifstream& file, HashTable& table){

    while(file.eof()!=true){
        std::string word;      
        file >> word; 

        if(word.empty() == true){ continue; }

        table.add(word);
    }
    std::cout<<"\n-- READING COMPLETE! --\n";
}
