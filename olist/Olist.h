#pragma once
#include <iostream>
#include <memory>

// forward declaration
//struct Node;

struct Node {
	Node() : next(nullptr) { ccount++; }
	Node(int d) : next(nullptr), data(d) { ccount++; }
	~Node() { dcount++; }


	int data;
	std::unique_ptr<Node> next;


	static void displayNodeCount() {
		std::cout << ccount << " created\n"
			<< dcount << " destroyed\n";
	}
	static int ccount;
	static int dcount;
};

class Olist
{
public:
	Olist();
	~Olist() = default;

	// copy
	Olist(const Olist& other);
	Olist(Olist&& other);
	Olist& operator=(Olist other);

	// move 

	bool insert(int e);
	bool remove(int e);
	void clear();
	bool isEmpty();
	int size();

	Olist operator+(const Olist& other) const; // add two lists
	Olist operator-(const Olist& other) const; // difference of two list
	Olist operator/(const Olist& other) const; // on both lists (intersection)

	friend std::ostream& operator<<(std::ostream& os, const Olist& rhs);
	
	void displayNodePointer() const;
	
	friend void swap(Olist& lhs, Olist& rhs);

private:
	std::unique_ptr<Node> head;
};

