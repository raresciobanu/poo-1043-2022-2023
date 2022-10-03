#include<iostream>

using namespace std;

typedef struct {
	int varsta;
	char nume[100];
	double salariu;
} angajat;

void main() {
	angajat a;

	//a.nume[0] = 'I';
	//a.nume[1] = 'o';
	//a.nume[2] = 'n';
	//a.nume[3] = ' ';
	//a.nume[4] = 'P';
	//a.nume[5] = 'o';
	//a.nume[6] = 'p';
	//a.nume[7] = 'e';
	//a.nume[8] = 's';
	//a.nume[9] = 'c';
	//a.nume[10] = 'u';
	//a.nume[10] = '\0';

	strcpy_s(a.nume, "Ion Popescu");
	a.salariu = 2555.66;
	a.varsta = 30;

	cout << "Nume = " << a.nume << " Salariu = " << a.salariu << " Varsta = " << a.varsta << endl;



	int x = 66;
	cout << "Adresa VARIABILEI X este: " << &x << endl;

	cout << "================\n\n";

	int* px = &x; //acest pointer px va pointa catre o variabila de pe stack -> NU AI VOIE sa o dezaloci!
	cout << "Adresa variabilei pointer PX este: " << &px << endl;

	cout << "Valoarea lui PX este: " << px << endl;

	cout << "Ce se afla la adresa valorii pointer-ului PX: " << *px << endl; //indirectare


	int* py = new int(20);//se creaza pe heap o zona de memorie ce contine variabila 20
	cout << "valoarea din variabila py" << py << endl;
	cout << "py = " << *py << endl;
	delete py;


	//vectori

	int k[100];

	cout << "afisare adresa vector k = " << &k << endl;
	cout << "afisare adresa k[0] = " << &k[0] << endl;
}