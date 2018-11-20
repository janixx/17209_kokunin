#include "myFunc.h"
//test
HashTable::HashTable() : HashTable(startSize) {}

HashTable::HashTable(size_t newsize) {
		data.resize(newsize);
		sz = newsize;
}

HashTable::HashTable(const HashTable& b) : sz(b.sz), used(b.used), data(b.data) {}//initializer list

HashTable::~HashTable() {};

size_t HashTable::hash(const Key & k) const {
	size_t hash = 17;
	for (size_t i = 0; i < k.length(); i++) {
		hash = k[i] + (hash << 6) + (hash << 16) - hash;
	}
	return hash;
}

size_t HashTable::hash_collis(const Key & k) const {
	//stackoverflow.com/questions/7666509/hash-function-for-string
	size_t hash = 5381;
	for (size_t i = 0; i < k.length(); i++){
		hash = (((hash << 5) + hash * 33) + k[i]);/* % size; hash * 33 + c */
	}
	return hash;
}
//test
void HashTable::swap(HashTable& b) {
	std::swap(data, b.data);
	std::swap(used, b.used);
	std::swap(sz, b.sz);
}

//передаЄт номер €чейки по ключу - если находит необходимый ключ, или 
//пустую €чейку если необходимо выполнить вставку
size_t HashTable::indexSearch(const Key& k, bool flag) const {
	size_t keyInt = 0, i = 0;
	do {
		keyInt = (hash(k) + i * hash_collis(k)) % sz;
		if ((data[keyInt].key == k) || (data[keyInt].empty && flag))
			return keyInt;
		i++;
	} while (i < sz);

	return 0;
}

void HashTable::resize(size_t newsize) {
	HashTable newTable(newsize);
	for (size_t i = 0; (i < sz)/* && (newTable.used < used))*/; i++) {
		if (data[i].empty == false)
			newTable.insert(data[i].key, data[i].value);
	}
	swap(newTable);
	//sz = newsize;
	//std::swap(data, newTable.data);
}

//test
HashTable& HashTable::operator=(const HashTable& b){
	if (this != &b) {
		used = b.used;
		data = b.data;
		sz = b.sz;
	}
	return *this;
}

// Clear container; size = startSize or unchanged; used = 0 
//test
void HashTable::clear() {
	used = 0;
	data.clear();
	sz = startSize;//optional
	data.resize(sz);//also optional
}

//test
bool HashTable::erase(const Key& k) {
	size_t keyInt = indexSearch(k, false);
	if ((data[keyInt].empty == false) && (data[keyInt].key == k)) {
		data[keyInt].key.clear();
		data[keyInt].empty = true;
		data[keyInt].value = { 0,0 };
		--used;
		return true;
	}
	else
		return false;
}

//test
bool HashTable::insert(const Key& k, const Value& v) {
	if ((used > sz / 2) && (sz <= SIZE_MAX / 2)) {
		resize(3 * sz);
	}
	
	size_t keyInt = indexSearch(k, true);
	if (data[keyInt].empty == true) {
		data[keyInt].empty = false;
		data[keyInt].value = v;
		data[keyInt].key = k;
		++used;
		return true;
	}
	else
		return false;
}

bool HashTable::contains(const Key& k) const {
	size_t keyInt = indexSearch(k, false);
	
	return (data[keyInt].key == k);
}

Value& HashTable::operator[](const Key& k) {
	size_t keyInt = indexSearch(k, false);
	if (data[keyInt].key == k) {
		return data[keyInt].value;
	}
	if ((used > sz / 2) && (sz <= SIZE_MAX / 2)) {
		resize(3 * sz);
	}
	keyInt = indexSearch(k, true);
	data[keyInt].key = k;
	data[keyInt].empty = false;
	used++;
	data[keyInt].value = Value();
	return (data[keyInt].value);
}

//test
Value& HashTable::at(const Key& k) {
	size_t keyInt = indexSearch(k, false);
	if ((data[keyInt].empty == false) && (data[keyInt].key == k))
		return data[keyInt].value;
	else
		throw std::out_of_range("No this key in table, try again.");
}

const Value& HashTable::at(const Key& k) const {
	size_t keyInt = indexSearch(k, false);
	if ((data[keyInt].empty == false) && (data[keyInt].key == k))
		return data[keyInt].value;
	else
		throw std::out_of_range("No this key in table, try again.");
}

//test
size_t HashTable::size() const {
	return used;
}

bool HashTable::empty() const {
	return (used == 0);
}

bool operator==(const HashTable& a, const HashTable& b) {
	if (a.used == b.used) {
		for (size_t i = 0; i < a.sz; i++)
			if ((!a.data[i].empty) && (!b.contains(a.data[i].key)))
				return false;
		
		return true;
	}	
	return false;
}

bool operator!=(const HashTable& a, const HashTable& b) { return (!(a == b)); }

//Data operations
HashTable::Data::Data() : value(), empty(true), key("\0") {}
HashTable::Data::Data(unsigned char a, unsigned char w, Key k) : value(a, w), empty(false), key(k) {}
HashTable::Data& HashTable::Data::operator=(const Data & a) {
	key = a.key;
	value = a.value;
	empty = a.empty;
	return *this;
}
bool operator==(const HashTable::Data & a, const HashTable::Data & b) {
	if (a.empty == b.empty)
		if (a.value.age == b.value.age)
			if (a.value.weight == b.value.weight)
				if (a.key == b.key)
					return true;
	return false;
}
bool operator!=(const HashTable::Data & a, const HashTable::Data & b) {
	if (a.empty == b.empty)
		if (a.value.age == b.value.age)
			if (a.value.weight == b.value.weight)
				if (a.key == b.key)
					return false;
	return true;
}

//Value operations
Value::Value(unsigned	char a, unsigned char w) : age(a), weight(w) {}
Value::Value() : Value(0, 0) {}
Value& Value::operator=(const Value & v) {
	age = v.age;
	weight = v.weight;
	return *this;
}
bool operator==(const Value& a, const Value& b) {
	if ((a.age == b.age) && (a.weight == b.weight))
		return true;
	return false;
}