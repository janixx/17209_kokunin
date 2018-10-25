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
	Value() {//� ��� ����?
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

	// ��� �������, ������������ �������.
	void resize(unsigned long newsize);

	// ���������� �������� ���� ���-������.
	void swap(HashTable& b);

	HashTable& operator=(const HashTable& b);
	
	// ������� ���������.
	void clear();
	// ������� ������� �� ��������� �����.
	bool erase(const Key& k);
	// ������� � ���������. ������������ �������� - ���������� �������.
	bool insert(const Key& k, const Value& v);

	// �������� ������� �������� �� ��������� �����.
	bool contains(const Key& k) const;

	// ���������� �������� �� �����. ������������ �����.
	// � ������ ���������� ����� � ����������, ������� �������� � ���������
	// ��������, ��������� ������������� �� ��������� � ������� ������ �� ����. 
	Value& operator[](const Key& k);

	// ���������� �������� �� �����. ������� ���������� ��� �������.
	Value& at(const Key& k);
	const Value& at(const Key& k) const;
	// ���������� ���������� ����������� ���������
	unsigned int Size() const;
	bool empty() const;

	friend bool operator==(const HashTable & a, const HashTable & b);// a == b if a.used == b.used, and a.data == b.data; BUT a.size may be != b.size
	friend bool operator!=(const HashTable & a, const HashTable & b);
};

unsigned int Hash(Key k, unsigned int size);
unsigned int HashCollis(Key k, unsigned int size);