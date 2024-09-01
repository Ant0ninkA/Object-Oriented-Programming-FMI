#pragma once
#include <cstdint>

class PartialFunc {
public:
	virtual int32_t operator()(int32_t x) const = 0;
	virtual bool isDefined(int32_t x) const = 0;
	virtual PartialFunc* clone() const = 0;
	virtual ~PartialFunc() = default;
};