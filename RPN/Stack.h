

class Stack {
public:
	Stack();
	void push(int e);
	int pop();
	int getDepth();
	bool isEmpty();
private:
	int elements[200];
	int count;
};