#pragma once
#include <iostream>
#include <fstream>

constexpr int MAX_ELEMENTS = -SHRT_MIN + SHRT_MAX + 1;

class ModifiableIntegerFunction {
private:
	short* data = nullptr;
	bool* excludedPoints = nullptr;
	void free();
	void copyFrom(const ModifiableIntegerFunction& other);
	bool areParallel(const ModifiableIntegerFunction& other) const;
	friend unsigned countOccurances(short point, const ModifiableIntegerFunction& func);

public:
	ModifiableIntegerFunction(short(*func)(short));
	ModifiableIntegerFunction(const ModifiableIntegerFunction& other);
	ModifiableIntegerFunction& operator=(const ModifiableIntegerFunction& other);
	~ModifiableIntegerFunction();

	void setSpecificResult(short x, short y);
	void addExcludedPoint(short x);
	ModifiableIntegerFunction& operator+=(const ModifiableIntegerFunction& other);
	ModifiableIntegerFunction& operator-=(const ModifiableIntegerFunction& other);
	friend ModifiableIntegerFunction operator*(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);
	friend ModifiableIntegerFunction operator~(const ModifiableIntegerFunction& func);
	friend bool operator||(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);
    friend bool operator<(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);
    friend bool operator<=(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);
    friend bool operator>(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);
    friend bool operator>=(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);
	friend bool operator==(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);
	friend bool operator!=(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);
    ModifiableIntegerFunction& operator^(unsigned k);
	ModifiableIntegerFunction getReverse() const;
	void drawPoints(short fstX, short fstY, short sndX, short sndY) const;
	void serialize(std::ofstream& ofs) const;
	void deserialize(std::ifstream& ifs);
	bool isInjective() const;
	bool isSurjective() const;
	bool isBijective() const;

};
ModifiableIntegerFunction operator+(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);
ModifiableIntegerFunction operator-(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);





