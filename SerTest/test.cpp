#include "pch.h"
#include <serialize.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>
using namespace std;
static int LENGHT = 1000;

TEST(Stiring, Null)
{
	ofstream ofs("NullString");
	string obj;
	string tobj;
	serialize(obj, ofs);
	ofs.close();
	ifstream ifs("NullString");
	ifs >> noskipws;
	deserialize(tobj, ifs);
	ASSERT_TRUE(obj == tobj);	
}

TEST(Stiring, NotNull)
{
	ofstream ofs("NullString");
	string obj = "123";
	string tobj;
	serialize(obj, ofs);
	ofs.close();
	ifstream ifs("NullString");
	deserialize(tobj, ifs);
	ASSERT_TRUE(obj == tobj);
}

TEST(VectorString, Null)
{
	ofstream ofs("VectorString");
	vector<string> obj;
	vector<string> tobj;
	serialize(obj, ofs);
	ofs.close();
	ifstream ifs("VectorString");
	deserialize(tobj, ifs);
	ASSERT_TRUE(obj == tobj);
}

TEST(VectorString, NotNull)
{
	ofstream ofs("VectorString");
	vector<string> obj;
	for (int i = 0; i < LENGHT; i++)
	{
		obj.push_back(std::to_string(i));
	}
	vector<string> tobj;
	serialize(obj, ofs);
	ofs.close();
	ifstream ifs("VectorString");
	ifs >> noskipws;
	deserialize(tobj, ifs);
	ASSERT_TRUE(obj == tobj);
}

TEST(MapStringString, Null)
{
	ofstream ofs("MapStringString");
	string obj;
	string tobj;
	serialize(obj, ofs);
	ofs.close();
	ifstream ifs("MapStringString");
	deserialize(tobj, ifs);
	ASSERT_TRUE(obj == tobj);
}

TEST(MapStringString, NotNull)
{
	ofstream ofs("MapStringString");
	map<string,string> obj;
	for (size_t i = 0; i < LENGHT; i++)
	{
		obj.emplace(to_string(i), to_string(i));
	}
	map<string, string> tobj;
	serialize(obj, ofs);
	ofs.close();
	ifstream ifs("MapStringString");
	ifs >> noskipws;
	deserialize(tobj, ifs);
	ASSERT_TRUE(obj == tobj);
}

TEST(VectorMapStringString, Null)
{
	ofstream ofs("VectorMapStringString");
	vector<map<string,string>> obj;
	vector<map<string, string>> tobj;
	serialize(obj, ofs);
	ofs.close();
	ifstream ifs("VectorMapStringString");
	ifs >> noskipws;
	deserialize(tobj, ifs);
	ASSERT_TRUE(obj == tobj);
}

TEST(VectorMapStringString, NotNull)
{
	ofstream ofs("VectorMapStringString");
	vector<map<string, string>> obj;
	for (size_t i = 0; i < LENGHT; i++)
	{
		map<string, string> toPushBack;
		for (size_t j = 0; j < LENGHT; j++)
		{
			toPushBack.emplace(to_string(10*i + j), to_string(10*i + j));
		}
	}
	vector<map<string, string>> tobj;
	serialize(obj, ofs);
	ofs.close();
	ifstream ifs("VectorMapStringString");
	ifs >> noskipws;
	deserialize(tobj, ifs);
	ASSERT_TRUE(obj == tobj);
}

TEST(MapStringVectorString, Null)
{
	ofstream ofs("MapStringVectorString");
	map<string, vector<string>> obj;
	map<string, vector<string>> tobj;
	serialize(obj, ofs);
	ofs.close();
	ifstream ifs("MapStringVectorString");
	ifs >> noskipws;
	deserialize(tobj, ifs);
	ASSERT_TRUE(obj == tobj);
}

TEST(MapStringVectorString, NotNull)
{
	ofstream ofs("MapStringVectorString");
	map<string,vector<string>> obj;
	for (size_t i = 0; i < LENGHT; i++)
	{
		vector<string> toEmplace;
		for (size_t j = 0; j < LENGHT; j++)
		{
			toEmplace.push_back(to_string(j));
		}
		obj.emplace(to_string(i), toEmplace);
	}
	map<string, vector<string>> tobj;
	serialize(obj, ofs);
	ofs.close();
	ifstream ifs("MapStringVectorString");
	ifs >> noskipws;
	deserialize(tobj, ifs);
	ASSERT_TRUE(obj == tobj);
}