#include "myFunc.h"

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


HashTable::HashTable() : HashTable(startSize) {}

HashTable::HashTable(size_t newsize) {
	data.resize(newsize);
	sz = newsize;
	used = 0;
}

HashTable::HashTable(const HashTable& b) : sz(b.sz), used(b.used), data(b.data) {}//initializer list

HashTable::~HashTable() {};

size_t HashTable::hash(const Key & k) const {
	unsigned long long hash = 33;
	for (size_t i = 0; i < k.length(); i++) {
		hash = k[i] + (hash << 5) + (hash << 16) - hash;
	}
	return (hash % sz);
}

size_t HashTable::hashCollis(const Key & k) const {
	//stackoverflow.com/questions/7666509/hash-function-for-string
	unsigned long long hash = 5381;
	for (unsigned int i = 0; i < k.length(); i++){
		hash = (((hash << 5) + hash) + k[i]);/* % size; hash * 33 + c */
	}
	return (hash % sz);
}

void HashTable::swap(HashTable& b) {
	std::swap(data, b.data);
	std::swap(used, b.used);
	std::swap(sz, b.sz);
}

//передаЄт номер €чейки по ключу. ≈сли €чейка свободна возвращает еЄ индекс, если находит 
//в некоторой €чейке соответствующей данной ключ - возвращает 
size_t HashTable::indexSearch(const Key& k) const {
	size_t keyInt = 0, i = 0;
	do {
		keyInt = (hash(k) + i * hashCollis(k)) % sz;
		if ((data[keyInt].empty == true) || (data[keyInt].key == k))
			break;
		else
			i++;
	} while (i < sz);
	return keyInt;
}

void HashTable::resize(size_t newsize) {
	HashTable newTable(newsize);
	size_t i = 0;
	for (; ((i < sz)&&(newTable.used < used)); i++) {
		if (data[i].empty == false)
			newTable.insert(data[i].key, data[i].value);
	}
	sz = newsize;
	std::swap(data, newTable.data);
}

HashTable& HashTable::operator=(const HashTable& b){
	if (this != &b) {
		used = b.used;
		data = b.data;
		sz = b.sz;
	}
	return *this;
}

// Clear container; size = startSize or unchanged; used = 0 
void HashTable::clear() {
	used = 0;
	data.clear();
	sz = startSize;//optional
	data.resize(sz);//also optional
}

bool HashTable::erase(const Key& k) {
	size_t keyInt = indexSearch(k);
	if ((data[keyInt].empty == false) && (data[keyInt].key == k)) {
		data[keyInt].key.clear();
		data[keyInt].empty = true;
		data[keyInt].value = { 0,0 };
		used--;
		return true;
	}
	else
		return false;
}

bool HashTable::insert(const Key& k, const Value& v) {
	if ((used + 1 >= sz) && (sz <= SIZE_MAX / 2))
		resize(2 * sz);

	size_t keyInt = indexSearch(k);
	if (data[keyInt].empty == true) {
		data[keyInt].empty = false;
		data[keyInt].value = v;
		data[keyInt].key = k;
		used++;
		return true;
	}
	else
		return false;
}

bool HashTable::contains(const Key& k) const {
	size_t keyInt = indexSearch(k);
	
	if ((data[keyInt].empty == false) && (data[keyInt].key == k))
		return true;
	else
		return false;
}

Value& HashTable::operator[](const Key& k) {
	size_t keyInt = indexSearch(k);
	if ((data[keyInt].empty == false) && (data[keyInt].key == k))
		return data[keyInt].value;
	else {
		Value v;
		return v;
	}
}

Value& HashTable::at(const Key& k) {
	size_t keyInt = indexSearch(k);
	if ((data[keyInt].empty == false) && (data[keyInt].key == k))
		return data[keyInt].value;
	else
		throw std::out_of_range("No this key in table, try again.");
}

const Value& HashTable::at(const Key& k) const {
	size_t keyInt = indexSearch(k);
	if ((data[keyInt].empty == false) && (data[keyInt].key == k))
		return data[keyInt].value;
	else
		throw std::out_of_range("No this key in table, try again.");
}

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
	else
		return false;
}

bool operator!=(const HashTable& a, const HashTable& b) {
	return (!(a == b));
}


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