#include <iostream>
using namespace std;

//The function is the sample model of solving Knapsack Problem in dynamic programming

int max(int x, int y) {
	return x*(x>y)+y*(1-(x>y));
}


int main() {
	int i,j;
	const int k = 4,b = 10;
	int S[k+1][b+1]={0}, count[k]={0}, v[k]={1, 3, 5, 9}, w[k]={2, 3, 4, 7};

//policy determine
	int P[k+1][b+1]={0};
	for (i=1; i<k+1; i++)
		for (j=b; j>0; j-=w[i-1])
			P[i][j]=1;

//compare S(i,j)
	for (i=1; i<k+1; i++) {
		for (j=1; j<b+1; j++) {
			if (j-w[i-1]>=0)
				S[i][j]=max(S[i-1][j],S[i][j-w[i-1]]+v[i-1]);
			else
				S[i][j]=S[i-1][j];

		}
	}

//find route
	int tempb=b;
	for (i=k; i>0; i--) {
		for (j=tempb; j>=0; j-=w[i-1]) {
			if (S[i][j]==S[i-1][j]) {
				tempb=j;
				j=0;
			}
			else
				count[i-1]++;
		}
	}

//print out
	for (i=0; i<k+1; i++) {
		for (j=0; j<b+1; j++) {
			cout << S[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl << "Maximum value is: " << S[k][b] << endl;
	for (i=0; i<k; i++) {
		if (count[i] !=0)
			cout << "Type " << i+1 << ": " << count[i] << endl;
	}

	return 0;
}