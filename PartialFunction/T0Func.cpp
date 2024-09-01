#include "T0Func.h"
#include <iostream>

T0Func::T0Func(const NVector& data, size_t N) : _arguments(N), _results(N) {
	this->N = N;

	for (size_t i = 0; i < N; i++) {
		_arguments[i] = data[i];
		_results[i] = data[i + N];
	}
}

bool T0Func::isDefined(int32_t x) const {
	for (size_t i = 0; i < N; i++) {
		if (_arguments[i] == x) {
			return true;
		}
	}
	return false;
}


int32_t T0Func::operator()(int32_t x) const {
	if (!isDefined(x)) {
	   throw std::invalid_argument("Function is undefined in this x");
	}

	for (size_t i = 0; i < N; i++) {
		if (_arguments[i] == x) {
			return _results[i];
		}
	}

}
