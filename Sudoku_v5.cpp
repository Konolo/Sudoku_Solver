/**
* This application attempts to solve a Sudoku puzzle which has been provided by the user
* 
* Author: Matthew Jacobs
* Version: 5.1.1
* Created: September 2021
* Updated: June 2024
* Copyright: Matthew Jacobs
* 
* Description: This application gets a Sudoku puzzle from the user in one of two ways
*	and then attempts to solve the puzzle. If it could not be solved
*	the user is notified. The program ends after the puzzle is either
*	solved or was unable to be solved.
*/

// imports
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <bitset>
#include <tuple>
#include <cmath>
#include <set>
using namespace std;

// intilize global variables
clock_t runTime = clock();
int RCVsize = 20;
int PH = 0;
vector<int> RCVform(20, 0);
auto RCV = make_tuple(RCVform, RCVform, RCVform);  //tuple<vector<int>, vector<int>, vector<int>> RCV = make_tuple(RCVform, RCVform, RCVform);
//[0] = 0; [1] = 1; [2] = 1; [3] = 1 [4] = 1; [5] = 1; [6] = 1; [7] = 1; [8] = 1; [9] = 1;
bitset<10> start(string("1111111110"));
bitset<10> reset(string("0000000001"));


class sudoku {
public:
	// Puzzle board with the boarders
	int PuzzleBoard[13][13] = { {11,12,10,10,12,10,10,10,12,10,10,12,11}, {11, 0, 0, 7,11, 9, 0, 0,11, 0, 0, 0,11}, {11, 0, 6, 0,11, 0, 0, 2,11, 9, 7, 0,11}, {11, 9, 2, 0,11, 0, 7, 1,11, 0, 0, 0,11}, {11,10,10,10,11,10,10,10,11,10,10,10,11}, {11, 4, 0, 0,11, 0, 0, 0,11, 0, 8, 0,11}, {11, 8, 0, 6,11, 4, 0, 3,11, 7, 0, 1,11}, {11, 0, 5, 0,11, 0, 0, 0,11, 0, 0, 9,11}, {11,10,10,10,11,10,10,10,11,10,10,10,11}, {11, 0, 0, 0,11, 2, 8, 0,11, 0, 1, 6,11}, {11, 0, 8, 3,11, 6, 0, 0,11, 0, 4, 0,11}, {11, 0, 0, 0,11, 0, 0, 5,11, 2, 0, 0,11}, {11,12,10,10,12,10,10,10,12,10,10,12,11} };
	
	// Puzzle without boarders
	int Puzzle[9][9] = { {0,0,7,9,0,0,0,0,0}, {0,6,0,0,0,2,9,7,0}, {9,2,0,0,7,1,0,0,0}, {4,0,0,0,0,0,0,8,0}, {8,0,6,4,0,3,7,0,1}, {0,5,0,0,0,0,0,0,9}, {0,0,0,2,8,0,0,1,6}, {0,8,3,6,0,0,0,4,0}, {0,0,0,0,0,5,2,0,0} };
	
	// Puzzle as characters
	char charPuzzle[9][9] = { {'0','0','7','9','0','0','0','0','0'}, {'0','6','0','0','0','2','9','7','0'}, {'9','2','0','0','7','1','0','0','0'}, {'4','0','0','0','0','0','0','8','0'}, {'8','0','6','4','0','3','7','0','1'}, {'0','5','0','0','0','0','0','0','9'}, {'0','0','0','2','8','0','0','1','6'}, {'0','8','3','6','0','0','0','4','0'}, {'0','0','0','0','0','5','2','0','0'} };

	vector<vector<bitset<10>>> CouldbeTable = { {start, start, start, start, start, start, start, start, start}, {start, start, start, start, start, start, start, start, start}, {start, start, start, start, start, start, start, start, start}, {start, start, start, start, start, start, start, start, start}, {start, start, start, start, start, start, start, start, start}, {start, start, start, start, start, start, start, start, start}, {start, start, start, start, start, start, start, start, start}, {start, start, start, start, start, start, start, start, start}, {start, start, start, start, start, start, start, start, start} };
	vector<bitset<10>> table = { start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start, start };
	// Sq11, Sq12, Sq13, Sq21, Sq22, Sq23, Sq31, Sq32, Sq33, Sq14, ... // divided by big square

