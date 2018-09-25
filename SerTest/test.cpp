#include "pch.h"

#include "temp.h"

#include <serialize.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>
using namespace std;


class TestCaseFixing : public ::testing::Test {
protected:
	virtual void SetUp(void) {
		// настройка перед запуском очередного теста
	}
	virtual void TearDown(void) {
		// очистка после прогона очередного теста
	}

	size_t LENGHT = 1000;
	string objString;
	vector<string> objVectorString;
	map<string,string> objMapStringString;
	vector<map<string,string>> objVectorMapStringString;
	map<string,vector<string>> objMapStringVectorString;
	 
	template<typename T>
	bool test(T obj)
	{
		ofstream ofs("obj.ser");
		serialize(obj, ofs);
		ofs.close();
		T tobj;
		ifstream ifs("obj.ser");
		ifs >> noskipws;
		deserialize(tobj, ifs);
		return obj == tobj;
	}

};

TEST_F(TestCaseFixing, NullString)
{
	ASSERT_TRUE(test(objString));
}

TEST_F(TestCaseFixing, NotNullString)
{
	objString = "test\0\n\0\0\0";
	ASSERT_TRUE(test(objString));
}

TEST_F(TestCaseFixing, NullVectorString)
{
	ASSERT_TRUE(test(objVectorString));
}

TEST_F(TestCaseFixing, NotNullVectorString)
{
	for (size_t i = 0; i < LENGHT; i++)
	{
		objVectorString.push_back(std::to_string(i));
	}
	ASSERT_TRUE(test(objVectorString));
}

TEST_F(TestCaseFixing, NullMapStringString)
{
	ASSERT_TRUE(test(objMapStringString));
}

TEST_F(TestCaseFixing, NotNullMapStringString)
{
	for (size_t i = 0; i < LENGHT; i++)
	{
		objMapStringString.emplace(to_string(i), to_string(i));
	}
	ASSERT_TRUE(test(objMapStringString));
}


TEST_F(TestCaseFixing, NullVectorMapStringString)
{
	ASSERT_TRUE(test(objVectorMapStringString));
}

TEST_F(TestCaseFixing, NotNullVectorMapStringString)
{
	for (size_t i = 0; i < LENGHT; i++)
	{
		map<string, string> toPushBack;
		for (size_t j = 0; j < LENGHT; j++)
		{
			toPushBack.emplace(to_string(j), to_string(j));
		}
		objVectorMapStringString.push_back(toPushBack);
	}
	ASSERT_TRUE(test(objVectorMapStringString));
}



TEST_F(TestCaseFixing, NullMapStringVectorString)
{
	ASSERT_TRUE(test(objMapStringVectorString));
}

TEST_F(TestCaseFixing, NotNullMapStringVectorString)
{
	for (size_t i = 0; i < LENGHT; i++)
	{
		vector<string> toEmplace;
		for (size_t j = 0; j < LENGHT; j++)
		{
			toEmplace.push_back(to_string(j));
		}
		objMapStringVectorString.emplace(to_string(i), toEmplace);
	}
	ASSERT_TRUE(test(objMapStringVectorString));
}
