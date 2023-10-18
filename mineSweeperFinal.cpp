
#include"mineSweeperFinal.h"

using namespace std;


// constructor
Square::Square() {
	/*
		1. set the attributes 'mines', 'side', 'countedMines', and 'fieldCounter' to be 0
		2. set the attributes 'table' and 'isVisited' to null pointer
	*/
	mines = 0;
	side = 0;
	countedMines = 0;
	fieldCounter = 0;
	table = nullptr;
	isVisited = nullptr;
}



//destructor
Square::~Square() {
	/*
		1. deletes the attributes 'table' and 'isVisited'
		2. set the attributes 'side' and 'mines' to be 0
		3. set the attributes 'table' and 'isVisited' to null pointer
	*/
	for (int i = 0; i < side; i++) {
		delete[] table[i];
	}
	delete[] table;
	for (int i = 0; i < side; i++) {
		delete[] isVisited[i];
	}
	delete[] isVisited;
	side = 0;
	mines = 0;
	table = nullptr;
	isVisited = nullptr;
}

//function to create the table and assign mines
void Square::createTable() {
	/*
		1. allocate memory dynamically for table attribute.
		2. assigns char '0' to every 0.
	*/
	table = new char* [side];
	for (int i = 0; i < side; i++) {
		table[i] = new char[side];
	}
	for (int i = 0; i < side; i++) {
		for (int j = 0; j < side; j++) {
			table[i][j] = '0';
		}
	}
	/*
		3. assigns  9's to the table /'mines' is the number of mines that are axpected to be in the table/, to assign 9's to the table:
			1. for loop will launch 'mines' times,
			2. new variable rrow will gat a value through rand function /'%side' - rand function may give big number so we take its remainder which remains
			   after deviding by 'side' which gives us a number less that 'side'/,
			3.new variable rcol will get a value through rand function,
			4. an entry matches the coordinate (rrow, rcol) is assigned char '9' which indicates there is a mine in the entry.
	*/
	srand((unsigned)time(NULL));
	for (int i = 0; i < mines; i++) {
		int rrow = rand() % side;
		int rcol = rand() % side;
		table[rrow][rcol] = '9';
	}
	/*
		1. an attribute mines is expected to be set as 0,
		2. count number of assigned mines in the table /a value of rrow and rcol might be overlapped, thus an attribute 'mines' needs to be counted/
	*/
	mines = 0;
	for (int i = 0; i < side; i++) {
		for (int j = 0; j < side; j++) {
			if (table[i][j] == '9') {
				mines++;
			}
		}
	}
}

