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
	size_t indexSearch(const Key& k, bool flag) const;//flag == true ����� ��� � �������, flag == false ���� ���� � �������
	void resize(size_t newsize);
	HashTable(size_t newsize);
public:
	HashTable();
	~HashTable();
	HashTable(const HashTable& b);
	// ���������� �������� ���� ���-������.
	void swap(HashTable& b);

	HashTable& operator=(const HashTable& b);
	
	// ������� ���������.
	void clear();
	// ������� ������� �� ��������� �����.
	bool erase(const Key& k);
	// ������� � ���������. ������������ �������� - ���������� �������.
	// ���� ���� k ������ � ���������� �� �������, ������������ false
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
	size_t size() const;
	bool empty() const;

	friend bool operator==(const HashTable & a, const HashTable & b);// a == b if a.used == b.used, and a.data == b.data; BUT a.size may be != b.size
	friend bool operator!=(const HashTable & a, const HashTable & b);
	// ��� ��������� Data
	friend bool operator==(const Data & a, const Data & b);
	friend bool operator!=(const Data & a, const Data & b);
};

//��������������� ���������
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