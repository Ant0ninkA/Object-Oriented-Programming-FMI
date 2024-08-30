#pragma once
#include <iostream>
#include <cmath>
#include <fstream>


class MultiSet {
	unsigned _n = 0;
	unsigned _k = 1;
	uint8_t* buckets = nullptr;
	unsigned bucketsCount = 0;
	unsigned elementsInBucket = sizeof(uint8_t) * 8;
	unsigned maxOccurance = 1;
	uint8_t mask = 1;

	void free();
	void copyFrom(const MultiSet& other);
	unsigned getBucketIndex(unsigned num) const;
	unsigned getLastBitIndex(unsigned num) const;
	void printNumKTimes(unsigned num, unsigned k) const;
	void addNumKTimes(unsigned num, int k);
public:

	MultiSet(unsigned n, unsigned k);
	MultiSet(const MultiSet& other);
	MultiSet& operator=(const MultiSet& other);
	~MultiSet();

	unsigned getCount(unsigned num) const;
	void add(unsigned num);
	void printAllNumsInSet() const;
	void printNumsInMemory();
	void serialize(std::ofstream& ofs) const;
	void deserialize(std::ifstream& ifs);

	friend MultiSet Intersection(const MultiSet& lhs, const MultiSet& rhs);
	friend MultiSet Difference(const MultiSet& lhs, const MultiSet& rhs);
	friend MultiSet Addition(const MultiSet& set);
};

void toBinary(uint8_t& bucket);
unsigned getMin(unsigned a, unsigned b);
