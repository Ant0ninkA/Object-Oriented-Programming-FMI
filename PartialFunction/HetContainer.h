#pragma once
#include "PartialFunc.h"

class HetContainer {
private:
	PartialFunc** _data = nullptr;
	size_t _size = 0;
	size_t _capacity = 0;
	void resize(size_t newCap);
	void free();
	void copyFrom(const HetContainer& other);
	void moveFrom(HetContainer &&other);
public:
	HetContainer();
	~HetContainer();
	HetContainer(const HetContainer& other);
	HetContainer(HetContainer&& other) noexcept;
	HetContainer& operator=(const HetContainer& other);
	HetContainer& operator=(HetContainer&& other) noexcept;
	void addFunc(PartialFunc* func);
	void addFunc(const PartialFunc& func);
	const PartialFunc* operator[](unsigned idx) const;
	size_t getSize() const;


};
