#include "pch.h"
#include "../HashTable/myFunc.h"
#include <string>
#include <vector>
#include <ctime>
#include <fstream>

struct Data {
	Value value;
	Key key;
	Data() : value(), key("\0") {}
	Data(unsigned char a, unsigned char w, Key k) : value(a, w), key(k) {}
	Data& operator=(const Data & a) {
		key = a.key;
		value = a.value;
		return *this;
	}
};

void TestContain(const HashTable & table, const std::vector<Data> & data, size_t size) {
	size_t i = 0;
	for (; i < size; i++) {
		//if (table.contains(data[i].key)) {
			EXPECT_NO_THROW(table.at(data[i].key));
			EXPECT_EQ(table.at(data[i].key), data[i].value);
		//}
	}
	EXPECT_EQ(table.size(), i);
}

void RandomString(std::vector<Data> & example, size_t size) {
	srand(unsigned int(time(0)));
	unsigned int lenght;
	std::ofstream out("names.txt");
	for (unsigned int i = 0; i < size; i++) {
		 lenght = 4 + rand() % 3;
		example[i].key.reserve(lenght + 1);
		example[i].key.push_back(unsigned char(65 + rand() % 26));
		for (unsigned int j = 1; j < lenght; j++) {
			example[i].key.push_back(unsigned char(97 + (rand() % 26)));
		}	
		out << example[i].key/* << "\t\t Name number: "<< i */<< std::endl;
	}
	//out << size << " names saved in file." << std::endl;
	std::cout << "Array with names succesfully generated." << std::endl;
}
void ReadString(std::vector<Data> & example, size_t size) {
	std::ifstream in("names.txt");
	std::ofstream out("test.txt");
	for (size_t i = 0; i < size; i++) {
		std::getline(in, example[i].key);
		out << example[i].key << std::endl;
	}
//	std::cout << "Array with names succesfully read to vector." << std::endl;
}

void TestInsert(HashTable & table, std::vector<Data> & data, size_t size) {
	size_t counter = 0;
	for (size_t i = 0; i < size; i++) {
		EXPECT_EQ(table.size(), i);
		EXPECT_TRUE(table.insert(data[i].key, data[i].value));
		EXPECT_EQ(table.at(data[i].key), data[i].value);
		EXPECT_NO_THROW(table.at(data[i].key));
	}
	EXPECT_FALSE(table.empty());
	//std::cout << "Я дошёл до метки 4" << std::endl;
}

void FillExampleArray(std::vector<Data> & examp, size_t size, bool flag) {

	if (flag)
		RandomString(examp, size);
	else
		ReadString(examp, size);
	for (int i = 0; i < size; i++)
		examp[i].value = { unsigned char(20 + (2 * i) % 20), unsigned char(70 + (2 * i) % 20) };
}

class TableTesting : public ::testing::Test
{
protected:
	void SetUp()
	{
		tableExample = new HashTable;
		flag = false;// flag == true - random generating
		size = 1500llu;
		example.resize(size);
		FillExampleArray(example, size, flag);
		TestInsert((*tableExample), example, size);
	}
	void TearDown() {
		delete tableExample;
	}
	HashTable * tableExample;
	size_t size;// > 75 для корректной работы всех тестов при текущих параметрах таблицы
	std::vector<Data> example;
	bool flag;
};

//constructors

TEST(ConstructorsTesting, ConstructorDefaultCopyTests) {
	HashTable a;
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
	EXPECT_THROW(a.at("Vasiliy"), std::out_of_range);
	Value v = { 10,32 };
	EXPECT_TRUE(a.insert("Vasiliy", v));
	EXPECT_EQ(a.size(), 1);
	EXPECT_EQ(a.at("Vasiliy"), v);
	EXPECT_FALSE(a.insert("Vasiliy", v));
	HashTable b = a;
	EXPECT_EQ(b.size(), 1);
	EXPECT_EQ(a, b);
	EXPECT_EQ(b.at("Vasiliy"), v);
	EXPECT_TRUE(b.erase("Vasiliy"));
	EXPECT_FALSE(b.erase("Vasiliy"));
	EXPECT_EQ(b.size(), 0);
	//std::cout << "Я дошёл до метки 0" << std::endl;
}

//operations