	vector<set<int>> Dot = { {0,1,2,3,4,5,6,7,8}, {9,10,11,12,13,14,15,16,17}, {18,19,20,21,22,23,24,25,26}, {27,28,29,30,31,32,33,34,35}, {36,37,38,39,40,41,42,43,44}, {45,46,47,48,49,50,51,52,53}, {54,55,56,57,58,59,60,61,62}, {63,64,65,66,67,68,69,70,71}, {72,73,74,75,76,77,78,79,80} };
	vector<set<int>> R = { {0,1,2,9,10,11,18,19,20}, {3,4,5,12,13,14,21,22,23}, {6,7,8,15,16,17,24,25,26}, {27,28,29,36,37,38,45,46,47}, {30,31,32,39,40,41,48,49,50}, {33,34,35,42,43,44,51,52,53}, {54,55,56,63,64,65,72,73,74}, {57,58,59,66,67,68,75,76,77}, {60,61,62,69,70,71,78,79,80} };
	vector<set<int>> C = { {0,3,6,27,30,33,54,57,60}, {1,4,7,28,31,34,55,58,61}, {2,5,8,29,32,35,56,59,62}, {9,12,15,36,39,42,63,66,69}, {10,13,16,37,40,43,64,67,70}, {11,14,17,38,41,44,65,68,71}, {18,21,24,45,48,51,72,75,78}, {19,22,25,46,49,52,73,76,79}, {20,23,26,47,50,53,74,77,80} };
};

sudoku grid;

// Parameters:
//    - Row: The y component of the cell coordinate
//    - Col: The x component of the cell coordinate
// RETURNS:
//    - Returns the one dimentional coordinate of the cell
// This function converts a 2-dimentional coordinate into a 1-dimentional coordinate
int RC_dot(int Row, int Col) {
	int loc = 0;
	loc = (Row > 5) ? 54 : ((Row > 2) ? 27 : 0);
	loc += (Col > 5) ? 18 : ((Col > 2) ? 9 : 0);

	int MRow = int(fmod(Row, 3));
	int MCol = int(fmod(Col, 3));

	loc += (MRow > 1) ? 6 : ((MRow > 0) ? 3 : 0);
	loc += (MCol > 1) ? 2 : ((MCol > 0) ? 1 : 0);

	return loc;
}

// Parameters:
//    - dot: The 1-dimentional coordinate of the cell
//    - Row: The y component of the cell coordinate
//    - Col: The x component of the cell coordinate
// This function converts a 1-dimentional coordinate into a 2-dimentional coordinate
void dot_RC(int dot, int* Row, int* Col) {
	int k1 = int(fmod(dot, 27));
	int k2 = int(fmod(dot, 9));
	int k3 = int(fmod(dot, 3));

	*Row = (dot > 54) ? 6 : ((dot > 27) ? 3 : 0);
	*Col = (k1 > 18) ? 6 : ((k1 > 9) ? 3 : ((k1 == 0) ? 6 : 0));
	*Row += (k2 > 6) ? 2 : ((k2 > 3) ? 1 : ((k2 == 0) ? 2 : 0));
	*Col += (k3 > 2) ? 2 : ((k3 > 1) ? 1 : ((k3 == 0) ? 2 : 0));
}

// Parameters:
//    - list: A bitset representing which cells have already been solved
//    - hold: A vector of sets which hold the positions of other cells
//    - v: The value of a cell, -1 if a value is not provided
// This function is a staging point from which either the OnlyPlace or Square_set function can be called depending on the input
void sender(bitset<81>* list, vector<set<int>*> hold, int v = -1) {
	// loops through the 3 elements in the hold structure
	for (int k = 0; k < 3; k++) {
		vector<bitset<10>*> build;
		// calls either OnlyPlace or Square_set depending on if a value was provided
		if (v == -1) { OnlyPlace(helper(list, hold.at(k), &build)); }
		else { Square_set(helper(list, hold.at(k), &build), &v); }
	}
}

