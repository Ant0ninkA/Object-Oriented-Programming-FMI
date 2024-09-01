#include "ExtremalFunc.h"

ExtremalFunc::ExtremalFunc(const HetContainer& container) : _container(container) {}

bool ExtremalFunc::isDefined(int32_t x) const {

	for (size_t i = 0; i < _container.getSize(); i++) {
		if (!(_container[i]->isDefined(x))) {
			return false;
		}
	}
	return true;
}

