/*
    Created by DrVrej.
    Initial creation date: May 10, 2020.
    Idea: http://www.cppforschool.com/project/tic-tac-toe-project.html

	Features:
	- All 8 possible combinations + draw (tie)
	- Multiplayer
	- Can detect invalid inputs
	- Can restart game

	Compiling:
	1. windres icon.rc -O coff -o icon.res
		- To create the icon
	2. g++ -o TicTacToe TicTacToe.cpp icon.res -static
*/
#include <iostream>

#define COLOR_DEFAULT		"\033[0m"
#define COLOR_RED			"\033[31m"
#define COLOR_GREEN			"\033[32m"
#define COLOR_YELLOW		"\033[33m"
#define COLOR_CYAN			"\033[36m"
#define COLOR_RED_BOLD		"\033[1m\033[31m"
#define COLOR_WHITE_BOLD	"\033[1m\033[37m"

char boxes[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

// Draws the board
void drawBoard(){
	std::cout << COLOR_WHITE_BOLD << "\n     " << boxes[0] << " | " << boxes[1] << " | " << boxes[2] << '\n';
    std::cout << "     " << "---------\n"; // Seperator
    std::cout << "     " << boxes[3] << " | " << boxes[4] << " | " << boxes[5] << '\n';
    std::cout << "     " << "---------\n"; // Seperator
    std::cout << "     " << boxes[6] << " | " << boxes[7] << " | " << boxes[8] << "\n\n" << COLOR_DEFAULT;
}

int main(){
    bool done{false}; // Is the game over?
	char turn{'X'}; // Whose turn is it? 'X' or 'O'
	restart: // Jump here if user decides to play again!

    while(done != true){
		int entered_num; // The user's input
		std::string result; // Will be printed as the result once the game is over

		redo_draw: // Jump here and redraw the board if the game has been finished
		system("cls"); // Clears the console, only for Windows!
		std::cout << COLOR_CYAN << "        Tic Tac Toe\n";
		std::cout << "     Created by DrVrej!\n";
		std::cout << COLOR_DEFAULT << "Player 1 (X) - Player 2 (O)\n";
		drawBoard();

		if(done == false){
			std::cout << "Player " + (std::string() + turn) + ", enter a number (1-9):\n";
			redo_input: // Jump here if the input is incorrect
			
			//std::cout << std::endl;
			std::cin >> entered_num;
			// Redo the input code if the given input is incorrect (Non-number or not 1 to 9)
			if((!entered_num) || (entered_num < 1) || (entered_num > 9)){
				std::cout << COLOR_RED_BOLD << "Incorrect input! Please input a number from 1 to 9\n" << COLOR_DEFAULT;
				std::cin.clear(); // Clear all input flags (ex: errors)
				std::cin.ignore(); // Ignore all the previous objects in the buffer
				goto redo_input;
			}else if(boxes[entered_num - 1] != ('0' + entered_num)){
				std::cout << COLOR_RED_BOLD << "That spot is already marked! Try again!\n" << COLOR_DEFAULT;
				std::cin.clear(); // Clear all input flags (ex: errors)
				std::cin.ignore(); // Ignore all the previous objects in the buffer
				goto redo_input;
			}
		}
		// Put X / O on the selected box
		boxes[entered_num - 1] = turn;

		/* Check if a player won: */
		if(done == false){
			result = "Player " + (std::string() + turn) + " won by ";
			// ROW (3)
			if((boxes[0] == turn && boxes[1] == turn && boxes[2] == turn) || (boxes[3] == turn && boxes[4] == turn && boxes[5] == turn) || (boxes[6] == turn && boxes[7] == turn && boxes[8] == turn)){
				result += "matching 3 in a row (- - -)";
				done = true;
				goto redo_draw;
			// COLUMN (3)
			}else if((boxes[0] == turn && boxes[3] == turn && boxes[6] == turn) || (boxes[1] == turn && boxes[4] == turn && boxes[7] == turn) || (boxes[2] == turn && boxes[5] == turn && boxes[8] == turn)){
				result += "matching 3 in a column (| | |)";
				done = true;
				goto redo_draw;
			// DIAGONAL (2)
			}else if((boxes[0] == turn && boxes[4] == turn && boxes[8] == turn) || (boxes[2] == turn && boxes[4] == turn && boxes[6] == turn)){
				result += "matching 3 in a diagonal (/ / /)";
				done = true;
				goto redo_draw;
			}else if(boxes[0] != '1' && boxes[1] != '2' && boxes[2] != '3' && boxes[3] != '4' && boxes[4] != '5' && boxes[5] != '6' && boxes[6] != '7' && boxes[7] != '8' && boxes[8] != '9'){
				result = "No winner! The result is a draw!";
				done = true;
				goto redo_draw;
			}
		}

		// If game is over then print out the result
		if(done == true){
			std::cout << "        GAME OVER!\n";
			std::cout << result << '\n';
		}else{ // Switch the turn for the next round
			if(turn == 'X'){
				turn = 'O';
			}else{
				turn = 'X';
			}
		}
    }

	// Check if the user wants to play again
	std::cout << COLOR_YELLOW << "\nDo you want to play again? (" << COLOR_GREEN << "y" << COLOR_DEFAULT << "/" << COLOR_RED <<"n" << COLOR_DEFAULT << ")\n\a";
	char play_again;
	std::cin >> play_again;
	// If y then reset all the values and jump back up
	if(play_again == 'y'){
		for(int n = 0; n <= 8; n++){
			boxes[n] = '0' + (n + 1);
		}
		done = false;
		turn = 'X';
		goto restart;
	}

    return EXIT_SUCCESS;
}