/*function to print menuand assign 'side' and 'mines' to an original table / in the game we use 2 objects which are 'original' - contains information about where
  mines are and what is a value of every entry, not visible for  palyer, and userBoard - visible by a player, which a player will play with/
*/
void Square::printMenu(Square& userBoard) {
	/*
		1. a menu with 2 options
		   - 1: play a new game
		   - 2: continue the last game
	*/
	cout << "1. New game" << endl << "2.continue last game" << endl;
	/*
		2. inside a while loop
			- exceptio handling: *takes an integer input from user
								 *if it is either not 2 or not 1, it throws '-1'
								 *if an input is valid (1 or 2) it breaks the while loop
								 *it catches the exception, prints error message and clears an input buffer, lastly go to try block again since thw while loop is
								  not broken.
	*/
	int a;
	while (true) {
		try {
			cout << "\n choose from the menu:";
			cin >> a;
			if (a != 2 && a != 1)
				throw - 1;
			break;
		}
		catch (int e) {
			cerr << "invalid input, please an integer between 1 to 2:" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}
	/*
		3. if an input 'a' is 1:
								- clears the screen
								- prints new menu in terms of its difficulty

	*/
	if (a == 1) {
		system("cls");
		cout << "1. Beginner" << endl << "2. Intermediate" << endl << "3. Advanced" << endl;
		cout << "Choose an difficulty level:" << endl;
		/*
			4. inside a while loop:
				- an exception handling:
										* get an input 'c' from the user
										* if it is greater that 3 or less than or equal to 0, throws '-1'
										* if not breaks the while loop
										* catches the exception, write an error message into screen and clears an input buffer, lastly go to try block again
										  since the while loop is not broken.
		*/
		int c;
		while (true) {
			try {
				cin >> c;
				if (c > 3 || c <= 0)
					throw - 1;
				break;
			}
			catch (int e) {
				cerr << "invalid input, please enter a number between 1 to 3:" << endl;
				cin.clear();
				cin.ignore(10000, '\n');
			}
		}
		/*
			5. switch statement: - sets an attributes 'table' and 'mines' of both objects 'original' and 'userBoard' according to its difficulty level and
								 - sets an attributes 'countedMines' and 'fieldCounter' as 0
		*/
		switch (c) {
		case 1: side = 9; mines = 10;
			userBoard.side = 9; userBoard.mines = 10;
			break;
		case 2: side = 12; mines = 20;
			userBoard.side = 12; userBoard.mines = 20;
			break;
		case 3: side = 15; mines = 35;
			userBoard.side = 15; userBoard.mines = 35;
			break;
		default: countedMines = 0;
			fieldCounter = 0;
			userBoard.countedMines = 0;
			userBoard.fieldCounter = 0;
		}
		/*
			6. allocates memory for an attribute 'isVisited' dynamically and assigns 'false' to every entry
			7. calls createTable function for allocating memory for an attribute 'table' and assigns mines to the 'table'
			8. calls assignNeighbours function for assigning numbers to neighbouring entries of a mine with respect to hpw many mines there are
			9. calls creaeUserBoard function for an object 'userBoard' to dynamically allocates memory for attributes 'table' and 'isVisited' and assign values for
			   every entry
		*/
		isVisited = new bool* [side];
		for (int i = 0; i < side; i++) {
			isVisited[i] = new bool[side];
		}
		for (int i = 0; i < side; i++) {
			for (int j = 0; j < side; j++) {
				isVisited[i][j] = false;
			}
		}
		createTable();
		assignNeighbours();
		userBoard.createUserBoard();
	}
	/*
		8. if a player chooses the menu 2 'continue last game'
		   - calls function readOriginalFromFile to allocate memory for attribute 'table' and 'isVisite' and assign values to the entries from a file
		   - calls function readUserBoardFromFile to allocate memory for attribute 'table' and 'isVisite' and assign values to the entries from a file
	*/
	else {
		readOriginalFromFile();
		userBoard.readUserboardFromFile();

	}

}

//function to assign numbers neighbouring squres of a mine; i stand for rows, j stand for columns similarly, r satnds fro subrow, c stands for subcolumn
void Square::assignNeighbours() const {
	/*
		1. for loop for inner square start from 1st row and column ends at the prelast row and column
	   - checks neighbours of an entry if there is a mine, a value of an local variable 'count' is incremented
	*/
	for (int i = 1; i < side - 1; i++) {
		for (int j = 1; j < side - 1; j++) {
			if (table[i][j] != '9') {
				int count = 0;
				if (table[i - 1][j - 1] == '9')
					count++;
				if (table[i - 1][j] == '9')
					count++;
				if (table[i - 1][j + 1] == '9')
					count++;
				if (table[i][j - 1] == '9')
					count++;
				if (table[i][j + 1] == '9')
					count++;
				if (table[i + 1][j - 1] == '9')
					count++;
				if (table[i + 1][j] == '9')
					count++;

				if (table[i + 1][j + 1] == '9')
					count++;
				table[i][j] = (char)(count + '0');
			}
		}
	}
	/*
		2. for loop for 0th row but start from 1st column and ends at prelest column
		 - checks neighbours of an entry if there is a mine, a value of an local variable 'count' is incremented
	*/
	for (int j = 1; j < side - 1; j++) {
		if (table[0][j] != '9') {
			int count = 0;
			if (table[0][j - 1] == '9')
				count++;
			if (table[0][j + 1] == '9')
				count++;
			if (table[1][j - 1] == '9')
				count++;
			if (table[1][j] == '9')
				count++;
			if (table[1][j + 1] == '9')
				count++;
			table[0][j] = (char)(count + '0');
		}
	}
	/*
		3. for loop for the last column but start from 1st row and ends at prelast row
		   - checks neighbours of an entry if there is a mine, a value of an local variable 'count' is incremented
	*/
	for (int i = 1; i < side - 1; i++) {
		if (table[i][side - 1] != '9') {
			int count = 0;
			if (table[i - 1][side - 2] == '9')
				count++;
			if (table[i - 1][side - 1] == '9')
				count++;
			if (table[i][side - 2] == '9')
				count++;
			if (table[i + 1][side - 2] == '9')
				count++;
			if (table[i + 1][side - 1] == '9')
				count++;
			table[i][side - 1] = (char)(count + '0');
		}
	}
	/*
		4. for loop for lst row but start from 1st column and ends at prelast column
		   - checks neighbours of an entry if there is a mine, a value of an local variable 'count' is incremented
	*/
	for (int j = 1; j < side - 1; j++) {
		if (table[side - 1][j] != '9') {
			int count = 0;
			for (int r = side - 2; r <= side - 1; r++) {
				for (int c = j - 1; c <= j + 1; c++) {
					if (table[r][c] == '9')
						count++;
				}
			}
			table[side - 1][j] = (char)(count + '0');
		}
	}
	/*
		5. for loop for first column but start from 1st row and ends at prelast row
		   - checks neighbours of an entry if there is a mine, a value of an local variable 'count' is incremented
	*/
	for (int i = 1; i < side - 1; i++) {
		if (table[i][0] != '9') {
			int count = 0;
			for (int r = i - 1; r <= i + 1; r++) {
				for (int c = 0; c <= 1; c++) {
					if (table[r][c] == '9') {
						count++;
					}
				}
			}
			table[i][0] = (char)(count + '0');
		}
	}
	/*
		6. (0, 0)th entry of the table
		   - checks neighbours of an entry if there is a mine, a value of an local variable 'count' is incremented
	*/
	if (table[0][0] != '9') {
		int count = 0;
		if (table[0][1] == '9') {
			count++;
		}
		if (table[1][1] == '9') {
			count++;
		}
		if (table[1][0] == '9') {
			count++;
		}
		table[0][0] = (char)(count + '0');
	}
	/*
		7. (0, side - 1)th entry of the table
		   - checks neighbours of an entry if there is a mine, a value of an local variable 'count' is incremented
	*/
	if (table[0][side - 1] != '9') {
		int count = 0;
		for (int r = 0; r <= 1; r++) {
			for (int c = side - 2; c <= side - 1; c++) {
				if (table[r][c] == '9')
					count++;
			}
		}
		table[0][side - 1] = (char)(count + '0');
	}
	/*
		8. (side - 1, side - 1)th entry of the table
		   - checks neighbours of an entry if there is a mine, a value of an local variable 'count' is incremented
	*/
	if (table[side - 1][side - 1] != '9') {
		int count = 0;
		if (table[side - 2][side - 1] == '9')
			count++;
		if (table[side - 2][side - 2] == '9')
			count++;
		if (table[side - 1][side - 2] == '9')
			count++;
		table[side - 1][side - 1] = (char)(count + '0');
	}
	/*
		9. (side-1, 0)th entry of the table
		   - checks neighbours of an entry if there is a mine, a value of an local variable 'count' is incremented
	*/
	if (table[side - 1][0] != '9') {
		int count = 0;
		if (table[side - 2][0] == '9')
			count++;
		if (table[side - 2][1] == '9')
			count++;
		if (table[side - 1][1] == '9')
			count++;
		table[side - 1][0] = (char)(count + '0');
	}
}

//a function to print the 'table' to screen
void Square::printSquare(Square& original) {
	/*
		1. determine the value of an attribute 'fieldCounter'. To determine:
					- compares entries of attribute table of 2 objects , 'original' and 'userBoard'
					- if it matches, the value of 'fieldCounter' is incremented
					- it needs to determine if the player wins
	*/
	fieldCounter = 0;
	for (int i = 0; i < side; i++) {
		for (int j = 0; j < side; j++) {
			if (table[i][j] == original.table[i][j]) {
				fieldCounter++;
			}
		}
	}
	/* text colouring stuff, if the player wants to mark an entry as suspected of containing a mine the entry will be a char '*' which is red coloured */
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole, &info);

	SetConsoleTextAttribute(hConsole, 15);
	/* printing the 'userBoard' table */
	cout << endl;
	cout << "   ";
	for (int i = 0; i < side; i++) {
		cout << setw(3) << i + 1 << " ";
	}
	cout << endl;
	cout << "   ";
	for (int i = 0; i < side; i++) {
		cout << "----";
	}
	cout << endl;
	for (int i = 0; i < side; i++) {
		cout << setw(2) << i + 1 << " | ";
		for (int j = 0; j < side; j++) {
			if (table[i][j] == '*') {
				SetConsoleTextAttribute(hConsole, 12);
				cout << table[i][j] << setw(3) << " ";
				SetConsoleTextAttribute(hConsole, 15);
			}
			else {
				cout << table[i][j] << setw(3) << " ";
			}
		}
		cout << endl;
	}
	/* for loop to determine a value of an attribute 'countedMines' so that the player can see how many entries he marked as a mine*/
	countedMines = 0;
	for (int i = 0; i < side; i++) {
		for (int j = 0; j < side; j++) {
			if (table[i][j] == '*')
				countedMines++;
		}
	}
	cout << endl << "counted mines:" << countedMines << endl;
	cout << endl << "field counter:" << fieldCounter << endl;
}

