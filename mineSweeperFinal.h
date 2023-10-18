#pragma once
#pragma once
#include <stdlib.h>
#include<string>
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<Windows.h>
#include<cstdio>
#include<ios>
#include<fstream>
#include<math.h>

class Square {
	int side;
	int mines;
	int countedMines;
	int fieldCounter;
	char** table;
	bool** isVisited;
	/* Attributes:
	   side - side of a table | mines - max number of mines in a table | countedMines - number of entries of a table that are marked as suspected containing a mine
	   fieldCounter - number of entries that player has opened so far | table - the board that contains mines and fields
	   isVisited - a 2D array ,whose size is same as the table which is used in showNeighnoursForZero function, contains information about every entry whether it is
	   visited: false - not visited, true - visited
	*/
public:
	Square(); //Definition at line 8 of file mineSweeperFinal.cpp.
	~Square();//Definition at line 24 of file mineSweeperFinal.cpp.
	void printMenu(Square& userBoard);//Definition at line 90 of file mineSweeperFinal.cpp.
	void createTable();//Definition at line 45 of file mineSweeperFinal.cpp.
	void assignNeighbours()const;//Definition at line 205 of file mineSweeperFinal.cpp.
	void printSquare(Square& original);//Definition at line 370 of file mineSweeperFinal.cpp.
	void createUserBoard();//Definition at line 431 of file mineSweeperFinal.cpp.
	int move(Square& original);//Definition at line 462 of file mineSweeperFinal.cpp.
	void showNeighboursForZero(int r, int c, Square& original);//Definition at line 579 of file mineSweeperFinal.cpp.
	void writeOriginalToFile();//Definition at line 614 of file mineSweeperFinal.cpp.
	void writeUserBoardToFile();//Definition at line 631 of file mineSweeperFinal.cpp.
	void readOriginalFromFile();//Definition at line 647 of file mineSweeperFinal.cpp.
	void readUserboardFromFile();//Definition at line 687 of file mineSweeperFinal.cpp.
};

