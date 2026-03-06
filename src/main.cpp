#include <iostream>
#include "Deck.h"
#include "../tests/include/TesterCLI.h"


int main() {

	Deck deck;

	TesterCLI tester(deck.getDeck());

	tester.runTest();

	return 0;
}