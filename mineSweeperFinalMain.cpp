

#include"mineSweeperFinal.h"


using namespace std;

int main() {
	/*
		1. create the objects 'original' and 'userBorad'
		2. calls the 'printMenu' function from the object 'original'
		3. calls 'printSquare' function from the object 'userBoard'
		4. define a variable 'v' equals 1
		4. the while loop will end once the value of the variable 'v' is not 1 /the value of the variable 'v' is updeted every time the function 'move' is called/
	*/
	Square original;
	Square userBoard;
	original.printMenu(userBoard);
	userBoard.printSquare(original);
	int v = 1;
	while (v == 1) {
		v = userBoard.move(original);
	}
	return 0;
}