// serialize.h
#pragma once

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <map>
#include <string>

//SERIALIZER
template <typename T>
struct serializer {
	static void apply(const T &obj, std::ostream &os) {
		const uint8_t *ptr = reinterpret_cast<const uint8_t *>(&obj);

		std::ostream_iterator<uint8_t> oi(os);

		std::copy(ptr, ptr + sizeof(T), oi);
	}
};

//DESIALIZER
template <typename T>
struct deserializer {
	static void apply(T &val, std::istream &is) {
		uint8_t *ptr = reinterpret_cast<uint8_t*>(&val);
		std::istream_iterator<uint8_t> ii(is);

		std::copy_n(ii, sizeof(T), ptr);
	}
};


template <typename T>
inline void serialize(const T &obj, std::ostream &os)
{
	serializer<T>::apply(obj, os);
}

template <typename T>
inline void deserialize(T &obj, std::istream &is)
{
	return deserializer<T>::apply(obj, is);
}


//SEREALIZE VECTOR
template<typename T>
struct serializer <std::vector<T>>{
	static void apply(const std::vector<T> &obj, std::ostream &os) {
		serialize<size_t>(obj.size(), os);
		for (auto& i : obj)
		{
			serialize(i, os);
		}
	}
};

//DESEREALIZE VECTOR
template<typename T>
struct deserializer <std::vector<T>> {
	static void apply(std::vector<T> &obj, std::istream &is) {
		size_t size;
		deserialize<size_t>(size, is);
		for (size_t i = 0; i < size; i++)
		{
			T objI;
			deserialize(objI, is);
		}
	}
};


//SEREALIZE MAP
template<typename T,typename U>
struct serializer <std::map<T,U>> {
	static void apply(const std::map<T,U> &obj, std::ostream &os) {
		serialize<size_t>(obj.size(), os);
		for (auto& i : obj)
		{
			serialize(i.first, os);
			serialize(i.second, os);
		}
	}
};

//DESERIALIZE MAP
template<typename T,typename U>
struct deserializer <std::map<T,U>> {
	static void apply(std::map<T,U> &obj, std::istream &is) {
		size_t size;
		deserialize<size_t>(size, is);
		for (size_t i = 0; i < size; i++)
		{
			T first;
			U second;
			deserialize(first, is);
			deserialize(second, is);
			obj.emplace(first, second);
		}
	}
};

//SERIALIZE STRING
template <>
struct serializer<std::string> {
	static void apply(const std::string&obj, std::ostream &os) {
		serialize<size_t>(obj.size(), os);
		os << obj;
	}
};

//DESERIALIZE STRING
template<>
struct deserializer <std::string>{
	static void apply(std::string &obj, std::istream &is) {
		size_t size;
		deserialize<size_t>(size, is);
		char* buf = (char*)malloc(sizeof(char)*size);
		is.read(buf, size);
		obj = std::string(buf);
		free(buf);
	}
};
