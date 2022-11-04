#include<iostream>
#include<string>

using namespace std;

enum GEN { FEMEIE, BARBAT = 3, NECUNOSCUT = 20 };

//private/protected/public
class Student {
	//by default totul e private de aici in jos
	const int ID_MATRICOL;
	GEN gen;

protected:
	int nrNote;
	double* note;
public:
	char* nume;
	int varsta = 22;
	string telefon = "0789 079 879";
	static string universitate;

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

		this->varsta = varsta;
		this->telefon = telefon;

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

	Student(const Student& s) :ID_MATRICOL(s.ID_MATRICOL) {
		this->gen = s.gen;

		this->nrNote = s.nrNote;

		this->varsta = s.varsta;
		this->telefon = s.telefon;

		this->note = new double[s.nrNote];
		for (int i = 0; i < s.nrNote; i++) {
			this->note[i] = s.note[i];
		}

		this->nume = new char[strlen(s.nume) + 1];
		strcpy_s(this->nume, strlen(s.nume) + 1, s.nume);
	}

	//operatori
	//op =
	//s2=s2  s6=s10
	Student& operator=(const Student& s) {
		if (this != &s) {
			this->gen = s.gen;

			this->nrNote = s.nrNote;

			this->varsta = s.varsta;
			this->telefon = s.telefon;

			if (this->note != nullptr) {
				delete[] this->note;
			}

			this->note = new double[s.nrNote];
			for (int i = 0; i < s.nrNote; i++) {
				this->note[i] = s.note[i];
			}

			if (this->nume != nullptr) {
				delete[] this->nume;
			}

			this->nume = new char[strlen(s.nume) + 1];
			strcpy_s(this->nume, strlen(s.nume) + 1, s.nume);
		}

		return *this;
	}

	~Student() {
		if (this->note != nullptr) {
			delete[] this->note;
		}

		if (this->nume != nullptr) {
			delete[] this->nume;
		}
	}

	void afisare() {
		cout << "ID matricol: " << ID_MATRICOL << endl;
		cout << "nume: " << nume << endl;
		cout << "varsta: " << varsta << endl;
		cout << "telefon: " << telefon << endl;
		cout << "gen: " << gen << endl;
		cout << "universitate: " << universitate << endl;

		cout << "nrNote: " << nrNote << endl;
		cout << "note: ";
		for (int i = 0; i < nrNote; i++) {
			cout << note[i] << " ";
		}

		cout << endl << endl;
	}

	//getteri

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

	string getUniversitate() {
		return universitate;
	}

