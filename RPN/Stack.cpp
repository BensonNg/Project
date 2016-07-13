/* CSCI1520
* Assignment:6
* Student ID:1155034528
* Name      :Ng Yin Hei
* E-mail adr:bensonyongvanich@gmail.com
*/

#include <iostream>
#include <cstdlib>
#include "Stack.h"
using namespace std;

//Constructor of empty stack
Stack::Stack() {
	count = 0;
}

//Push the element into the stack
void Stack::push(int e) {
	if (count == 200) {
		cout << "Stack full! Program exit.\n";
		exit(1);
	}
	elements[count] = e;							//count should add after element writing since count is start from 0
	count += 1;
}

//Pop out the top elememt of the stack
int Stack::pop() {
	if (isEmpty()) {
		cout << "Stack empty! Programe exit.\n";
		exit(1);
	}
	count -= 1;										//since count == 0 is the above case, count never be non-positive here
	int p = elements[count];						//before pop the element the count should -1
	return p;										//since in pushthe count is add after element writing
}

//Return the depth of the stack
int Stack::getDepth() {
	return count;
}

//Return true for empty and false for non-empty
bool Stack::isEmpty() {								//if count == 0 => false, empty    => !count true
	return !count;									//if count != 0 => true, non-empty => !count false
}