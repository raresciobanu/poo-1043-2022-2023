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
	string telefon = "0789 079 879";


	//constr. default
	Student() :ID_MATRICOL(499) {
		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");

		this->gen = FEMEIE;

		this->varsta = 23;
		this->telefon = "0786 078 968";

		this->nrNote = 0;
		this->note = nullptr;
	}

	Student(int idMatricol, GEN gen, int nrNote, double* note,
		const char* nume, int varsta, string telefon) :ID_MATRICOL(idMatricol) {
		this->gen = gen;

		this->nrNote = nrNote;


		this->note = new double[nrNote];
		for (int i = 0; i < nrNote; i++) {
			this->note[i] = note[i];
		}

		this->nume = new char[strlen(nume) + 1];
		strcpy_s(this->nume, strlen(nume) + 1, nume);
	}

	Student(GEN gen, int nrNote, double* note) :ID_MATRICOL(222) {
		this->gen = gen;

		this->nrNote = nrNote;


		this->note = new double[nrNote];
		for (int i = 0; i < nrNote; i++) {
			this->note[i] = note[i];
		}

		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
	}

	void afisare() {
		cout << "ID matricol: " << ID_MATRICOL << endl;
		cout << "nume: " << nume << endl;
		cout << "varsta: " << varsta << endl;
		cout << "telefon: " << telefon << endl;
		cout << "gen: " << gen << endl;
		cout << "nrNote: " << nrNote << endl;
		cout << "note: ";
		for (int i = 0; i < nrNote; i++) {
			cout << note[i] << " ";
		}

		cout << endl << endl;
	}

	int getIdMatricol() {
		return ID_MATRICOL;
	}

	char* getNume() {
		return nume;
	}

	int getVarsta() {
		return varsta;
	}

	string getTelefon() {
		return telefon;
	}

	GEN getGen() {
		return gen;
	}

	int getNrNote() {
		return nrNote;
	}

	double* getNote() {
		return note;
	}
};

void main() {
	Student s1, s2;
	s1.telefon = "0797 879 333";

	double note1[2] = { 7.7,9.3 };
	Student s3(1000, BARBAT, 2, note1, "Popescu Vasile", 23, "0787 797 686");

	double note2[3] = { 6.5, 5.5, 8.6 };
	Student s4(FEMEIE, 3, note2);

	s1.afisare();

	s2.afisare();
	s3.afisare();
	s4.afisare();


	cout << s4.getIdMatricol() << " "<<s4.nume<< endl;
}