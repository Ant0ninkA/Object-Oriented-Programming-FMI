#pragma once
#include "NVector.h"

class T0Func {
private:
	NVector _arguments;
	NVector _results;
	size_t N;
public:
	T0Func(const NVector& data, size_t N);
	int32_t operator()(int32_t x) const;
	bool isDefined(int32_t x) const;
};
