#include <iostream>
#include "зад1.h"

//домашното е обсъждано със Златина Лилова, 2ра група

MultiSet::MultiSet(unsigned n, unsigned k) {
	bucketsCount = (n + 1) * k / elementsInBucket + 1;
	buckets = new uint8_t[bucketsCount]{ 0 };
	maxOccurance = pow(2, k) - 1;
	mask = (mask << k) - 1;
	_n = n;
	_k = k;
}

void MultiSet::free()
{
	delete[] buckets;
	bucketsCount = 0;
	buckets = nullptr;
	_n = 0;
	_k = mask = maxOccurance = 1;
}

void MultiSet::copyFrom(const MultiSet& other)
{
	buckets = new uint8_t[other.bucketsCount];
	for (size_t i = 0; i < other.bucketsCount; i++)
		buckets[i] = other.buckets[i];
	bucketsCount = other.bucketsCount;
	_n = other._n;
	_k = other._k;
	mask = other.mask;
	maxOccurance = other.maxOccurance;
}

MultiSet::MultiSet(const MultiSet& other) {
	copyFrom(other);
}

MultiSet& MultiSet::operator=(const MultiSet& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

MultiSet::~MultiSet() {
	free();
}

unsigned MultiSet::getBucketIndex(unsigned num) const {
	return (num * _k) / elementsInBucket;
};

unsigned MultiSet::getLastBitIndex(unsigned num) const {
	unsigned bucket = getBucketIndex(num);
	unsigned idx = ((num + 1) * _k - 1);
	if ((int)((idx % 8) - _k) < 0)
		return idx; 
	else
		return idx % elementsInBucket;
}

unsigned MultiSet::getCount(unsigned num) const {
	if (num < 0 || num > _n) {
		std::cout << "This number is out of range!" << std::endl;
		return 0;
	}

	unsigned bit = getLastBitIndex(num);
	unsigned bucket = getBucketIndex(num);

	if (bit < elementsInBucket) {
		unsigned help = elementsInBucket - bit - 1;
		return (buckets[bucket] & (mask << help)) >> help;
	}
	else {
		bit %= elementsInBucket;
		unsigned bitsInNextBucket = bit + 1;

		unsigned shift = elementsInBucket - bitsInNextBucket;
		uint8_t mask1 = mask << shift;
		uint8_t mask2 = (1 << (_k - bitsInNextBucket)) - 1;

		return ((buckets[bucket] & mask2) << bitsInNextBucket) | ((buckets[bucket + 1] & mask1) >> shift);
	}
}

void MultiSet::add(unsigned num) {
	if (num < 0 || num > _n) {
		std::cout << "This number is out of range!" << std::endl;
		return;
	}
	unsigned countOfNum = getCount(num);
	if (countOfNum == maxOccurance) {
		std::cout << "No more space for this num" << std::endl;
		return;
	}
	countOfNum++;

	unsigned bit = getLastBitIndex(num);
	unsigned bucket = getBucketIndex(num);

	if (bit < elementsInBucket)
	{
		unsigned shift = elementsInBucket - bit - 1;
		countOfNum <<= shift;
		uint8_t clear_mask = ~(mask << shift);
		buckets[bucket] = (buckets[bucket] & clear_mask) | countOfNum;
	}
	else
	{
		bit %= elementsInBucket;
		unsigned bitsInNextBucket = bit + 1;
		unsigned shift = elementsInBucket - bitsInNextBucket;

		uint8_t mask1 = mask << shift;
		uint8_t mask2 = (1 << (_k - bitsInNextBucket)) - 1;

		unsigned nextBucketBits = (countOfNum << shift) & mask1;
		unsigned prevBucketBits = (countOfNum >> bitsInNextBucket) & mask2;

		buckets[bucket] = (buckets[bucket] & ~mask2) | prevBucketBits;
		buckets[bucket + 1] = (buckets[bucket + 1] &= ~mask1) | nextBucketBits;
	}

}

void MultiSet::printAllNumsInSet() const {
	std::cout << "{ ";
	unsigned count;
	for (unsigned i = 0; i <= _n; i++) {
		count = getCount(i);
		printNumKTimes(i, count);
	}
	std::cout << "}" << std::endl;
}
void MultiSet::printNumsInMemory() {
	for (unsigned i = 0; i < bucketsCount; i++) {
		toBinary(buckets[i]);
		std::cout << " ";
	}
	std::cout << std::endl;
}

void MultiSet::serialize(std::ofstream& ofs) const {
	ofs.write((const char*)&_n, sizeof(unsigned));
	ofs.write((const char*)&_k, sizeof(unsigned));
	ofs.write((const char*)buckets, (sizeof(buckets)));
}

void MultiSet::deserialize(std::ifstream& ifs) {
	ifs.read((char*)&_n, sizeof(unsigned));
	ifs.read((char*)&_k, sizeof(unsigned));

	maxOccurance = pow(2, _k) - 1;
	mask = (1 << _k) - 1;
	bucketsCount = (_n + 1) * _k / elementsInBucket + 1;
	delete[] buckets;
	buckets = new uint8_t[bucketsCount]{ 0 };

	ifs.read((char*)buckets, (sizeof(buckets)));
}

MultiSet Intersection(const MultiSet& lhs, const MultiSet& rhs) {
	unsigned minN = getMin(lhs._n, rhs._n);
	unsigned minK = getMin(lhs._k, rhs._k);

	MultiSet res(minN, minK);

	unsigned occuranceInLhs;
	unsigned occuranceInRhs;
	unsigned intersection;
	for (unsigned i = 0; i <= minN; i++) {
		occuranceInLhs = lhs.getCount(i);
		occuranceInRhs = rhs.getCount(i);

		intersection = getMin(occuranceInLhs, occuranceInRhs);

		res.addNumKTimes(i, intersection);
	}

	return res;
}

MultiSet Difference(const MultiSet& lhs, const MultiSet& rhs) {
	unsigned minN = getMin(lhs._n, rhs._n);

	MultiSet res(lhs._n, lhs._k);

	unsigned occuranceInLhs;
	unsigned occuranceInRhs;
	int diff;
	for (unsigned i = 0; i <= minN; i++) {
		occuranceInLhs = lhs.getCount(i);
		occuranceInRhs = rhs.getCount(i);

		diff = occuranceInLhs - occuranceInRhs;

		res.addNumKTimes(i, diff);
	}

	for (unsigned i = minN + 1; i <= lhs._n; i++) {
		res.addNumKTimes(i, lhs.getCount(i));
	}

	return res;
}

MultiSet Addition(const MultiSet& set) {
	MultiSet res(set._n, set._k);

	for (unsigned i = 0; i < set.bucketsCount; i++) {
		res.buckets[i] = set.buckets[i] ^ 255;
	}

	return res;
}

void MultiSet::printNumKTimes(unsigned num, unsigned count) const {
	for (unsigned i = 0; i < count; i++) {
		std::cout << num << " ";
	}
}
void MultiSet::addNumKTimes(unsigned num, int k) {
	for (int i = 0; i < k; i++)
		this->add(num);
}

void toBinary(uint8_t& bucket) {
	int counter = 7;
	while (counter >= 0) {
		std::cout << ((bucket >> counter) & 1);
		counter--;
	}
}
unsigned getMin(unsigned a, unsigned b) {
	if (a <= b)
		return a;
	else
		return b;
}