// This function assists the user in the process of inputting the puzzle
void InsertPuzzle() {
	bool InsertPuzzle = true;
	char Insert;
	string Command;
	string InputMethod;

	cout << " Would you like to input a puzzle to solve? (y/n): ";
	cin >> Insert;
	cout << endl;

	if (Insert == 'y') {
		while (InsertPuzzle == true) {
			// determine what input method to use
			cout << " Select which way you will be inputing the puzzle from the list below:\n"
				<< "    * \"space\"  (each number is seperated with a space)\n"
				<< "    * \"together\"  (nothing separates the numbers being input)" << endl;

			do {
				cout << "\n Input Method: ";
				cin >> InputMethod;

				if (InputMethod != "space" && InputMethod != "together") {
					cout << " The input method input above is not valid, please input a valid input method" << endl;
				}
			} while (InputMethod != "space" && InputMethod != "together");

			// get the puzzle input
			PuzzleInput(&InputMethod);

			cout << endl;
			// check if the puzzle needs to be input again
			cout << " Please enter one of the following commands:\n"
				<< "    * \"solve\"  (proceeds to solve the puzzle)\n"
				<< "    * \"reinput\"  (allows you to input the puzzle again)" << endl;

			do {
				cout << "\n Input Command: ";
				cin >> Command;

				if (Command == "reinput") { break; }
				if (Command != "solve" && Command != "reinput") {
					cout << " The command input above is not valid, please input a valid command" << endl;
				}
			} while (Command != "solve");

			InsertPuzzle = (Command == "solve") ? false : true;
		}
	}

	cout << endl;
}

// This function gets the puzzle data from the user
void PuzzleInput(string* method) {
	string s, s1, s2, s3, s4, s5, s6, s7, s8, s9;
	char c;

	// explains how to input the puzzle
	cout << " Please insert the puzzle below following these rules:\n"
		 << "    *Insert blank spaces as 0,\n"
		 << "    *Insert each row on a new line,\n"
		 << "    *Insert each row from Left to Right." << endl;

	if ((*method) == "space") {
		cout << "    *Seperate each number with one or more spaces\n"
			 << "    *For the best looking input, line up each number with C that appears above it." << endl;
		cout << endl;
		cout << "     C0 C1 C2 C3 C4 C5 C6 C7 C8" << endl;
	}
	else {
		cout << endl;
	}

	for (int i = 0; i < 9; i++) {
		// gets the user input
		if ((*method) == "space") {
			cout << " R" << i << ": ";
			cin >> s1 >> s2 >> s3 >> s4 >> s5 >> s6 >> s7 >> s8 >> s9;
			s = s1 + s2 + s3 + s4 + s5 + s6 + s7 + s8 + s9;
		}
		else {
			cout << " R" << i << ": ";
			cin >> s;
		}

		// adds the data into the board
		for (int j = 0; j < 9; j++) {
			c = s[j];
			grid.Puzzle[i][j] = atoi(&c);
		}
	}
}

// RETURNS:
//    - Returns the number of blank cells
// This function outputs the puzzle to the screen along with some other information
int draw() {
	int remain = 0;
	static int run = 0;
	string save = " ";

	// loops through the entire puzzle board and prints it out
	for (int Row = 0; Row < 13; Row++) {
		for (int Col = 0; Col < 13; Col++) {
			switch (grid.PuzzleBoard[Row][Col]) {
			case 0:
				save += "   "; remain++; break;
			case 1: case 2: case 3:
			case 4: case 5: case 6:
			case 7: case 8: case 9:
				save = save + " " + to_string((grid.PuzzleBoard[Row][Col])) + " "; break;
			case 10:
				save += "==="; break;
			case 11:
				save += "|"; break;
			case 12:
				save += "=="; break;
			}
		}

		cout << save << endl;
		save = " ";
	}

	// prints out information about the state of the puzzle
	cout << "  - " << remain << " blank spaces remain" << endl;

	if (run == 0) {
		cout << "  - The program is ready to solve the puzzle\n" << endl;
	}
	else {
		cout << "  - The program has been executed " << run << " times\n" << endl;
	}

	run += 1;
	return remain;
}

