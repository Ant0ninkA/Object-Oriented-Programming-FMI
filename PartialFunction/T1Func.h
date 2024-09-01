#pragma once
#include "NVector.h"

class T1Func {
private:
	NVector _invalidArguments;
	size_t N;
public:
	T1Func(const NVector& data, size_t N);
	int32_t operator()(int32_t x) const;
	bool isDefined(int32_t x) const;

};
