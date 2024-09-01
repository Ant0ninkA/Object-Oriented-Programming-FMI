#pragma once
#include <iostream>

class NVector
{
private:
	int32_t* data;
	size_t size;

	void copyFrom(const NVector& other);
	void free();

public:
	NVector(size_t size);
	NVector(const int32_t* newData, size_t n);

	NVector(const NVector& other);
	NVector& operator=(const NVector& other);
	~NVector();


	NVector& operator+=(const NVector& other);
	NVector& operator-=(const NVector& other);


	NVector& operator*=(size_t scalar);

	int32_t& operator[](size_t); //get set
	const int32_t operator[](size_t) const; // get


	size_t operator~() const;// size;

	friend std::ostream& operator<<(std::ostream& os, const NVector& v);
	friend std::istream& operator>>(std::istream&, NVector& v);
};

