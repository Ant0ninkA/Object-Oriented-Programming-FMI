#include "MinFunc.h"
#include <iostream>

MinFunc::MinFunc(const HetContainer& container) : ExtremalFunc(container) {};

int32_t MinFunc::operator()(int32_t x) const {
	if (!isDefined(x)) {
		throw std::invalid_argument("Function is undefined in this x");
	}

	int32_t min = _container[0]->operator()(x);
	for (size_t i = 0; i < _container.getSize(); i++) {
		int32_t curr = _container[i]->operator()(x);
		if (curr < min) {
			min = curr;
		}
	}

	return min;
}

PartialFunc* MinFunc::clone() const{
	return new MinFunc(*this);
}
