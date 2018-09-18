// serialize.h
#pragma once

#include <iostream>
#include <iterator>
#include <algorithm>

template <typename T>
struct serializer {
	static void apply(const T &obj, std::ostream &os) {
		const uint8_t *ptr = reinterpret_cast<const uint8_t *>(&obj);

		std::ostream_iterator<uint8_t> oi(os);

		std::copy(ptr, ptr + sizeof(T), oi);
	}
};

///////////////////////////////////////////////////////////////////////

template <typename T>
struct deserializer {
	static void apply(T &val, std::istream &is) {
		uint8_t *ptr = reinterpret_cast<uint8_t*>(&val);
		std::istream_iterator<uint8_t> ii(is);

		std::copy_n(ii, sizeof(T), ptr);
	}
};

///////////////////////////////////////////////////////////////////////

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