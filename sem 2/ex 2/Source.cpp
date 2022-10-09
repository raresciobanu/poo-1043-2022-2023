#include<iostream>
#include<string>

using namespace std;

enum GEN { FEMEIE, BARBAT = 3, NECUNOSCUT = 20 };

//private/protected/public
class Student {
	//by default totul e private de aici in jos
	const int ID_MATRICOL;
	GEN gen;

	int nrNote;
	double* note;
public:
	char* nume;
	int varsta = 22;
	string nume = "Ion Popescu";
	

	//constr. default
	Student() :ID_MATRICOL(200){
		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
	}

};