#include "FuncFactory.h"
#include "FuncByCriteria.hpp"
#include "T0Func.h"
#include "T1Func.h"
#include "T2Func.h"
#include "MinFunc.h"
#include "MaxFunc.h"
#include "NVector.h"
#include <iostream>
#pragma warning(disable:4996)


PartialFunc* funcFactory(std::ifstream& is) {
	uint16_t N;
	uint16_t T;

	is.read((char*)&N, sizeof(N));
	is.read((char*)&T, sizeof(T));


	if (N > 32) {
		throw std::invalid_argument("N is out of range");
	}

	switch (T)
	{
	case 0:
	{
		int32_t* data = new int32_t[2 * N];
		is.read((char*)data, sizeof(int32_t) * 2 * N);
		NVector values(data, 2 * N);
		T0Func obj(values, N);
		delete[] data;
		return new FuncByCriteria<T0Func>(obj);
	}
	case 1:
	{
		int32_t* data = new int32_t[N];
		is.read((char*)data, sizeof(int32_t) * N);
		NVector values(data, N);
		T1Func obj(values, N);
		delete[] data;
		return new FuncByCriteria<T1Func>(obj);
	}
	case 2:
	{
		int32_t* data = new int32_t[N];
		is.read((char*)data, sizeof(int32_t) * N);
		NVector values(data, N);
		T2Func obj(values, N);
		delete[] data;
		return new FuncByCriteria<T2Func>(obj);
	}
	case 3:
	{
		HetContainer container;
		for (unsigned i = 0; i < N; i++) {
			char* filename = readFromBinaryFile(is);

			std::ifstream file(filename, std::ios::binary);
			if (!file.is_open()) {
				throw std::invalid_argument("This file cannot be opened");
			}

			container.addFunc(funcFactory(file));
		}

		return new MaxFunc(container);
	}
	case 4:
	{
		HetContainer container;
		for (unsigned i = 0; i < N; i++) {
			char* filename = readFromBinaryFile(is);

			std::ifstream file(filename, std::ios::binary);
			if (!file.is_open()) {
				throw std::invalid_argument("This file cannot be opened");
			}

			container.addFunc(funcFactory(file));
		}

		return new MinFunc(container);
	}
	default:
		throw std::invalid_argument("T must be in [0..4]");
	}

}

char* readFromBinaryFile(std::ifstream& is) {
	const size_t maxSize = 1024;
	char* buffer = new char[maxSize];
	size_t index = 0;
	char ch;

	while (is.read(&ch, sizeof(ch))) {
		buffer[index++] = ch;
		if (ch == '\0') {
			break;
		}
	}

	char* result = new char[index];
	std::strcpy(result, buffer);

	delete[] buffer;
	return result;
}