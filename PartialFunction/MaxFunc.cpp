#include "MaxFunc.h"
#include <iostream>

MaxFunc::MaxFunc(const HetContainer& container) : ExtremalFunc(container) {};

int32_t MaxFunc::operator()(int32_t x) const{
	if (!isDefined(x)) {
		throw std::invalid_argument("Function is undefined in this x");
	}

	int32_t max = _container[0]->operator()(x);
	for (size_t i = 0; i < _container.getSize(); i++) {
		int32_t curr = _container[i]->operator()(x);
		if (curr > max) {
			max = curr;
		}
	}

	return max;
}

PartialFunc* MaxFunc::clone() const {
	return new MaxFunc(*this);
}
