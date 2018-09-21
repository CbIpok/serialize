#pragma once

#include <initializer_list>

template <typename T>
class Temp {

public:
	explicit Temp(std::initializer_list<std::pair<T, T>> list){}
	~Temp() = default;
};

