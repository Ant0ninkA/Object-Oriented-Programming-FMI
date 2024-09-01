#pragma once
#include "NVector.h"

class T2Func {
private:
	NVector _arguments;
	size_t N;
public:
	T2Func(const NVector& data, size_t N);
	int32_t operator()(int32_t x) const;
	bool isDefined(int32_t x) const;
};
