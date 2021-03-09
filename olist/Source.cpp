// header comment
// auth: David Burchill
// this is my work


#include <iostream>
#include "Olist.h"




int main() {
	{
		Olist l;
		std::cout << l << "\n";

		for (int i = 0; i < 10; ++i) {
			l.insert(i);
			std::cout << l.size() << ": " << l << "\n";
		}

		auto l2(l);
		l2.insert(73);
		l2.insert(73);
		l2.remove(3);
		l2.remove(3);

		std::cout << "L2: " << l2 << "\n";

		swap(l, l2);
		std::cout << "L: " << l << "\n";
		std::cout << "L2: " << l2 << "\n";
		
	}
	Node::displayNodeCount();

	{
		Olist l1;
		Olist l2;
		 
		for (int i = 0; i < 10; ++i) {
			l1.insert(2*i + 1);
			l2.insert(i);
		}
		std::cout << "l1: " << l1 << "\n"; 
		std::cout << "l2: " << l2 << "\n"; 
		std::cout << "l1 + l2: " << l1 + l2 << "\n";
		std::cout << "l1 - l2: " << l1 - l2 << "\n";
		std::cout << "l1 / l2: " << l1 / l2 << "\n";
	}

	Node::displayNodeCount();
}