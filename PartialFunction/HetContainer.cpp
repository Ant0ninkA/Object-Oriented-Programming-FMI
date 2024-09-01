#include <iostream>
#include "HetContainer.h"

HetContainer::HetContainer()
{
    _capacity = 8;
    _data = new PartialFunc * [_capacity] {nullptr};
    _size = 0;
}


HetContainer::HetContainer(const HetContainer& other) {
    copyFrom(other);
}

HetContainer& HetContainer::operator=(const HetContainer& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

void HetContainer::copyFrom(const HetContainer& other) {
	_data = new PartialFunc * [other._capacity];

	for (size_t i = 0; i < other._size; ++i) {
		_data[i] = other._data[i]->clone();
	}
    _size = other._size;
    _capacity = other._capacity;
}

HetContainer::HetContainer(HetContainer&& other)  noexcept{
    moveFrom(std::move(other));
}

HetContainer& HetContainer::operator=(HetContainer&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

void HetContainer::moveFrom(HetContainer&& other) {
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;

    other._data = nullptr;
    other._size = other._capacity = 0;
}

HetContainer::~HetContainer() {
    free();
}

void HetContainer::free() {
    for (size_t i = 0; i < _size; ++i) {
        delete _data[i];
    }
    delete[] _data;
    _data = nullptr;
    _size = _capacity = 0;
}


void HetContainer::addFunc(PartialFunc* func) {
    if (_size == _capacity)
        resize(_capacity * 2);
    _data[_size++] = func; 
    func = nullptr;
}

void HetContainer::addFunc(const PartialFunc& func)
{
    PartialFunc* cloned = func.clone();
    addFunc(cloned);
}

void HetContainer::resize(size_t newCap) {
    PartialFunc** newData = new PartialFunc * [newCap];
    for (int i = 0; i < _size; i++)
        newData[i] = _data[i];
    delete[] _data;
    _data = newData;
    _capacity = newCap;
}

const PartialFunc* HetContainer::operator[](unsigned idx) const {
    return _data[idx];
}

size_t HetContainer::getSize() const {
    return _size;
}
