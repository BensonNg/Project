/* CSCI1520
* Assignment:3
* Student ID:1155034528
* Name      :Ng Yin Hei
* E-mail adr:bensonyongvanich@gmail.com
*/

#include <iostream>
using namespace std;

int main() {
	int n, a, mgno, turn, s;

	a = 1;	//initiate the game
	while (a == 1){
		cout << "How many player? ";
		cin >> n;
		while (n < 2) {
			cout << "At least 2 player. Enter again!\nHow many player? ";
			cin >> n;
		}
		cout << "Enter a magic number: ";
		cin >> mgno;
		while (mgno < 5 * n) {
			cout << "Magic number must be at least " << 5 * n << ". Enter again!\nEnter a magic number: ";
				cin >> mgno;
		}
		turn = -1;	//make the start turn for player 1
		while (mgno > 0) {
			turn = (turn + 1) % n;	//set cyclo loop of {0, ... ,n-1}
			cout << "Player " << turn + 1 << ", make your call (1-3): ";	//turn + 1 change loop from {0, ..., n-1} to {1, ..., n}
				cin >> s;
			while (s != 1 && s != 2 && s != 3) {
				cout << "Calls must be 1-3. Enter again!\nPlayer " << turn + 1 << ", make your call (1-3): ";
					cin >> s;
			}
			mgno -= s;
			if (mgno > 0)
			cout << "Magic number is now " << mgno << endl;
		}
		cout << "Bomb! Player " << turn + 1 << " loses!\nPlay again (1=Yes)? ";
		cin >> a;
	}
	cout << "Bye!\n";
	return 0;
}