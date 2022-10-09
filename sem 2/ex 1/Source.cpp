#include<iostream>

using namespace std;

void  afisare(int x, float* y) {
	cout << x << " ";
	if (y == nullptr) {
		cout << "nullptr\n";
	}
}

void main() {
	cout << "Sem 2\n";

	const int t = 200;

	int x = 10, y = 100, z = 1000;

	//pointer constant la o zona de memorie
	int* const xp = &x;

	*xp = 333;

//	xp = &y; //eroare
	

	//pointer la o zona de memorie constanta
	const int* xp2 = &x;

	xp2 = &y;
	//*xp2 = 1000;//error


	//pointer constant la o zona de memorie constanta

	const int* const xp3 = &x;

	/*xp3 = &z;
	*xp3 = 200;*/ 
	
	afisare(NULL, nullptr);


	int** matrice = new int* [2];
	for (int i = 0; i < 2; i++) {
		matrice[i] = new int[3];
		for (int j = 0; j < 3; j++) {
			matrice[i][j] = i * j + 1;
		}
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			cout << matrice[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < 2; i++) {
		delete[] matrice[i];
	}

	delete[] matrice;
}