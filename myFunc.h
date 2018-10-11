#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

unsigned int startSize = 100;

typedef std::string Key;

struct Value {
	unsigned char age;
	unsigned char weight;
};

struct Data {
	Value value;
	bool empty;
	Key key;
};

class HashTable {
private:
	std::vector<Data> data;
	unsigned int size;
	unsigned int used;
public:
	HashTable();
	~HashTable();

	HashTable(const HashTable& b);

	// Мои функции, самостройные функции.
	void resize(unsigned long newsize);

	// Обменивает значения двух хэш-таблиц.
	// Подумайте, зачем нужен этот метод, при наличии стандартной функции
	// std::swap.
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

	std::size_t Size() const;
	bool empty() const;

	friend bool operator==(const HashTable & a, const HashTable & b);
	friend bool operator!=(const HashTable & a, const HashTable & b);
};

unsigned int Hash(Key k, unsigned int size);
unsigned int HashСollis(Key k, unsigned int size);