// Parameters:
//    - list: A bitset representing which cells have already been solved
// This function froms groups of cells to be examined
void OnlyPlace_GroupFormer(bitset<81> *list) {
	for (int i = 0; i < 9; i++) {
		sender(list, { &grid.Dot.at(i), &grid.R.at(i), &grid.C.at(i) });
	}
}

// Parameters:
//    - list: A bitset representing which cells have already been solved
//    - hold: A set which hold the positions of cells from a row, column, or square
//    - build: A list of bitsets representing what values can exist in that cell
// RETURNS:
//    - Returns a list of bitsets representing what values can exist in that cell
// This function separates out the blank cells from a row, column, or square
vector<bitset<10>*>* helper(bitset<81>* list, set<int>* hold, vector<bitset<10>*>* build) {
	vector<int> solved;

	// Iterate through hold
	for (set<int>::iterator it = hold->begin(); it != hold->end(); ++it) {

		// if the cell is not filled in, add it to the list to examine, otherwise add it to the solved list
		if ((*list).test(*it) == false) build->push_back(&grid.table.at(*it)); 
		else { solved.push_back(*it); }
	}

	// loop through the solved list and remove those cells from hold
	for (int k = 0; k < int(solved.size()); k++) {
		hold->erase(hold->find(solved.at(k)));
	}

	return build;
}

// Parameters:
//    - group: A list of bitsets representing what values can exist in that cell
// Determines if there is only one cell in a row, column, or square that can be some value x
void OnlyPlace(vector<bitset<10>*>* group) {
	bitset<9> determiner(string("000000000"));

	// loops through each of the 9 possible values
	for (int val = 1; val <= 9; val++) {
		// if group is empty, break out of the loop
		if ((*group).size() == 0) { break; }
		// loops through group
		for (int index = 0; index < int((*group).size()); index++) {
			// sets the bitset to the value within the group bitsets at some value
			determiner[index] = (*(group->at(index)))[val];
		}

		// see if only one cell could be some value
		if (determiner.count() == 1) {
			int hold = -1;
			int counter = 0;

			// determine which group (cell) from the row, column, or square must be a certain value
			while (hold == -1) {
				hold = (determiner.test(counter)) ? counter : -1;
				counter += 1;
			}

			// make the cell reflect that it must be some value
			((*group).at(hold))->reset();
			((*group).at(hold))->set(val);
		}

		determiner.reset();
	}
}

// Parameters:
//    - list: A bitset representing which cells have already been solved
// Searches through all the cells on the board and calls sender to be examined
void Search_sq(bitset<81>* list) {
	int Row = 0, Col = 0;

	// loops through all the cells on the board
	for (int i = 0; i < 81; i++) {
		dot_RC(i + 1, &Row, &Col);

		// see if the cell is empty
		if (grid.Puzzle[Row][Col] != 0) {
			int RCv = grid.Puzzle[Row][Col];
			grid.table.at(i) = reset;

			sender(list, { &grid.Dot.at(i / 9), &grid.R.at(Row), &grid.C.at(Col) }, RCv);
		}
	}
}

// Parameters:
//    - Set: A vector of bitsets representing the possible values that can exist in each cell
//    - index: The value of a cell that is already known (i.e. 9)
// This function updates the possible values that a cell could be based on the value of a newly found cell which impacts the other cells
void Square_set(vector<bitset<10>*>* Set, const int* index) {
	// loops through all the bitsets in the vector
	for (int i = 0; i < int((*Set).size()); i++) {
		// sets the value in the bitset at the index to zero (denotes that this value can't be in this square)
		(*(Set->at(i)))[*index] = 0;
	}
}

// Searches all the cells and calls check_Print on those which have been filled in
void passThrough() {
	int Row, Col;

	// loops through all the cells
	for (int i = 0; i < 81; i++) {
		bitset<10> passingOn = grid.table.at(i);
		dot_RC(i + 1, &Row, &Col);

		// checks if the cell is filled in
		if (passingOn[0] == 0 && passingOn.count() == 1) { check_Print(passingOn, &Row, &Col); }
	}
}

