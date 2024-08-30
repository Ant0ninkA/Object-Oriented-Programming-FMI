#pragma once
#include <iostream>
#include "ModifiableIntegerFunction.h"

short func1(short x) {
	return x + 1;
}

short func2(short x) {
	return x;
}

short del3(short x) {
	return x / 3;
}

int main() {
	ModifiableIntegerFunction f(func1);
	ModifiableIntegerFunction g(func2);
	ModifiableIntegerFunction h(func1);


	g ^ 2;

	g.drawPoints(-10, 0 , 10, 20);

}
