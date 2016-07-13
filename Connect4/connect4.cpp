/* CSCI1520
* Assignment:5
* Student ID:1155034528
* Name      :Ng Yin Hei
* E-mail adr:bensonyongvanich@gmail.com
*/

#include <iostream>
using namespace std;

// displayBoard is a function to display the board
void displayBoard(char board[][7]) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++)
			cout << board[i][j];
		cout << endl;
	}
	cout << "0123456\n";
	return;
}

// checkInput is a function to check whether the position is valid move
int checkInput(int check[], int pos) {
	int flag = 0;
	if (check[pos] == 6)
		flag = 1;
	return flag;
}

//updateBoard is a function to update the board variable
char updateBoard(char board[][7], int check[], int pos, char p) {
	board[5 - check[pos]][pos] = p;		//5-check[pos] is to update the board form the bottom to top
	return board[5-check[pos]][pos];
}

// checkWinningState is to check the winning state by 
// 0:draw, 1:finish by someone win the game and 2:game have not finished
int checkWinningState(char board[][7]) {
	int flag = 0, i, j;

/* To explain the following, first we should know that 'X'=88, 'O'=79 and '.'=46
 * then by solve the linear equation 46a+79b=88c and 46d+88e=79f
 * since we can find that there are no integer solution for d,e and the first integer solution of a,b are 88
 * so there are no linear combination that a,b,d,e are integer in this case(a+b<=4, d+e<=4)
 * then we can conclude that the only case is (4*88) % 88 = 0 and (4*79) % 79 = 0
 * therefore we can check the winning state by this constrain
 */
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 7; j++) {
			if (board[i][j] == 46)
				flag = 2;
		}
	}
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 4; j++) {
			if ((board[i][j] + board[i][j + 1] + board[i][j + 2] + board[i][j + 3]) % 88 == 0 || (board[i][j] + board[i][j + 1] + board[i][j + 2] + board[i][j + 3]) % 79 == 0)
				flag = 1;
		}
	}
	for (i = 0; i < 3; i++)	{
		for (j = 0; j < 7; j++) {
			if ((board[i][j] + board[i + 1][j] + board[i + 2][j] + board[i + 3][j]) % 88 == 0 || (board[i][j] + board[i + 1][j] + board[i + 2][j] + board[i + 3][j]) % 79 == 0)
				flag = 1;
		}
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 4; j++) {
			if ((board[i][j] + board[i + 1][j + 1] + board[i + 2][j + 2] + board[i + 3][j + 3]) % 88 == 0 || (board[i][j] + board[i + 1][j + 1] + board[i + 2][j + 2] + board[i + 3][j + 3]) % 79 == 0)
				flag = 1;
		}
	}
	for (i = 3; i < 6; i++) {
		for (j = 0; j < 4; j++) {
			if ((board[i][j] + board[i - 1][j + 1] + board[i - 2][j + 2] + board[i - 3][j + 3]) % 88 == 0 || (board[i][j] + board[i - 1][j + 1] + board[i - 2][j + 2] + board[i - 3][j + 3]) % 79 == 0)
				flag = 1;
		}
	}

	return flag;
}

// the main function is the process for the game
int main() {
	const int R = 6, C = 7;
	char board[R][C];
	char p = 'O';
	int check[7] = { 0 };	// for checking the column position
	int pos, state=2;

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			board[i][j] = '.';
		}
	}
	displayBoard(board);
	while (state == 2) {
		p = 'X' + 'O' - p;	// turn change
		cout << "Player " << p << ", make your move (0-6): ";
		cin >> pos;
		while (checkInput(check, pos) == 1 || pos < 0 || pos > 6) {
			if (checkInput(check, pos) == 1) {
				cout << "Column full. Try again!\nPlayer " << p << ", make your move (0-6): ";
				cin >> pos;
			}
			else {
				cout << "Invalid move. Try again!\nPlayer " << p << ", make your move (0-6): ";
				cin >> pos;
			}
		}
		updateBoard(board, check, pos, p);
		check[pos]++;
		displayBoard(board);
		state = checkWinningState(board);
	}
	if (state == 0)
		cout << "Draw game!\n";
	else
		cout << "Player " << p << " wins!\n";	// since this is a normal play rule impartial game,
												// the winner can only be the one who make the final move
	return 0;
}