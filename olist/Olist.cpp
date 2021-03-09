#include "Olist.h"
#include <iostream>


int Node::ccount = 0;
int Node::dcount = 0;


Olist::Olist() : head(nullptr)
{}


Olist::Olist(const Olist& other)
{
	auto  curr = other.head.get();
	while (curr) {
		insert(curr->data);
		curr = curr->next.get();
	}
}


Olist::Olist(Olist&& other) : head(std::move(other.head))
{}

// copy swap does copy and move assignment
Olist& Olist::operator=(Olist other)
{
	swap(*this, other);
	return *this;
}

bool Olist::insert(int e)
{
	// 
	// case 1, empty list
	//
	if (!head) {
		head = std::make_unique<Node>(e);
		return true;
	}

	//
	// case 2, e belongs at front of list
	//
	if (e < head->data) {
		auto tmp = std::make_unique<Node>(e);
		tmp->next = std::move(head);
		head = std::move(tmp);
		return true;
	}

	//
	//  walk the list until find Node where next Node is >= e 
	//  or reach the end of list
	//
	auto cur = head.get();
	while (cur && cur->next && cur->next->data < e) {
		cur = cur->next.get();
	}

	// end of list case
	if (cur->next == nullptr) {
		cur->next = std::make_unique<Node>(e);
		return true;
	}

	// duplicate element case 
	if (cur->next->data == e) {
		return false;
	}


	// insert mid list case
	auto tmp = std::make_unique<Node>(e);
	tmp->next = std::move(cur->next);
	cur->next = std::move(tmp);
	return true;

	return false; // shouldn't get here
}

bool Olist::remove(int e)
{

	// e is first Node case
	if (head->data == e)
	{
		head = std::move(head->next);
		return true;
	}

	// walk to e
	auto cur = head.get();
	while (cur && cur->next && cur->next->data < e) {
		cur = cur->next.get();
	}

	if (cur && cur->next && cur->next->data == e) {
		cur->next = std::move(cur->next->next);
		return true;
	}

	return false;
}

void Olist::clear()
{
	head = nullptr;
}

bool Olist::isEmpty()
{
	return head == nullptr;
}

int Olist::size()
{
	int count{ 0 };
	auto cur = head.get();
	while (cur) {
		count += 1;
		cur = cur->next.get();
	}
	return count;
}


// new list has all the elements of both lists
Olist Olist::operator+(const Olist& other) const
{
	// copy construct tmp from other
	Olist tmp(other);

	// insert all the elements of this into tmp, duplicats will be ignored
	auto cur = head.get();
	while (cur) {
		tmp.insert(cur->data);
		cur = cur->next.get();
	}

	return tmp;
}


// new list has all the elemens of this with all elements in other removed
Olist Olist::operator-(const Olist& other) const
{
	Olist tmp(*this);

	// remove all the elements in other from tmp
	auto cur = other.head.get();
	while (cur) {
		tmp.remove(cur->data);
		cur = cur->next.get();
	}

	return tmp;
}


// new list is only elements that are in both this and other
Olist Olist::operator/(const Olist& other) const
{
	Olist tmp;

	auto curThis = head.get();
	auto curOther = other.head.get();

	while (curThis && curOther) {
		if (curThis->data == curOther->data) {
			tmp.insert(curThis->data);
			curThis = curThis->next.get();
			curOther = curOther->next.get();
		}
		else if (curThis->data < curOther->data) {
			curThis = curThis->next.get();
		}
		else {
			curOther = curOther->next.get();
		}
	}

	return tmp;
}

void Olist::displayNodePointer() const
{

	auto cur = head.get();
	while (cur) {
		std::cout << cur << ", ";
		cur = cur->next.get();
	}
	std::cout << "\n";
}

void  swap(Olist& lhs, Olist& rhs)
{
	using std::swap;          // enable ADL
	swap(lhs.head, rhs.head); // let compiler pick best overload to use
}


std::ostream& operator<<(std::ostream& os, const Olist& rhs)
{
	os << "{";
	auto cur = rhs.head.get();

	if (cur) {
		os << cur->data;
		cur = cur->next.get();
	}

	while (cur) {
		os << ", " << cur->data;
		cur = cur->next.get();
	}
	os << "}";
	return os;
}
