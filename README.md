# mineSweeper
## Introduction and problem statement
This is a single-player game which is played on a rectangular board that has
clickable squares with hidden bombs. The objective is to clear the board without
clicking on any bombs. If a player clicks on a bomb, the game ends. A number
between 0 (displayed as a blank) to 8 is displayed that identifies the total number of
bombs in the 8 neighboring squares. A player can mark a square as a flag which
implies the square is suspected of containing a bomb.
## Solution Design and Implementation
 The whole program is console based and is done on one class called ‘Square’
which contains attributes mines, side, countedMines, fieldCounter, table, and
isVisited and methods Square, ~Square, printMenu, createTable, assignNeighbours,
printSquare, createUserBoard, move, showNeighboursForZero, writeOriginalToFile,
writeUserBoardToFile, readOriginalFromFile, and readUserboardFromFile.
Implementations of every function is written in the source code as comments.
 Dynamic memory allocation, exception handling and file handling is included in
the project.
## Testing and Verification
The application has all the features that a regular minesweeper game should
have and all these features function properly as tested by manual check of input and
expected output. Entering invalid input – catching exception and prompting the user
to enter values again until the input is valid.
