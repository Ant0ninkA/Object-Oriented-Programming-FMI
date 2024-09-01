#include "NVector.h"

NVector::NVector(size_t n) : size(n)
{
	data = new int32_t[n];

	for (int i = 0; i < n; i++)
		data[i] = 0;
}

NVector::NVector(const int32_t* newData, size_t n) : size(n) {
	data = new int32_t[n]{ 0 };

	for (size_t i = 0; i < n; i++) {
		data[i] = newData[i];
	}
}


NVector::NVector(const NVector& other)
{
	copyFrom(other);
}

NVector& NVector::operator=(const NVector& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
NVector::~NVector()
{
	free();
}

void NVector::copyFrom(const NVector& other)
{
	size = other.size;
	data = new int[size];

	for (int i = 0; i < size; i++)
		data[i] = other.data[i];
}
void NVector::free()
{
	delete[] data;
	size = 0;
}

NVector& NVector::operator+=(const NVector& other)
{
	if (size != other.size)
		throw "The vectors should have the same size!";

	for (int i = 0; i < size; i++)
		data[i] += other.data[i];

	return *this;
}

NVector& NVector::operator-=(const NVector& other)
{
	if (size != other.size)
		throw "The vectors should have the same size!";

	for (int i = 0; i < size; i++)
		data[i] -= other.data[i];

	return *this;
}

int32_t& NVector::operator[](size_t index)
{
	if (index >= size)
		throw "Invalid index";

	return data[index];
}

const int32_t NVector::operator[](size_t index) const
{
	if (index >= size)
		throw "Invalid index";

	return data[index];
}

size_t NVector::operator~() const
{
	return size;
}

std::ostream& operator<<(std::ostream& os, const NVector& v)
{
	os << "[ ";
	for (int i = 0; i < v.size; i++)
		os << v[i] << " ";
	os << " ]";

	return os;
}

std::istream& operator>>(std::istream& is, NVector& v)
{
	for (int i = 0; i < v.size; i++)
		is >> v[i];

	return is;
}


NVector& NVector::operator*=(size_t scalar)
{
	for (int i = 0; i < size; i++)
		data[i] *= scalar;

	return *this;
}

