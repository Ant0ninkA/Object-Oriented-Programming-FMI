#include "T1Func.h"
#include <iostream>

T1Func::T1Func(const NVector& data, size_t N) : _invalidArguments(N){
	this->N = N;

	for (size_t i = 0; i < N; i++) {
		_invalidArguments[i] = data[i];
	}
}

bool T1Func::isDefined(int32_t x) const {
	for (size_t i = 0; i < N; i++) {
		if (_invalidArguments[i] == x) {
			return false;
		}
	}

	return true;
}


int32_t T1Func::operator()(int32_t x) const {
	if (!isDefined(x)) {
	    throw std::invalid_argument("Function is undefined in this x");
	}
	return x;
}