	// setteri
	void setNume(const char* nume) {
		if (nume != nullptr) {
			delete[] this->nume;  //pt a evita memory leaks

			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else {
			throw new exception("numele primit ca input este null"); //arunci un pointer ce pointeaza catre un obiect de tip exception
		}
	}

	void setVarsta(int varsta) {
		if (varsta < 0) {
			throw new exception("varsta nu poate fi mai mica ca 0");
		}
		else {
			this->varsta = varsta;
		}
	}

	void setTelefon(string telefon) {
		if (telefon.empty()) {
			throw new exception("inputul trimis are 0 caractere");
		}

		if (telefon.length() < 10) {
			throw new exception("inputul trimis are mai putin de 10 caractere");
		}

		this->telefon = telefon;
	}

	void setGen(GEN gen) {
		if (gen == NECUNOSCUT) {
			throw new exception("genul unui student nu poate fi necunoscut");
		}

		this->gen = gen;
	}

	void setNrNote(int nrNote) {
		if (nrNote < 0) {
			throw new exception("nrNote nu poate fi mai mic ca 0");
		}
		else {
			this->nrNote = nrNote;
		}
	}

	void setNote(double* note, int nrNote) {
		if (note == nullptr || nrNote < 0) {
			throw new exception("inputul este gresit");
		}
		else {
			this->nrNote = nrNote;

			delete[] this->note; //pt a evita memory leaks

			this->note = new double[nrNote];
			for (int i = 0; i < nrNote; i++) {
				this->note[i] = note[i];
			}
		}
	}

	void setUniversitate(string universitate) {
		if (universitate.length() < 2) {
			throw new exception("universitate trebuie sa aiba minim 2 caractere");
		}

		this->universitate = universitate;
	}

	friend double calculeazaMedieStudent(const Student& s);
	friend ostream& operator<<(ostream& out, const Student& s);
	friend istream& operator>>(istream& in, Student& s);

	//operatori
	//op. unari 
	//op. ++ - pre-incrementare
	const Student& operator++() {
		varsta++;

		return *this;
	}

	//op. ++ - post-incrementare
	const Student operator++(int) {
		Student aux(*this);

		varsta++;


		return aux;
	}

	//op binari
	//op. + (ex: cout<<s5+2;)
	int operator+(int x) {
		return varsta + x;
	}

	//op. +  (ex: cout<<s4+s3;)
	Student operator+(const Student& student) {
		Student aux(*this);

		aux.telefon = aux.telefon + " al doilea numar: " + student.telefon;

		return aux;
	}

	//op. + (ex: cout<<10+s3;)
	friend int operator+(int x, const Student& student);

	//op += (s5+=3;)
	void operator+=(int x) {
		varsta += x;
	}

	//op !
	//if(!s4){//fa ceva};
	bool operator!() {
		return nrNote > 0;
	}


	//op ==
	//if(s3==s6){//fa ceva}
	bool operator==(Student& s) {
		if (this == &s) {
			return true;
		}

		bool sameFields = strcmp(this->nume, s.nume) == 0 &&
			this->telefon == s.telefon &&
			this->varsta == s.varsta &&
			this->gen == s.gen &&
			this->nrNote == s.nrNote;

		if (sameFields == true) {
			for (int i = 0; i < nrNote; i++) {
				if (this->note[i] != s.note[i]) {
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}

	//op functie ()
	void operator()(int valoare) {
		if (valoare >= 1 && valoare <= 3) {
			for (int i = 0; i < nrNote; i++) {
				if (this->note[i] + valoare <= 10)
					this->note[i] += valoare;
			}
		}
		else {
			throw new exception("Eroare: valoare < 1 sau valoare >3");
		}
	}

	//op index[]
	//cout<<s6[2];
	double& operator[](int index) {
		if (index >= 0 && index < nrNote) {
			return note[index];
		}
		else {
			throw new exception("Eroare: index < 0 sau index > nrNote");
		}
	}

	//operator cast - implicit sau explicit
	operator int() {
		return varsta;
	}
};

string Student::universitate = "ASE";

GEN getGENByString(string value) {
	if (value == "FEMEIE" || value == "femeie") {
		return FEMEIE;
	}
	else if (value == "BARBAT" || value == "barbat") {
		return BARBAT;
	}
	else {
		return NECUNOSCUT;
	}
}

ostream& operator<<(ostream& out, const Student& s) {
	out << "ID matricol: " << s.ID_MATRICOL << endl;
	out << "nume: " << s.nume << endl;
	out << "varsta: " << s.varsta << endl;
	out << "telefon: " << s.telefon << endl;
	out << "gen: " << s.gen << endl;
	out << "universitate: " << s.universitate << endl;

	out << "nrNote: " << s.nrNote << endl;
	out << "note: ";
	for (int i = 0; i < s.nrNote; i++) {
		out << s.note[i] << " ";
	}

	out << endl << endl;

	return out;
}


istream& operator>>(istream& in, Student& s) {
	cout << "Introdu date despre student:\n";

	char aux[100];

	cout << "nume = "; in.getline(aux, 100);
	delete[] s.nume;  //pt a evita memory leaks

	s.nume = new char[strlen(aux) + 1];
	strcpy_s(s.nume, strlen(aux) + 1, aux);

	cout << "varsta = "; in >> s.varsta;

	in.ignore();//golire buffer

	cout << "telefon = "; in.getline(aux, 100);
	s.telefon = aux;


	cout << "gen = "; in >> aux;
	s.gen = getGENByString(aux);

	cout << "nrNote = "; in >> s.nrNote;

	delete[] s.note;  //pt a evita memory leaks
	s.note = new double[s.nrNote];

	cout << "NOTE:\n";
	for (int i = 0; i < s.nrNote; i++) {
		cout << "note[" << i << "] = "; in >> s.note[i];
	}

	return in;
}

//op. + (ex: cout<<10+s3;)
int operator+(int x, const Student& student) {
	return x + student.varsta;
}


double calculeazaMedieStudent(const Student& s) {
	double medie = 0.0;

	for (int i = 0; i < s.nrNote; i++) {
		medie += s.note[i];
	}

	return medie;
}


//polimorfism = supraincarcare si suprascriere
int suma(int a, int b) {
	return a + b;
}

int suma(int a, int b, double c) {
	return a + b + c;
}

double suma(int a, double b) {
	return a + b;
}


void main() {
	Student s1, s2;
	s1.telefon = "0797 879 333";

	double note1[2] = { 7.7,9.3 };
	Student s3(1000, BARBAT, 2, note1, "Popescu Vasile", 23, "0787 797 686");
	s3.setNume("Rares");


	double note2[3] = { 6.5, 5.5, 8.6 };
	Student s4(FEMEIE, 3, note2);

	s1.afisare();

	s2.afisare();
	s2.universitate = "POLI";


	s3.afisare();
	s3.setGen(FEMEIE);
	s3.setVarsta(33);
	s3.setNume("Maria Popescu");

	double note3[5] = { 6.5, 5.5, 8.6, 10, 9.3 };
	s3.setNote(note3, 5);
	s3.setTelefon("0764 044 666");

	s3.afisare();

	s4.afisare();


	cout << s4.getIdMatricol() << " " << s4.nume << endl;

	Student s5(s4); //constr copiere
	Student s6 = s4; //constr copiere
	Student s7;
	s7 = s4; //op egal


	cout << s7 << endl << endl;

	//cin >> s7;

	cout << endl << endl << s7 << endl << endl;


	///operatori

	//operator ++ pre-incrementare
	cout << ++s6 << endl << endl;


	//operator ++ post-incrementare
	cout << s6++ << endl << endl;

	//op +
	cout << s6 + 10 << endl << endl;

	//op +
	cout << 3 + s6 << endl << endl;

	//op +
	cout << s6 + s2 << endl << endl;

	//op +=
	s6 += 1;
	cout << s6 << endl << endl;

	//verifica daca s4 are note
	if (!s4) {
		cout << s4 << "\n\n";
	}
	else {
		cout << "s4 nu are valori in vectorul note\n\n";
	}

	//op ==
	if (s3 == s6) {
		cout << "s3==s6" << endl << endl;
	}
	else {
		cout << "s3!=s6" << endl << endl;
	}

	// op ()
	s6(2);
	cout << "op functie:\n" << s6 << endl << endl;

	//op []
	cout << s6[2] << endl << endl;

	//op cast explicit
	cout << "(int)s6=" << (int)s6 << endl << endl;

	//op cast implicit
	int varsta = s6;
	cout << "varsta=" << varsta << endl << endl;
}