// Parameters:
//    - universal: A bitset holding the possible values that a cell could be
//    - row: The y component of the cell coordinate
//    - col: The x component of the cell coordinate
// Adds the position and value of the cell into the RCV (Row, Column, Value) tuple so the board can be updated
void check_Print(bitset<10> universal, int* row, int* col) {
	int Success_holder = 0;

	// loops through the possible values and checks if the value is set
	for (int i = 1; i <= 9; i++) {
		if (universal[i] == 1) { Success_holder = i; break; }
	}

	// adds the values to the RCV by either pushing it on or by just adding it to a position
	if (PH > (RCVsize - 1)) {
		(get<0>(RCV)).push_back(*row);
		(get<1>(RCV)).push_back(*col);
		(get<2>(RCV)).push_back(Success_holder);
		PH++;
	}
	else {
		(get<0>(RCV)).at(PH) = *row;
		(get<1>(RCV)).at(PH) = *col;
		(get<2>(RCV)).at(PH) = Success_holder;
		PH++;
	}
}

// Updates the puzzle with all the filled in cells
void Print() {
	// loops through the RCV
	for (int add = 0; add < PH; add++) {
		// pull out the values
		int x = (get<0>(RCV)).at(add);
		int y = (get<1>(RCV)).at(add);
		int z = (get<2>(RCV)).at(add);

		// update the puzzle
		grid.Puzzle[x][y] = z;
		(get<0>(RCV)).at(add) = 0;
		(get<1>(RCV)).at(add) = 0;
		(get<2>(RCV)).at(add) = 0;
	}

	// resize the RCV
	RCVsize = (PH > (RCVsize - 1)) ? ((get<0>(RCV)).size() - 1) : RCVsize;
	PH = 0;
}

// Parameters:
//    - List: A bitset representing which cells have already been solved
// Updates the PuzzleBoard to reflect the current state of the board
void picture_setup(bitset<81> *List) {
	int adj_r = 1;
	int adj_c = 1;

	// determine what offsets are needed to translate between the two boards
	for (int Row = 0; Row < 9; Row++) {
		adj_r = (Row > 2) ? 2 : 1;
		adj_r = (Row > 5) ? 3 : adj_r;

		for (int Col = 0; Col < 9; Col++) {
			adj_c = (Col > 2) ? 2 : 1;
			adj_c = (Col > 5) ? 3 : adj_c;

			// update the board
			grid.PuzzleBoard[Row + adj_r][Col + adj_c] = grid.Puzzle[Row][Col];

			// update list
			if (grid.Puzzle[Row][Col] != 0) { (*List)[RC_dot(Row, Col)] = 1; }
		}
	}
}

int main() {
	static int emptySpace = 0;
	static int spaceHold = emptySpace;
	static bool noChangeInSpace = false;
	static clock_t solveTime;
	bitset<81> list;
	grid.table;

	// do initial puzzle set up
	InsertPuzzle();
	solveTime = clock();
	picture_setup(&list);
	emptySpace = draw();

	// as long as there are blank spaces keep looking for a solution
	while (emptySpace != 0) {
		Search_sq(&list);
		OnlyPlace_GroupFormer(&list);
		passThrough();
		Print();
		picture_setup(&list);
		emptySpace = draw();

		// check to see if there is any change in the state of the puzzle
		if (noChangeInSpace == true && spaceHold == emptySpace) {
			cout << " -> The program was unable to solve the puzzle." << endl;
			return 1;
		}

		noChangeInSpace = (spaceHold == emptySpace) ? true : false;
		spaceHold = emptySpace;
	}

	// display information about how long it took to solve
	cout << " Puzzle Completed!\n"
		<< "    It took " << ((float)clock() - solveTime) / CLOCKS_PER_SEC << " Seconds to solve the puzzle\n"
		<< "    and the program was running for " << ((float)clock() - runTime) / CLOCKS_PER_SEC << " Seconds\n"
		<< " Thank you and have a good day" << endl;
	return 0;
}
