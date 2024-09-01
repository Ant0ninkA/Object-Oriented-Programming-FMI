#pragma once
#include "PartialFunc.h"
#include "HetContainer.h"

class ExtremalFunc : public PartialFunc {
protected:
	HetContainer _container;
public:
	ExtremalFunc(const HetContainer& container);
	bool isDefined(int32_t x) const override final;
};