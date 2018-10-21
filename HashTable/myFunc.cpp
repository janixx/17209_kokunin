#include "myFunc.h"

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

HashTable::~HashTable() {
	//data.clear();
	data.~vector();
};

unsigned int Hash(Key k, unsigned int size) {
	unsigned long hash = 33;
	for (unsigned int i = 0; i < k.length(); i++) {
		hash = k[i] + (hash << 5) + (hash << 16) - hash;
	}
	return (hash % size);
}

unsigned int HashCollis(Key k, unsigned int size) {
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

	return *this;
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
		keyInt = (Hash(k, size) + i * HashCollis(k, size)) % size;
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
		keyInt = (Hash(k, size) + i * HashCollis(k, size)) % size;
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
		keyInt = (Hash(k, size) + i * HashCollis(k, size)) % size;
		tmp = data[keyInt];
		if (tmp.empty == false) {
			if (tmp.key == k) {
				flag = false;
				ret = true;
			}
			else ret = false;
		}
		i++;
	} while ((flag) && (i < size));
	return ret;
}

Value& HashTable::operator[](const Key& k) {
	unsigned int keyInt = 0, i = 0;
	bool flag = false;
	Data tmp;
	do {
		keyInt = (Hash(k, size) + i * HashCollis(k, size)) % size;
		tmp = data[keyInt];
		if (tmp.empty == true) {
			if (tmp.key == k)
				flag = true;
			break;
		}
		/*else if (tmp.empty == true) {
			tmp.key = k;
			tmp.empty = false;
			tmp.value = 
		}*/
		else
			i++;
	} while (i < size);
	Data& tmp_L = data[keyInt];
	if (flag == false) {
		tmp_L.value.age = 0;
		tmp_L.value.weight = 0;
		tmp_L.key = k;
		tmp_L.empty = false;
	}
	Value& ret = tmp_L.value;
	return ret;
}
Value& HashTable::at(const Key& k) {
	unsigned int keyInt = 0, i = 0;
	bool flag = false;
	Data tmp;
	do {
		keyInt = (Hash(k, size) + i * HashCollis(k, size)) % size;
		tmp = data[keyInt];
		if (tmp.empty == false)
			if (tmp.key == k) {
				flag = true;
				break;
			}
		else
			i++;
	} while (i < size);
	if (flag == true) {
		Data& tmp_L = data[keyInt];
		Value& ret = tmp_L.value;
		return ret;
	}
	throw false;
}

const Value& HashTable::at(const Key& k) const {
	unsigned int keyInt = 0, i = 0;
	bool flag = false;
	Data tmp;
	do {
		keyInt = (Hash(k, size) + i * HashCollis(k, size)) % size;
		tmp = data[keyInt];
		if (tmp.empty == false)
			if (tmp.key == k) {
				flag = true;
				break;
			}
			else
				i++;
	} while (i < size);
	if (flag == true) {
		const Data& tmp_L = data[keyInt];
		const Value& ret = tmp_L.value;
		return ret;
	}
	throw false;
}

unsigned int HashTable::Size() const {
	return used;
}

bool HashTable::empty() const {
	return (used == 0);
}

bool operator==(const HashTable& a, const HashTable& b) {
	bool ret = false;
	unsigned int maxIndex = 0, i = 0;
	if (a.size >= b.size)
		maxIndex = b.size;
	else
		maxIndex = a.size;
	if (a.used == b.used) {
		ret = true;
		for (; i < maxIndex; i++)
			if (a.data[i] != b.data[i]) {
				ret = false;
				break;
			}
	}
	return ret;
}

bool operator!=(const HashTable& a, const HashTable& b) {
	bool ret = false;
	unsigned int maxIndex = 0, i = 0;
	if (a.size >= b.size)
		maxIndex = b.size;
	else
		maxIndex = a.size;
	if (a.used != b.used) {
		ret = true;
	for (; i < maxIndex; i++)
		if (a.data[i] == b.data[i]) {
			ret = false;
			break;
		}
	}	
	return ret;
}

bool operator==(const Data & a, const Data & b) {
	if (a.empty == b.empty)
		if (a.value.age == b.value.age)
			if (a.value.weight == b.value.weight)
				if (a.key == b.key)
					return true;
	return false;
}

bool operator!=(const Data & a, const Data & b) {
	if (a.empty == b.empty)
		if (a.value.age == b.value.age)
			if (a.value.weight == b.value.weight)
				if (a.key == b.key)
					return false;
	return true;
}