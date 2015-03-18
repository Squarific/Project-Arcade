#include "DesignByContract.h"

bool returnTrue() {
	return false;
}

int main() {
	REQUIRE(returnTrue(), "Woop");
	return 0;
}
