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

	// ��� �������, ������������ �������.
	void resize(unsigned long newsize);

	// ���������� �������� ���� ���-������.
	// ���������, ����� ����� ���� �����, ��� ������� ����������� �������
	// std::swap.
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

	std::size_t Size() const;
	bool empty() const;

	friend bool operator==(const HashTable & a, const HashTable & b);
	friend bool operator!=(const HashTable & a, const HashTable & b);
};

unsigned int Hash(Key k, unsigned int size);
unsigned int Hash�ollis(Key k, unsigned int size);