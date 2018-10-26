#include "pch.h"
#include "../HashTable/myFunc.h"
#include <string>
#include <vector>

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

//void TestContain(const HashTable & table, const std::vector<Data> & data);

//void TestTableEquality(const HashTable & a, const HashTable & b);

void FillExampleArray(std::vector<Data> & tableExamp) {
	tableExamp[0].key = "Ivanov Petr";
	tableExamp[1].key = "Golubev Vladislav";
	tableExamp[2].key = "Boyarkin Valeriy";
	tableExamp[3].key = "Makarov Semen";
	tableExamp[4].key = "Demichev Artem";
	tableExamp[5].key = "Doroshev Victor";
	tableExamp[6].key = "Maximov Nikita";
	tableExamp[7].key = "Buharin Petr";
	tableExamp[8].key = "Kamenev Vladimir";
	tableExamp[9].key = "Ivanov Denis";
	for (int i = 0; i < 10; i++)
		tableExamp[i].value = { unsigned char (20 + (2 * i) % 20), unsigned char (70 + (2 * i) % 20) };
}

//constructors

TEST(ConstructorsTesting, HT_Tests) {
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
	//std::vector<Data> example(10);

}