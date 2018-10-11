#include "myFunc.h"

extern unsigned int startSize;

HashTable::HashTable() {
	data.resize(startSize);
	size = startSize;
	used = 0;
}

HashTable::HashTable(unsigned int newsize) {
	data.resize(newsize);
	size = newsize;
	used = 0;
}

HashTable::HashTable (const HashTable& b) {
	size = b.size;
	used = b.used;
	data.resize(size);
	data = b.data;
}

HashTable::~HashTable() {};

unsigned int Hash(Key k, unsigned int size) {
	unsigned long hash = 33;
	for (unsigned int i = 0; i < k.length(); i++) {
		hash = k[i] + (hash << 5) + (hash << 16) - hash;
	}
	return (hash % size);
}

unsigned int Hash—ollis(Key k, unsigned int size) {
	//stackoverflow.com/questions/7666509/hash-function-for-string
	unsigned long hash = 5381;
	for (unsigned int i = 0; i < k.length(); i++)
		hash = ((hash << 5) + hash) + k[i]; /* hash * 33 + c */

	return (hash % size);
}

void HashTable::swap(HashTable& b) {
	std::vector<Data> tmpD;
	tmpD.reserve(size);
	tmpD = data;
	data.reserve(b.size);
	data = b.data;
	b.data.reserve(size);
	b.data = tmpD;
	if (b.used != used) {
		unsigned int tmpU = used;
		used = b.used;
		b.used = tmpU;
	}

	if (b.size != size) {
		unsigned int tmpS = size;
		size = b.size;
		b.size = tmpS;
	}
}

void HashTable::resize(unsigned long newsize) {
	HashTable newTable(newsize);
	unsigned int i = 0;
	Data tmp;
	for (; ((i < size)&&(used < newTable.used)); i++) {
		tmp = data[i];
		if (tmp.empty == false)
			newTable.insert(tmp.key, tmp.value);
	}
	newTable.size = newsize;
	size = newsize;
	data.reserve(newsize);
	data = newTable.data;
}

HashTable& HashTable::operator=(const HashTable& b){
	used = b.used;
	data.clear();
	data.reserve(b.size);
	data = b.data;
	size = b.size;
	used = b.used;
	return b;
}

// Clear container; size = startSize or unchanged; used = 0 
void HashTable::clear() {
	used = 0;
	data.clear();
	size = startSize;//optional
	data.resize(size);//also optional
}

bool HashTable::erase(const Key& k) {
	unsigned int keyInt = 0, i = 0;
	Data tmp;
	bool flag = true, ret = false;
	do {
		keyInt = (Hash(k, size) + i * Hash—ollis(k, size)) % size;
		tmp = data[keyInt];
		if ((tmp.empty == false)&&(tmp.key == k)) {
			used--;
			tmp.empty = true;
			tmp.value = { 0,0 };
			tmp.key.clear();
			flag = false;
			ret = true;
		}
		else
			i++;
	} while ((flag)&&(i < size));
	return ret;
}

bool HashTable::insert(const Key& k, const Value& v) {
	unsigned int keyInt = 0, i = 0;
	Data tmp;
	bool flag = true;
	if (used + 1 >= size)
		resize(2 * size);
	do {
		keyInt = (Hash(k, size) + i * Hash—ollis(k, size)) % size;
		tmp = data[keyInt];
		if (tmp.empty == true) {
			tmp.key = k;
			tmp.empty = false;
			tmp.value = v;
			data[keyInt] = tmp;
			used++;
			flag = false;
		}
		else
			i++;
		
	} while ((flag)&&(i < size/2));
	return flag;
}

bool HashTable::contains(const Key& k) const {
	unsigned int keyInt = 0, i = 0;
	Data tmp;
	bool flag = true, ret = false;
	do {
		keyInt = (Hash(k, size) + i * Hash—ollis(k, size)) % size;
		tmp = data[keyInt];
		if (tmp.key == k) {
			flag = false;
			ret = true;
		}
		else
			i++;

	} while ((flag) && (i < size));
	return ret;
}

Value& HashTable::operator[](const Key& k) {};

Value& HashTable::at(const Key& k) {}
const Value& HashTable::at(const Key& k) const {}

std::size_t HashTable::Size() const {
	return std::size_t(size);
}
bool HashTable::empty() const {
	return (used == 0) ? true : false;
}

bool HashTable::operator==(const HashTable& a, const HashTable& b);
bool HashTable::operator!=(const HashTable& a, const HashTable& b);
};

int main(int argc, char ** argv) {
	
}