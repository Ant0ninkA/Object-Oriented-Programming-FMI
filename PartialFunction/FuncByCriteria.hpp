#include "PartialFunc.h"
#include <iostream>

template<class T>
class FuncByCriteria : public PartialFunc{
private:
	T myFunc;
public:
	FuncByCriteria(const T& obj);
	bool isDefined(int32_t x) const override;
	int32_t operator()(int32_t x) const override;
	PartialFunc* clone() const override;
};

template<class T>
FuncByCriteria<T>::FuncByCriteria(const T& obj) : myFunc(obj) {}

template<class T>
bool FuncByCriteria<T>::isDefined(int32_t x) const{
	return myFunc.isDefined(x);
}

template<class T>
int32_t FuncByCriteria<T>::operator()(int32_t x) const{
	if (!(myFunc.isDefined(x))) {
		throw std::invalid_argument("Function is undefined in this x");
	}

	return myFunc.operator()(x);
}

template<class T>
PartialFunc* FuncByCriteria<T>::clone() const {
	return new FuncByCriteria(*this);
}

