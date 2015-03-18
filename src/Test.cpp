#include "DesignByContract.h"

bool returnTrue() {
	return true;
}

int main() {
	REQUIRE(returnTrue(), "Woop");
	return 0;
}