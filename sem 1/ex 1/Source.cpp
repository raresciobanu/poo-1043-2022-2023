#include<iostream>

using namespace std;


void fct1(int a, int b) {
	cout << "a = " << a << " b = " << b << endl;
}

void fct2(int a, int b) {

	cout << "a = " << a << " b = " << b << endl;

	a = 200;
	b = 300;
}

void fct3(int& c, int& d) {

	cout << "c = " << c << " d = " << d << endl;

	c = 900;
	d = 1100;
}


double suma(double a, int b) {
	return a + b;
}

void main() {
	cout << "merge" << "\n";


	int a = 40, b = 33;
	fct1(a, b);

	fct2(a, b);
	cout << "a = " << a << " b = " << b << endl;

	fct3(a, b);
	cout << "a = " << a << " b = " << b << endl;

}