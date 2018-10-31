#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

typedef std::string Key;

struct Value {
	unsigned char age;
	unsigned char weight;

	Value(unsigned	char a, unsigned char w);
	Value();
	Value& operator=(const Value & v);
};

bool operator==(const Value& a, const Value& b);

class HashTable {
private:
	struct Data;
	std::vector<Data> data;
	size_t sz;
	size_t used = 0;
	const static size_t startSize = 61;
private: //my functions
	size_t hash(const Key & k) const;
	size_t hash_collis(const Key & k) const;
	size_t indexSearch(const Key& k, bool flag) const;//flag == true ключа нет в таблице, flag == false ключ есть в таблице
	void resize(size_t newsize);
	HashTable(size_t newsize);
public:
	HashTable();
	~HashTable();
	HashTable(const HashTable& b);
	// Обменивает значения двух хэш-таблиц.
	void swap(HashTable& b);

	HashTable& operator=(const HashTable& b);
	
	// Очищает контейнер.
	void clear();
	// Удаляет элемент по заданному ключу.
	bool erase(const Key& k);
	// Вставка в контейнер. Возвращаемое значение - успешность вставки.
	// Если ключ k имелся в контейнере до вставки, возвращается false
	bool insert(const Key& k, const Value& v);

	// Проверка наличия значения по заданному ключу.
	bool contains(const Key& k) const;

	// Возвращает значение по ключу. Небезопасный метод.
	// В случае отсутствия ключа в контейнере, следует вставить в контейнер
	// значение, созданное конструктором по умолчанию и вернуть ссылку на него. 
	Value& operator[](const Key& k);

	// Возвращает значение по ключу. Бросает исключение при неудаче.
	Value& at(const Key& k);
	const Value& at(const Key& k) const;
	// Возвращает количество вставленных элементов
	size_t size() const;
	bool empty() const;

	friend bool operator==(const HashTable & a, const HashTable & b);// a == b if a.used == b.used, and a.data == b.data; BUT a.size may be != b.size
	friend bool operator!=(const HashTable & a, const HashTable & b);
	// Для сравнения Data
	friend bool operator==(const Data & a, const Data & b);
	friend bool operator!=(const Data & a, const Data & b);
};

//Вспомогательная структура
struct HashTable::Data {
	Value value;
	bool empty;// true -- slot is empty, false -- slot isn't empty
	Key key;

	Data();
	Data(unsigned char a, unsigned char w, Key k);
	Data& operator=(const Data & a);
	friend bool operator==(const Data & a, const Data & b);
	friend bool operator!=(const Data & a, const Data & b);
};
//unsigned int Hash(Key k, unsigned int size);
//unsigned int HashCollis(Key k, unsigned int size);