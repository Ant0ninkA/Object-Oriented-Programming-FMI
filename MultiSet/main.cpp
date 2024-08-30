#pragma once
#include <iostream>
#include "зад1.h"


int main() {
	MultiSet mySet1(4, 3);
	mySet1.add(0);
	mySet1.add(0);
	mySet1.add(4);
	mySet1.add(1);
	mySet1.add(1);
	mySet1.add(1);
	mySet1.add(2);
	mySet1.add(2);
	mySet1.add(2);
	mySet1.add(3);
	mySet1.add(3);
	mySet1.add(3);
	mySet1.printAllNumsInSet();
	mySet1.printNumsInMemory();

	std::ofstream ofs("test1.dat", std::ios::binary);
	mySet1.serialize(ofs);
	ofs.close();

	MultiSet mySet2(2, 3);
	std::ifstream ifs("test1.dat", std::ios::binary);
	mySet2.deserialize(ifs);
	ifs.close();
	mySet2.printAllNumsInSet();
	mySet2.printNumsInMemory();


	MultiSet mySet3(4, 5);
	mySet3.add(0);
	mySet3.add(2);
	mySet3.add(2);
	mySet3.add(2);
	mySet3.add(3);
	mySet3.add(3);
	mySet3.add(4);
	mySet3.printAllNumsInSet();

	MultiSet mySet4 = Intersection(mySet1, mySet3);
	mySet4.printAllNumsInSet();
	mySet4 = Difference(mySet1, mySet3);
	mySet4.printAllNumsInSet();
	mySet4 = Addition(mySet3);
	mySet4.printAllNumsInSet();

};

