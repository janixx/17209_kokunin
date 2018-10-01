#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

#define START_SIZE 50

typedef std::string keys;

struct value {
	unsigned char age;
	unsigned char weight;
};

class hashTable {
	keys** key;
	value* value;
	unsigned int size;
	unsigned int used;
public:
	hashTable() {
		size = START_SIZE;
		key = (keys**)(malloc(sizeof(keys*)*size));//это так работает?
		for (int i = 0; i < size; i++)
			key[i] = NULL;
		value = (struct value*)(calloc(size,sizeof(value)));//а это?
		used = 0;
	}
	~hashTable() {
		for (int i = 0; i < size; i++)м
			free(key[i]);
		free(value);
	}
	hashTable(const hashTable& b) {
		size = b.size;
		used = b.used;
		key = (keys**)(malloc(sizeof(keys*)*size));
		for (int i = 0; i < size; i++){
			if (b.key[i] != NULL) {

				/*копирование строк -- наладить!*/

			}
			else this->key[i] = NULL;
		}
		value = (struct value*)(calloc(size, sizeof(value)));
		for (int i = 0; i < size; i++) {// fixme: add empty check
			b.value[i].age = value[i].age;
			b.value[i].weight = value[i].weight;
		}
	}
	unsigned int hashCol(const keys& key) {
		//stackoverflow.com/questions/7666509/hash-function-for-string
		unsigned long hash = 5381;
		for (int i = 0; i < key.length; i++)
			hash = ((hash << 5) + hash) + key[i]; /* hash * 33 + c */

		return (hash % size);
	}
	unsigned int hash(const keys& key) {
		unsigned long hash = 33;
		for (int i = 0; i < key.length; i++) {
			hash = key[i] + (hash << 5) + (hash << 16) - hash;
		}
		return (hash % size);
	}
	// Обменивает значения двух хэш-таблиц.
	void swap(hashTable& b);
	hashTable& operator=(const hashTable& b){
		used = b.used;
		for (int i = 0; i < size; i++)
			free(key[i]);
		free(value);
		size = b.size;
		key = (keys**)(malloc(sizeof(keys*)*size));
		for (int i = 0; i < size; i++) {
			if (b.key[i] != NULL) {

				/*копирование строк -- наладить!*/

			}
			else this->key[i] = NULL;
		}
		value = (struct value*)(calloc(size, sizeof(value)));
		for (int i = 0; i < size; i++) {// fixme: add empty check
			b.value[i].age = value[i].age;
			b.value[i].weight = value[i].weight;
		}
		hashTable& ret = b;//?
		return ret;
	}
	// Очищает контейнер. Size = START_SIZE; массив имён -- пустой 
	void clear() {
		for (int i = 0; i < size; i++) {
			if (key[i] != NULL)
				free(key[i]);
		}
		free(key);
		free(value);
		used = 0;
		size = START_SIZE;//optional
		//не точно
		key = (keys**)(malloc(sizeof(keys*)*size));
		for (int i = 0; i < size; i++)
			key[i] = NULL;
		value = (struct value*)(calloc(size, sizeof(value)));
		//
	}
	// Удаляет элемент по заданному ключу.
	bool erase(const keys& k) {
		
	}
	// Вставка в контейнер. Возвращаемое значение - успешность вставки.
	bool insert(const keys& k, const value& v) {

	}

	// Проверка наличия значения по заданному ключу.
	bool contains(const keys& k) const {

	}

	// Возвращает значение по ключу. Небезопасный метод.
	// В случае отсутствия ключа в контейнере, следует вставить в контейнер
	// значение, созданное конструктором по умолчанию и вернуть ссылку на него. 
	value& operator[](const keys& k);

	// Возвращает значение по ключу. Бросает исключение при неудаче.
	value& at(const keys& k);
	const value& at(const keys& k) const;

	size_t size() const;
	bool empty() const;

	friend bool operator==(const hashTable & a, const hashTable & b);
	friend bool operator!=(const hashTable & a, const hashTable & b);
};

int main(int argc, char ** argv) {
	
}