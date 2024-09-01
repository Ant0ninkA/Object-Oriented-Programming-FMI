#include <iostream>
#include <fstream>
#include "FuncFactory.h"
#include "PartialFunc.h"

int main()
{
	std::ifstream is("func.dat", std::ios::binary);
	if (!is.is_open()) {
		throw std::invalid_argument("This file cannot be opened");
	}

    PartialFunc* func = funcFactory(is);
    if (!func) {
        throw std::invalid_argument("Failed to create function from the file!");
    }

    std::cout << "Choose mode:\n1. Range mode\n2. Interactive mode" << std::endl;
    int mode;
    std::cin >> mode;

    if (mode == 1) {
        int32_t a, b;
        std::cout << "Enter range [a, b]: ";
        std::cin >> a >> b;
        for (int32_t i = a; i < b; i++) {
            if (func->isDefined(i)) {
                std::cout << func->operator()(i) << " ";
            }
        }
    }

    delete func;
}



