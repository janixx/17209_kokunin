#include "pch.h"
#include "gtest/gtest.h"
#include "C:/Users/Admin/Documents/Visual Studio 2017/Projects/HashTable/HashTable/myFunc.h"


TEST(TestCaseName, TestName) {
	HashTable a;
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(JustTest, First) {
	HashTable a(50);
	Value v = { 50, 11 };
	a.insert("Fedor Ivanov", v);
	HashTable b = a;
	EXPECT_EQ(a.Size(),b.Size());
	EXPECT_TRUE(a.at("Fedor Ivanov").age == v.age);
	EXPECT_TRUE(a.at("Fedor Ivanov").weight == v.weight);
}

//int main(int argc, char **argv) {
//	::testing::InitGoogleTest(&argc, argv);
//	return RUN_ALL_TESTS();
//}