#include <iostream>
#include <memory>
#include <fstream>


class Ht_item{
public:
	unsigned int id;
	std::string key;

	std::shared_ptr<Ht_item> next_item;
        //std::shared_ptr<Ht_item> last_item;
        unsigned int count;

	Ht_item();
	Ht_item(std::string);
	Ht_item(std::string, unsigned int);
	Ht_item(std::string, unsigned int, std::shared_ptr<Ht_item>);
        //Ht_item(std::string, unsigned int, std::shared_ptr<Ht_item>, std::shared_ptr<Ht_item>);

	Ht_item& operator=(const Ht_item&);

	void output();
};


class Ht_box{
public:
	unsigned int item_amount;

	std::shared_ptr<Ht_item> fkey;
	std::shared_ptr<Ht_item> lkey;
	std::shared_ptr<Ht_item> curkey;

	// Empty constructor
	Ht_box();

	Ht_box& operator=(const Ht_box&);
	
	void add(std::string, unsigned int);
	void add(std::shared_ptr<Ht_item>);

	void pop(std::string);

	void output();

	// Поиск в коробке
	bool search(std::string);
	bool search(std::shared_ptr<Ht_item>);
};


class HashTable{
private:
	// Количество боксов
	unsigned int size_of_table;

	// Массив коробок
	std::unique_ptr<Ht_box[]> table;

	// Количество элементов
	unsigned int amount_of_elem;
public:
	// Хэш-функция
	unsigned int hash_function(std::string); 

	// Пустой конструктор
	HashTable();

	// Конструктор с количеством боксов
	HashTable(unsigned int);

	// Расширение таблицы в случае переполнения
	void increase();

        void reconstruct(unsigned int);

	// Добавление элемента в таблицу, если его там нет
	void add(std::string);

	// Удаление элемента из таблицы, если он там есть
	void pop(std::string);

	// Поиск по ключу
	bool search(std::string);

	// Вывод таблицы
	void output();

	// Очистка всей таблицы
	void delete_table();

	// Функция чтения из файла
	friend void reading_from_file(std::ifstream&, HashTable&);
};
