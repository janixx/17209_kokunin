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
	Value (unsigned	char a, unsigned char w) {
		age = a;
		weight = w;
	}
	Value() {//а это надо?
		age = 0;
		weight = 0;
	}
};

struct Data {
	Value value;
	bool empty;// true -- slot is empty, false -- slot isn't empty
	Key key;
	friend bool operator==(const Data & a, const Data & b);
	friend bool operator!=(const Data & a, const Data & b);
	/*Data() {
		value = {0, 0};
		key = nullptr;
		empty = true;
	}*/
};

class HashTable {
private:
	std::vector<Data> data;
	unsigned int size;
	unsigned int used;//size_t
	const static unsigned int startSize = 100;
public:
	HashTable();
	~HashTable();
	HashTable(unsigned int newsize);

	HashTable(const HashTable& b);

	// Мои функции, самостройные функции.
	void resize(unsigned long newsize);

	// Обменивает значения двух хэш-таблиц.
	void swap(HashTable& b);

	HashTable& operator=(const HashTable& b);
	
	// Очищает контейнер.
	void clear();
	// Удаляет элемент по заданному ключу.
	bool erase(const Key& k);
	// Вставка в контейнер. Возвращаемое значение - успешность вставки.
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
	unsigned int Size() const;
	bool empty() const;

	friend bool operator==(const HashTable & a, const HashTable & b);// a == b if a.used == b.used, and a.data == b.data; BUT a.size may be != b.size
	friend bool operator!=(const HashTable & a, const HashTable & b);
};

unsigned int Hash(Key k, unsigned int size);
unsigned int HashCollis(Key k, unsigned int size);