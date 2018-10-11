#include "myFunc.h"

extern unsigned int startSize;


HashTable::HashTable() {
	data.resize(startSize);
	size = startSize;
	used = 0;
}

HashTable::~HashTable () {};

HashTable::HashTable (const HashTable& b) {
	size = b.size;
	used = b.used;
	data.resize(size);
	data = b.data;
}

unsigned int Hash(Key k, unsigned int size) {
	unsigned long hash = 33;
	for (unsigned int i = 0; i < k.length(); i++) {
		hash = k[i] + (hash << 5) + (hash << 16) - hash;
	}
	return (hash % size);
}

unsigned int HashСollis(Key k, unsigned int size) {
	//stackoverflow.com/questions/7666509/hash-function-for-string
	unsigned long hash = 5381;
	for (unsigned int i = 0; i < k.length(); i++)
		hash = ((hash << 5) + hash) + k[i]; /* hash * 33 + c */

	return (hash % size);
}

// Обменивает значения двух хэш-таблиц.
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

}

HashTable& HashTable::operator=(const HashTable& b){
	used = b.used;
	data.clear();
	data.reserve();
	data = b.data;
	size = b.size;
	used = b.used;
	return this;
}

// Очищает контейнер. Size = START_SIZE; массив имён -- пустой 
void HashTable::clear() {
	used = 0;
	data.clear();
	size = startSize;//optional
	data.resize(size);//also optional
}
// Удаляет элемент по заданному ключу.
bool HashTable::erase(const Key& k) {
	
}
// Вставка в контейнер. Возвращаемое значение - успешность вставки.
bool HashTable::insert(const Key& k, const Value& v) {
	unsigned int keyInt = 0, i = 0;
	Data tmp;
	bool flag = true;
	if (used + 1 >= size)
		resize(2 * size);
	do {
		keyInt = (Hash(k, size) + i * HashСollis(k, size)) % size;
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
		
	} while ((flag)&(i < size/2));
	return flag;
}

// Проверка наличия значения по заданному ключу.
bool HashTable::contains(const Key& k) const {
	unsigned int keyInt = 0, i = 0;
	Data tmp;
	bool flag = true, ret = false;
	do {
		keyInt = (Hash(k, size) + i * HashСollis(k, size)) % size;
		tmp = data[keyInt];
		if (tmp.key == k) {
			flag = false;
			ret = true;
		}
		else
			i++;

	} while ((flag) & (i < size));
	return ret;
}

// Возвращает значение по ключу. Небезопасный метод.
// В случае отсутствия ключа в контейнере, следует вставить в контейнер
// значение, созданное конструктором по умолчанию и вернуть ссылку на него. 
Value& HashTable::operator[](const Key& k) {};

// Возвращает значение по ключу. Бросает исключение при неудаче.
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