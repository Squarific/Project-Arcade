#include <string>
#include <iostream>
#include "DesignByContract.h"
#include "Move.h"

Move::Move() {
	_initcheck = this;
}

Move::Move(int d, std::string n, bool a) {
	_initcheck = this;
	direction = d;
	name = n;
	isAttack = a;
}

bool Move::properlyInitialized() {
	return _initcheck == this;
}

void Move::set_direction(int d) {
	REQUIRE(this->properlyInitialized(), "ERROR: Move was not properly initialized.");
	
	direction = d;

	ENSURE(this->get_direction() == d, "ERROR: set_direction() did not work correctly.");
}

int Move::get_direction() {
	REQUIRE(this->properlyInitialized(), "ERROR: Move was not properly initialized.");
	
	return direction;
}

void Move::set_name(std::string str) {
	REQUIRE(this->properlyInitialized(), "ERROR: Move was not properly initialized.");
	
	name = str;

	ENSURE(this->get_name() == str, "ERROR: set_name() did not work correctly.");
}

std::string Move::get_name() {
	REQUIRE(this->properlyInitialized(), "ERROR: Move was not properly initialized.");
	
	return name;
}