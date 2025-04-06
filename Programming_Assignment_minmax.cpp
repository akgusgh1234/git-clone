#include<iostream>
#include<cmath>
#include<bitset>
#include<vector>
using namespace std;

void minterm(int N,char var[]) {
	int total = pow(2, N); 
	string min[1024];
	for (int i = 0; i < total; i++) {
		string current_term;
		bitset<10> binary(i); 

		for (int j = N - 1; j >= 0; j--) { 
			if (binary[j] == 0) {
				current_term += var[N - 1 - j];
				current_term += "'";
			}
			else {
				current_term += var[N - 1 - j];
			}
		}
		min[i] = current_term;
		
	}
	cout << "Enters the list of minterm numbers (ends for -1): ";
	vector<int> minterms;
	int a;
	
	while (cin >> a) {
		if (a == -1) {
			break;
		}
		if (a >= 0 && a < total) {
			minterms.push_back(a);
		}
		else {
			cout << "Invalid minterm number. Try again." << endl;
		}
	}
	if (!minterms.empty()) {
		cout << "(Output) F = ";
		for (size_t i = 0; i < minterms.size(); ++i) {
			if (i != 0) {
				cout << " + ";  
			}
			cout << min[minterms[i]];
		}
		cout << endl;
	}
	else {
		cout << "No valid minterms entered." << endl;
	}
}

void maxterm(int N, char var[]) {
	int total = pow(2, N);
	string max[1024];

	for (int i = 0; i < total; i++) {
		string current_term;
		bitset<10> binary(i);

		for (int j = N - 1; j >= 0; j--) {
			if (binary[j] == 0) {
				current_term += var[N - 1 - j];
			}
			else {
				current_term += var[N - 1 - j];
				current_term += "'";
			}
		}
		max[i] = current_term;
	}

	cout << "Enters the list of maxterm numbers (ends for -1): ";
	vector<int> maxterms;
	int a;

	while (cin >> a) {
		if (a == -1) {
			break;
		}
		if (a >= 0 && a < total) {
			maxterms.push_back(a);
		}
		else {
			cout << "Invalid maxterm number. Try again." << endl;
		}
	}

	if (!maxterms.empty()) {
		cout << "(Output) F = ";
		for (size_t i = 0; i < maxterms.size(); ++i) {
			cout << "(";
			string current_maxterm = max[maxterms[i]];
			for (size_t j = 0; j < current_maxterm.size(); ) {
				if (j != 0) {
					cout << " + ";
				}
				cout << current_maxterm[j];
				if (j + 1 < current_maxterm.size() && current_maxterm[j + 1] == '\'') {
					cout << "'";
					j += 2;
				}
				else {
					j += 1;
				}
			}
			cout << ")";
		}
		cout << endl;
	}
	else {
		cout << "No valid maxterms entered." << endl;
	}
}

int main() {
	char var[10];
	int N;
	int isMinorMax;
	do {
		cout << "Enter N: "; cin >> N;
		if (N > 10) {
			cout << "The maximum is 10" << endl;
		}
		if (N < 1) {
			cout << "Enter nature number" << endl;
		}

	} while (N > 10);
	cout << "Enter " << N << " alphabets: ";
	for (int i = 0; i < N; i++) {
		cin >> var[i];
	}
	cout << "Select Minterm or Maxterm (0: Minterm, 1: Maxterm): ";
	
	while (cin >> isMinorMax) {
		switch (isMinorMax)
		{
		case 0:
			minterm(N, var);
			break;
		case 1:
			maxterm(N, var);
			break;
		default:
			cout << "Please enter 0 or 1"<<endl;
			cout << "Select Minterm or Maxterm (0: Minterm, 1: Maxterm): ";
			continue;
		}
		break;
	}
	
}