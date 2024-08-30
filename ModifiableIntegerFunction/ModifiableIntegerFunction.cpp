#include "зад2.h"

//задачата е обсъждана с Димитър Радев, 2ра група

ModifiableIntegerFunction::ModifiableIntegerFunction(short(*func)(short)) {
	data = new short[MAX_ELEMENTS];
	excludedPoints = new bool[MAX_ELEMENTS] {0};

	for (int i = 0; i < MAX_ELEMENTS; i++) {
		short y = func(i + SHRT_MIN);
		data[i] = func(i + SHRT_MIN);
	}
}

void ModifiableIntegerFunction::copyFrom(const ModifiableIntegerFunction& other) {
	data = new short[MAX_ELEMENTS];
	excludedPoints = new bool[MAX_ELEMENTS] {0};

	for (int i = 0; i < MAX_ELEMENTS; i++)
	{
		data[i] = other.data[i];
		excludedPoints[i] = other.excludedPoints[i];
	}
}

void ModifiableIntegerFunction::free() {
	delete[] data;
	data = nullptr;

	delete[] excludedPoints;
	excludedPoints = nullptr;
}

ModifiableIntegerFunction::ModifiableIntegerFunction(const ModifiableIntegerFunction& other) {
	copyFrom(other);
}
ModifiableIntegerFunction& ModifiableIntegerFunction::operator=(const ModifiableIntegerFunction& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}
ModifiableIntegerFunction::~ModifiableIntegerFunction() {
	free();
}

void ModifiableIntegerFunction::setSpecificResult(short x, short y) {
	data[x - SHRT_MIN] = y;
}

void ModifiableIntegerFunction::addExcludedPoint(short x) {
	excludedPoints[x - SHRT_MIN] = 1;
}

ModifiableIntegerFunction& ModifiableIntegerFunction::operator+=(const ModifiableIntegerFunction& other) {
	for (int i = 0; i < MAX_ELEMENTS; i++) {
		if (excludedPoints[i] || other.excludedPoints[i]) {
			excludedPoints[i] = 1;
			continue;
		}
		data[i] += other.data[i];
	}
       return *this;
}

ModifiableIntegerFunction operator+(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs) {
	ModifiableIntegerFunction result(lhs); 
	result += rhs;

	return result;
}

ModifiableIntegerFunction& ModifiableIntegerFunction::operator-=(const ModifiableIntegerFunction& other) {
	for (int i = 0; i < MAX_ELEMENTS; i++) {
		if (excludedPoints[i] || other.excludedPoints[i]) {
			excludedPoints[i] = 1;
			continue;
		}
		data[i] -= other.data[i];
	}

	return *this;
}

ModifiableIntegerFunction operator-(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs) {
	ModifiableIntegerFunction result(lhs);
	result -= rhs;

	return result;
}

ModifiableIntegerFunction operator*(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs){
	ModifiableIntegerFunction res = rhs;

	for (int i = 0; i < MAX_ELEMENTS; i++) {
		if (lhs.excludedPoints[res.data[i] - SHRT_MIN]) {
			std::cout << "The function is not defined for: " << res.data[i] - SHRT_MIN << std::endl;
			res.excludedPoints[i] = 1;
			continue;
		}
		res.data[i] = lhs.data[res.data[i] - SHRT_MIN];
	}

	return res;
}

bool operator||(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs){
	return lhs.areParallel(rhs);
}


ModifiableIntegerFunction& ModifiableIntegerFunction::operator^(unsigned k) {
	for (unsigned i = 1; i < k; i++) {
		*this = (*this) * (*this);
	}

	return *this;
}

bool operator<(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs) {
	for (int i = 0; i < MAX_ELEMENTS; i++) {
		if (lhs.excludedPoints[i]) {
			continue;
		}
		else if(rhs.excludedPoints[i]  || lhs.data[i] >= rhs.data[i]) {
			return false;
		}
	}
	return true;
}

bool operator<=(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs) {
	for (int i = 0; i < MAX_ELEMENTS; i++) {
		if (lhs.excludedPoints[i]) {
			continue;
		}
		else if (rhs.excludedPoints[i] || lhs.data[i] > rhs.data[i]) {
			return false;
		}
	}
	return true;
}

bool operator>(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs) {
	return !(lhs <= rhs);
}

bool operator>=(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs) {
	return !(lhs < rhs);
}

bool operator==(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs) {
	return (lhs >= rhs && lhs <= rhs);
}

bool operator!=(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs) {
	return !(lhs == rhs);
}

bool ModifiableIntegerFunction::areParallel(const ModifiableIntegerFunction& other) const {
	ModifiableIntegerFunction diff = *this - other;
	short difference = diff.data[0];

	for (int i = 1; i < MAX_ELEMENTS; i++) {
		if (excludedPoints[i] || other.excludedPoints) {
			continue;
		}
		if (diff.data[i] != difference) {
			return false;
		}
	}

	return true;
}

ModifiableIntegerFunction operator~(const ModifiableIntegerFunction& func) {
	ModifiableIntegerFunction reverse = func.getReverse();
	return reverse;
}


ModifiableIntegerFunction ModifiableIntegerFunction::getReverse() const {
	if (isBijective()) {
	ModifiableIntegerFunction res(*this);
	for (int i = 0; i < MAX_ELEMENTS; i++) {
		if (excludedPoints[i]) {
			continue;
		}
		res.setSpecificResult(data[i], i + SHRT_MIN);
	}
	return res;
	}
	else {
		std::cout << "This function does not have reverse one";
		return *this;
	}
}


void ModifiableIntegerFunction::drawPoints(short x1, short y1, short x2, short y2) const
{
	if (x2 - x1 != 20 || y2 - y1 != 20)
	{
		std::cout << "(x2 - x1) and (y2 - y1) should be equal to 20 in every case";
		return;
	}

	for (int i = x1; i <= x2; i++)
	{
		if (data[i - SHRT_MIN] >= y1 && data[i - SHRT_MIN] <= y2)
			std::cout << "(" << i << ", " << data[i - SHRT_MIN] << ")" << std::endl;
	}
}

void ModifiableIntegerFunction::serialize(std::ofstream& ofs) const
{
	ofs.write((const char*)data, MAX_ELEMENTS * sizeof(short));
	ofs.write((const char*)excludedPoints, MAX_ELEMENTS);
}
void ModifiableIntegerFunction::deserialize(std::ifstream& ifs)
{
	data = new short[MAX_ELEMENTS];
	excludedPoints = new bool[MAX_ELEMENTS] {0};

	ifs.read((char*)data, MAX_ELEMENTS * sizeof(short));
	ifs.read((char*)excludedPoints, MAX_ELEMENTS);
}

unsigned countOccurances(short point, const ModifiableIntegerFunction& func)
{
	unsigned count = 0;
	for (int i = 0; i < MAX_ELEMENTS; i++)
	{
		if (!func.excludedPoints[i])
		{
			if (point == func.data[i])
				count++;
		}
	}

	return count;
}

bool ModifiableIntegerFunction::isInjective() const
{
	for (int i = 0; i < MAX_ELEMENTS; i++)
	{
		if (countOccurances(i, *this) > 1)
			return false;
	}
	return true;
}


bool ModifiableIntegerFunction::isSurjective() const
{
	for (int i = 0; i < MAX_ELEMENTS; i++)
	{
		if (countOccurances(i + SHRT_MIN, *this) == 0)
			return false;
	}

	return true;
}

bool ModifiableIntegerFunction::isBijective() const {
	return (isSurjective() && isInjective());
}


