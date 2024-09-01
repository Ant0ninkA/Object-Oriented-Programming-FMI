#include "T2Func.h"
#include <iostream>

T2Func::T2Func(const NVector& data, size_t N) : _arguments(N) {
	this->N = N;

	for (size_t i = 0; i < N; i++) {
		_arguments[i] = data[i];
	}
}

bool T2Func::isDefined(int32_t x) const {
	return true;
}


int32_t T2Func::operator()(int32_t x) const {
	for (size_t i = 0; i < N; i++) {
		if (_arguments[i] == x) {
			return 1;
		}
	}
	return 0;
}