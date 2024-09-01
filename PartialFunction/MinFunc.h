#pragma once
#include <iostream>
#include "ExtremalFunc.h"


class MinFunc : public ExtremalFunc {
public:
	MinFunc(const HetContainer& container);
	int32_t operator()(int32_t x) const override;
	PartialFunc* clone() const override;
};