// a function that creates 'userBoard' table
void Square::createUserBoard() {
	/*
		1. allocating memory for the attribute 'isVisited' dynamically
		2. assignes 'false' to every entry
	*/
	isVisited = new bool* [side];
	for (int i = 0; i < side; i++) {
		isVisited[i] = new bool[side];
	}
	for (int i = 0; i < side; i++) {
		for (int j = 0; j < side; j++) {
			isVisited[i][j] = false;
		}
	}
	/*
		3. allocates memory for the attribute 'table' dynamically
		4. assigns a char '-' to every entry of the 'table'
	*/
	table = new char* [side];
	for (int i = 0; i < side; i++) {
		table[i] = new char[side];
	}
	for (int i = 0; i < side; i++) {
		for (int j = 0; j < side; j++) {
			table[i][j] = '-';
		}
	}
	//   5. the attribute 'fieldCounter' is expected to be set to 0
	fieldCounter = 0;
}
// a function that receives an input from user to make a move
int Square::move(Square& original) {
	//   1. writes data from the attribute 'table' to a file
	original.writeOriginalToFile();
	int r, c;
	char i;
	/*
		2. inside a while loop which ends when the value of 'fieldCounter' matches the number of non-mine entries in the 'table' that the player needs to open to win
			1. inside another while loop:
				- exception handling:
					* gets inputs for local variables 'r', 'c', and 'i' /r - row, c - column, i - whether the player wants to open or mark/
					* if it is a valid input, breaks the inner while loop
					* if not throws an exception
					* catches the exception, prints error message to screen, and clears an input buffer, lastly go to try block again since the iiner while loop is not broken
	*/
	while (fieldCounter != (side * side - mines)) {
		while (true) {
			try {
				cout << " \n Enter a coordinate of an entry that is expected to be opened or marked. \n To open, please enter a row and a column and a character 'o'";
				cout << "\n To mark, please enter a row and a column and then a character 'm'\n ";
				cin >> r >> c >> i;
				if (r > 0 && r <= side && c > 0 && c <= side && (i == 'o' || i == 'm')) {
					break;
				}
				else {
					throw - 1;
				}
			}
			catch (int e) {
				cerr << "invalid input. Enter again:" << endl;
				cin.clear();
				cin.ignore(10000, '\n');
			}
		}
		//  - the values of local variables 'r' and 'c' needs to be decremented because there is a gap between the player's input ant indecies of the 
		//    attribute 'table'
		r = r - 1;
		c = c - 1;
		/*
				2. if the local variable 'i' is a char 'o' /it means to open/
					- checks if it is a mine, if it is a mine:
															- clears screen
															- prints a message about the player has just clicked on a mine
															- prints the 'original' table
															- returns -1 / in the main function that function /'move'/ is called when returning value is 1/
					- if it is a char '0' 
										- a function 'shorNeighboursForZero' is called /when the player clicks an entry that contains a char '0' its neighbours 
										  need to be opened/
										- clears screen
										- prints the attribute 'table' of the object 'userBoard' 
										- every time the player clicks on a non-mine entry the 'userBoard' table is written into a file ,for next time if the player
										  wants to continue the last game, to write information from the file to the attribute 'table' of the object 'userBoard'
										- returns 1
					- if it is a non-mine or non-zero entry
															- copy the entry from the attribute 'table' of the object 'original' to the attribute of the object 
															  'userBoard'
															- clears screen
															- prints the 'userBorad' table
															- every time the player clicks on a non-mine entry the 'userBoard' table is written into a file ,for 
															  next time if the player wants to continue the last game, to write information from the file to the 
															  attribute 'table' of the object 'userBoard'
															- returns 1
		*/
		if (i == 'o') {
			if (original.table[r][c] == '9') {
				system("cls");
				cout << "you clicked on a mine." << endl;
				original.printSquare(original);
				return -1;
			}
			else if (original.table[r][c] == '0') {
				this->showNeighboursForZero(r, c, original);
				system("cls");
				this->printSquare(original);
				writeUserBoardToFile();
				return 1;
			}

			else
			{
				table[r][c] = original.table[r][c];
				system("cls");
				this->printSquare(original);
				writeUserBoardToFile();
				return 1;
			}
		}
		/*
				3. if the local variable 'i' is a char 'm' /means to mark/
					- assigns a char '*' to the entry
					- clears screen
					- prints the 'userBoard' table
					- every time the player clicks on a non-mine entry the 'userBoard' table is written into a file ,for next time if the player
					  wants to continue the last game, to write information from the file to the attribute 'table' of the object 'userBoard'
					- returns 1
		*/
		else if (i == 'm') {
			table[r][c] = '*';
			system("cls");
			this->printSquare(original);
			writeUserBoardToFile();
			return 1;
		}

	}
	/*
		3. when the outer while loop finishes /when player wins/ 
			- clears screen
			- prints the 'original' table
			- prints a message about the player has just sweeped all the mines
			- returns -1
	*/
	system("cls");
	original.printSquare(original);
	cout << " you have sweeped all the mines." << endl;
	return -1;
}