TEST_F(TableTesting, OperationsTesting) {
	//size_t size = 150;
	//std::vector<Data> example(size);
	//FillExampleArray(example, size);
	//TestInsert(a, example, size);
	HashTable b = (*tableExample);
	EXPECT_EQ((*tableExample).size(), b.size());
	EXPECT_FALSE(b.empty());
	for (int i = 0; i < size; i++) {
		EXPECT_TRUE(b.contains(example[i].key));
		EXPECT_FALSE(b.insert(example[i].key,example[i].value));
		EXPECT_NO_THROW(b.at(example[i].key));
	}
	b.clear();
	EXPECT_TRUE(b.empty());
	EXPECT_EQ(b.size(), 0);
	for (int i = 0; i < size; i++) {
		EXPECT_FALSE(b.contains(example[i].key));
		EXPECT_THROW(b.at(example[i].key),std::out_of_range);
		EXPECT_TRUE(b.insert(example[i].key, example[i].value));
	}
	//std::cout << "Я дошёл до метки 5" << std::endl;
}

TEST_F(TableTesting, ResizeTests) {
	size_t new_size = 10;
	HashTable a;
	Value b;
	b = { 20, 50 };
	a.insert("Nnn\0", b);
	a.insert("Nnn=", b);
	a = (*tableExample);
	TestContain(a, example, size);
	//std::cout << "Я дошёл до метки 6" << std::endl;
}

TEST_F(TableTesting, SwapTests) {
	//size_t size = 1000;
	HashTable a;
	//std::vector<Data> example(size);
	//FillExampleArray(example, size);
	//TestInsert(a, example, size);
	//TestContain(a, example, size);
	Value av = { 3,3 };
	a.insert("bbb",av);
	a.swap((*tableExample));
	EXPECT_THROW(a.at("bbb"), std::out_of_range);
	TestContain(a, example, size);
	EXPECT_NO_THROW((*tableExample).at("bbb"));
	EXPECT_EQ((*tableExample).at("bbb"), av);
	(*tableExample).swap(a);
	TestContain((*tableExample), example, size);
	//std::cout << "Я дошёл до метки 7" << std::endl;
}

TEST_F(TableTesting, OperatorSquareBracketsTests) {
	Value v = Value();
	for (int i = 0; i < size; i++) {
		EXPECT_EQ((*tableExample)[example[i].key], example[i].value);
	}

	EXPECT_EQ(Value('l','p'), (*tableExample)["jjjjjjj"] = Value('l', 'p'));
	EXPECT_NO_THROW((*tableExample).at("jjjjjjj"));
	EXPECT_EQ(Value(), (*tableExample)["ffffffff"]);
	EXPECT_NO_THROW((*tableExample).at("ffffffff"));
}

TEST_F(TableTesting, EqualityTest) {
	HashTable a;
	TestInsert(a, example, size);
	EXPECT_EQ((*tableExample), a);
	HashTable b(a);
	EXPECT_EQ(a, b);
	HashTable c = a;
	EXPECT_EQ(a, b);
	b.erase(example[size - 1].key);
	EXPECT_TRUE(a != b);
	b.clear();
	EXPECT_TRUE(a != b);
}

TEST_F(TableTesting, ClearTest) {
	HashTable a((*tableExample));
	EXPECT_FALSE(a.empty());
	EXPECT_EQ(a, (*tableExample));
	a.clear();
	EXPECT_TRUE(a.empty());
	EXPECT_EQ(a.size(),0);
	EXPECT_FALSE(a == (*tableExample));
}

//Что новая ХТ является идентичной старой, а не её копией
TEST_F(TableTesting, AssigmentOperator) {
	HashTable a = (*tableExample);
	EXPECT_EQ((*tableExample), a);
	a.erase(example[1].key);
	EXPECT_NO_THROW((*tableExample).at(example[1].key));
	EXPECT_THROW(a.at(example[1].key), std::out_of_range);
	a.clear();
	EXPECT_FALSE((*tableExample).empty());
}


TEST_F(TableTesting, EraseTest) {
	for (int i = 0; i < size; i++) {
		EXPECT_TRUE((*tableExample).contains(example[i].key));
		EXPECT_TRUE((*tableExample).erase(example[i].key));
		EXPECT_FALSE((*tableExample).contains(example[i].key));
	}
	EXPECT_EQ((*tableExample).size(), 0);
	EXPECT_TRUE((*tableExample).empty());
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}