// a function to show neighbours of a zero entry when player clicks on a zero entry /written by chatgpt/
void Square::showNeighboursForZero(int r, int c, Square& original) {
	/*
		1. defines the 'dr' and 'dc' arrays of integers /dr - direction for row, dc - direction for column/. They are needed when we determine neighbours of the
		   zero entry where a coordinate is formed by respective elements of both of the arrays indicating a location of neighbouring entries with respect to the 
		   zero entry
		2. assigns 'true' for the entry of the attribute 'isVisited' of the object 'userBoard' which indicates that the entry has been visited
		3. copies an entry, that matches the coordinate 'r' and 'c', of the attribute 'table' of the object 'original' to an entry, that matches the coordinate 
		   'r' and 'c', of the attribute 'table' of the object 'userBoard'
		4. inside the for loop 
			- defines a local variable 'newrow' with a value which is equal to the value of the 'r' plus ith element of the 'dr' array
			- defines a local variable 'newcol' with a value which is equal to the value of the 'c' plus ith element of the 'dc' array
			- if the values  of the variables 'newrow' and 'newcol' is valid /can be a coordinate of an entry in the 'table'/
				- copies an entry table[newrow][newcol] of the object 'original' to an entry table[newrow][newcol] of the object 'userBoard'
				- another if statement that checks whether the entry isVisited[newrow][newcol] of the object 'userBoard' is 'false' and the entry 
				  table[newrow][newcol] of the object 'original' is char '0'. If taht condition holds:
						-calls the showNeighboursForZero function itself /recursion/

				  
	*/
	int dr[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	int dc[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	isVisited[r][c] = true;
	table[r][c] = original.table[r][c];
	for (int i = 0; i < 8; i++) {
		int newrow = r + dr[i];
		int newcol = c + dc[i];
		if (newrow >= 0 && newrow < side && newcol >= 0 && newcol < side) {
			table[newrow][newcol] = original.table[newrow][newcol];
			if (!isVisited[newrow][newcol] && original.table[newrow][newcol] == '0') {
				showNeighboursForZero(newrow, newcol, original);
			}
		}
	}
}
// a function that writes data from the attribute 'table' of the object 'original' to a file named "last_game_original.txt"
void Square::writeOriginalToFile() {
	/*
		1. opens the file for writing
		2. copies every entry of the 'table' of the object 'original' to the file
		3. closes the file
	*/
	fstream file;
	file.open("last_game_original.txt", ios::out);
	for (int i = 0; i < side; i++) {
		for (int j = 0; j < side; j++) {
			file << table[i][j];
		}
	}
	file.clear();
}

// a function that writes data from the attribute 'table' of the object 'original' to a file named "last_game_original.txt"
void Square::writeUserBoardToFile() {
	/*
		1. opens the file for writing
		2. copies every entry of the 'table' of the object 'userBoard' to the file
		3. closes the file
	*/
	fstream file;
	file.open("last_game_Userboard.txt", ios::out);
	for (int i = 0; i < side; i++) {
		for (int j = 0; j < side; j++) {
			file << table[i][j];
		}
	}
	file.close();
}
 // a function for reading data from the file named "last_game_original.txt" to the attribute 'table' of the object 'original'
void Square::readOriginalFromFile() {
	/*
		1. opens the file for reading
		2. declares a string named 'data'
		2. copies data from the file to the string 'data'
		4. set an attribute 'side' of an object 'original' by taking square root of lenght of the string 'data' /the 'table' is square /
		5. allocates memory for the attribute 'table' of the object 'original' dynamically
		6. copies every element of the string 'data' to the 'table' of the object 'original'
		7. allocates memory for the attribute 'isVisited' of the object 'original' dynamically
		8. assigns every entry of the 'isVisited' as 'false'
		9. closes the file
	*/
	fstream file;
	file.open("last_game_original.txt", ios::in);
	string data;
	file >> data;
	side = sqrt(data.length());
	table = new char* [side];
	for (int i = 0; i < side; i++) {
		table[i] = new char[side];
	}
	int n = 0;
	for (int i = 0; i < side; i++) {
		for (int j = 0; j < side; j++) {
			table[i][j] = data[n++];
		}
	}
	isVisited = new bool* [side];
	for (int i = 0; i < side; i++) {
		isVisited[i] = new bool[side];
	}
	for (int i = 0; i < side; i++) {
		for (int j = 0; j < side; j++) {
			isVisited[i][j] = false;
		}
	}
	file.close();
}

// a function for reading data from the file named "last_game_UserBoard.txt" to the attribute 'table' of the object 'userBoard'
void Square::readUserboardFromFile() {
	/*
		1. opens the file for reading
		2. declares a string named 'data'
		2. copies data from the file to the string 'data'
		4. set an attribute 'side' of an object 'userBoard' by taking square root of lenght of the string 'data' /the 'table' is square /
		5. allocates memory for the attribute 'table' of the object 'userBoard' dynamically
		6. copies every element of the string 'data' to the 'table' of the object 'userBoard'
		7. allocates memory for the attribute 'isVisited' of the object 'userBoard' dynamically
		8. assigns every entry of the 'isVisited' as 'false'
		9. closes the file
	*/
	fstream file;
	file.open("last_game_Userboard.txt", ios::in);
	string data;
	file >> data;
	side = sqrt(data.length());
	table = new char* [side];
	for (int i = 0; i < side; i++) {
		table[i] = new char[side];
	}
	int n = 0;
	for (int i = 0; i < side; i++) {
		for (int j = 0; j < side; j++) {
			table[i][j] = data[n++];
		}
	}
	isVisited = new bool* [side];
	for (int i = 0; i < side; i++) {
		isVisited[i] = new bool[side];
	}
	for (int i = 0; i < side; i++) {
		for (int j = 0; j < side; j++) {
			isVisited[i][j] = false;
		}
	}
	file.close();
}