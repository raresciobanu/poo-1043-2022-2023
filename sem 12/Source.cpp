#include<iostream>
#include<fstream>

using namespace std;

//inferfata -> este o clasa ce contine DOAR fct virtuale pure
//clasa abstracta -> este o clasa ce contine cel putin o fct virtuala pura
//clasele abstracte nu mai pot fi instantiate ca obiecte
//clase abstracte - todo sapt 13 pe alt exemplu

class InterfataElectrocasnice {
	virtual int durataGarantieLuni() = 0;//fct virtuala pura
};

class ExceptieCustom : public exception { //faceti mostenirea publica altfel nu o sa mearga polimorfismul
	string message;
public:
	ExceptieCustom(string message) {
		this->message = message;
	}

	string mesajEroare() {
		return this->message;
	}


	char const* what() const {
		return this->message.c_str();//c_str() transforma un string in sir de caractere
	}
};

class Review {
	const int id_Review;
	string mesaj;

	static int counter;

public:
	Review() :id_Review(counter++) {
		this->mesaj = "No info.";
	}

	Review(const int id_Review, string mesaj) :id_Review(id_Review) {
		this->mesaj = mesaj;
	}

	Review(const Review& review) :id_Review(review.id_Review) {
		this->mesaj = review.mesaj;
	}

	Review& operator=(const Review& review) {
		if (this != &review) {
			this->mesaj = review.mesaj;
		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, const Review& review) {
		out << "Review with ID ";
		out << review.id_Review << " : " << review.mesaj << endl;

		return out;
	}

	friend ofstream& operator<<(ofstream& out, const Review& review) {
		out << review.id_Review << endl << review.mesaj << endl;

		return out;
	}

	friend istream& operator>>(istream& in, Review& review) {
		cout << "Mesaj : ";
		char aux[300];
		in.getline(aux, 300);

		review.mesaj = aux;

		return in;
	}

	friend ifstream& operator>>(ifstream& in, Review& review) {
		char aux[300];
		in.getline(aux, 300);

		review.mesaj = aux;

		return in;
	}


	void scrieInFisierBinar(ofstream& fisBinarOut) {
		fisBinarOut.write((char*)&this->id_Review, sizeof(this->id_Review)); //tu ai un pointer de tip char CE are ca VALOARE adresa lui this->id_Review

		//string
		//pentru a scrie char* si string intr un fisier binar trebuie intai sa scriem ce dimensiune au pentru a sti la citire cand sa ne oprim
		int dim = mesaj.size() + 1; //+1 - pt '\0' de la finalul unui sir de caractere

		//fct write - compilatorul trebuie sa stie la CE adresa sa se uite in memorie si cat sa citeasca
		fisBinarOut.write((char*)&dim, sizeof(dim)); //tu ai un pointer de tip char CE are ca VALOARE adresa lui dim....
		fisBinarOut.write(this->mesaj.c_str(), dim); //aici nu mai e sizeof, pt ca ai calculat deja dimensiunea string-ului
	}

	void citireDinFisierBinar(ifstream& fisBinarIn) {
		fisBinarIn.read((char*)&id_Review, sizeof(id_Review));

		int dim = 0;
		fisBinarIn.read((char*)&dim, sizeof(dim));

		char aux[200];
		fisBinarIn.read(aux, dim);
		this->mesaj = aux;
	}
};

int Review::counter = 1;

class Electrocasnice :InterfataElectrocasnice {
protected:
	string clasa;
	float pret;
	char* marca;

	//Electrocasnice has A vector of Review - compunere
	Review* reviews;
	int nrReviews;

public:

	Electrocasnice() {
		this->clasa = "A+";
		this->pret = 1000.99;

		this->marca = new char[strlen("LG") + 1];
		strcpy(this->marca, "LG");

		this->nrReviews = 0;
		this->reviews = nullptr;
	}

	Electrocasnice(string clasa, float pret, const char* marca, Review* reviews, int nrReviews) {
		this->clasa = clasa;

		this->pret = pret;

		this->marca = new char[strlen(marca) + 1];
		strcpy(this->marca, marca);

		this->nrReviews = nrReviews;

		this->reviews = new Review[nrReviews];
		for (int i = 0; i < nrReviews; i++) {
			this->reviews[i] = reviews[i];
		}
	}

	Electrocasnice(const Electrocasnice& electrocasnice) {
		this->clasa = electrocasnice.clasa;

		this->pret = electrocasnice.pret;

		this->marca = new char[strlen(electrocasnice.marca) + 1];
		strcpy(this->marca, electrocasnice.marca);

		this->nrReviews = electrocasnice.nrReviews;

		this->reviews = new Review[electrocasnice.nrReviews];
		for (int i = 0; i < electrocasnice.nrReviews; i++) {
			this->reviews[i] = electrocasnice.reviews[i];
		}
	}

	Electrocasnice& operator=(const Electrocasnice& electrocasnice) {
		if (this != &electrocasnice) {
			//dezalocare memorie pt a evita memory leaks
			delete[] this->reviews;
			delete[] this->marca;

			this->clasa = electrocasnice.clasa;

			this->pret = electrocasnice.pret;

			this->marca = new char[strlen(electrocasnice.marca) + 1];
			strcpy(this->marca, electrocasnice.marca);

			this->nrReviews = electrocasnice.nrReviews;

			this->reviews = new Review[electrocasnice.nrReviews];
			for (int i = 0; i < electrocasnice.nrReviews; i++) {
				this->reviews[i] = electrocasnice.reviews[i];
			}
		}

		return *this;
	}

	~Electrocasnice() {
		if (this->reviews != nullptr) {
			delete[] this->reviews;
		}

		if (this->marca != nullptr) {
			delete[] this->marca;
		}
	}

	friend ostream& operator<<(ostream& out, const Electrocasnice& electrocasnic) {
		out << "Clasa : " << electrocasnic.clasa << " Pret : " << electrocasnic.pret
			<< " Marca : " << electrocasnic.marca << " Nr reviews : " << electrocasnic.nrReviews << endl;
		for (int i = 0; i < electrocasnic.nrReviews; i++) {
			out << electrocasnic.reviews[i];
		}


		return out;
	}

	friend ofstream& operator<<(ofstream& out, const Electrocasnice& electrocasnic) {
		out << electrocasnic.clasa << endl << electrocasnic.pret << endl << electrocasnic.marca << endl << electrocasnic.nrReviews << endl;
		for (int i = 0; i < electrocasnic.nrReviews; i++) {
			out << electrocasnic.reviews[i] << endl;
		}

		return out;
	}

	friend istream& operator>>(istream& in, Electrocasnice& electrocasnic) {
		cout << "Electrocasnic\n";

		cout << "Clasa : ";
		char aux[300];
		in >> aux;
		electrocasnic.clasa = aux;

		cout << "Pret : ";
		in >> electrocasnic.pret;

		in.ignore();

		cout << "Marca : ";
		in >> aux;

		delete[] electrocasnic.marca;
		electrocasnic.marca = new char[strlen(aux) + 1];
		strcpy(electrocasnic.marca, aux);


		cout << "Nr reviews : ";
		in >> electrocasnic.nrReviews;

		in.ignore();

		cout << "Reviews : ";
		delete[] electrocasnic.reviews;
		electrocasnic.reviews = new Review[electrocasnic.nrReviews];
		for (int i = 0; i < electrocasnic.nrReviews; i++) {
			in >> electrocasnic.reviews[i];
		}

		return in;
	}

	friend ifstream& operator>>(ifstream& in, Electrocasnice& electrocasnic) {
		char aux[300];
		in >> aux;
		electrocasnic.clasa = aux;

		in >> electrocasnic.pret;

		in.ignore();

		in >> aux;

		delete[] electrocasnic.marca;
		electrocasnic.marca = new char[strlen(aux) + 1];
		strcpy(electrocasnic.marca, aux);

		in >> electrocasnic.nrReviews;

		in.ignore();

		delete[] electrocasnic.reviews;
		electrocasnic.reviews = new Review[electrocasnic.nrReviews];
		for (int i = 0; i < electrocasnic.nrReviews; i++) {
			in >> electrocasnic.reviews[i];
		}

		return in;
	}

	void setClasa(string clasa) {
		if (clasa.size() <= 1) {
			throw new exception("clasa trebuie sa aiba minim 2 caractere");
		}
		else if (strcmp(clasa.c_str(), "BB") == 0) {
			throw exception("clasa nu poate fi valoarea BB");
		}
		else if (strcmp(clasa.c_str(), "CC") == 0) {
			throw - 100;
		}
		else if (clasa.length() > 10) {
			throw new ExceptieCustom("clasa nu poate sa aiba mai mult de 10 caractere");
		}
	}

	void adaugReviewInVector(const Review& review) {
		Review* paux = new Review[nrReviews + 1];

		for (int i = 0; i < nrReviews; i++) {
			paux[i] = reviews[i];
		}

		paux[nrReviews] = review;
		nrReviews++;

		delete[] reviews;//evita memory leaks

		reviews = paux;
	}

	//sau poti sa faci ce ai facut in functia de mai sus cu un operator(posibil sa fie la examen)
	void operator+=(const Review& review) {
		Review* paux = new Review[nrReviews + 1];

		for (int i = 0; i < nrReviews; i++) {
			paux[i] = reviews[i];
		}

		paux[nrReviews] = review;
		nrReviews++;

		delete[] reviews;//evita memory leaks

		reviews = paux;
	}

	void stergeUltimulElementDinVector() {
		Review* paux = new Review[nrReviews - 1];

		for (int i = 0; i < nrReviews - 1; i++) {
			paux[i] = reviews[i];
		}

		nrReviews--;

		delete[] reviews;//evita memory leaks

		reviews = paux;
	}

	//sau poti sa faci ce ai facut in functia de mai sus cu un operator(posibil sa fie la examen)
	//op. -- - post-decrementare
	const Electrocasnice operator--(int) {
		Electrocasnice aux(*this);


		Review* paux = new Review[nrReviews - 1];

		for (int i = 0; i < nrReviews - 1; i++) {
			paux[i] = reviews[i];
		}

		nrReviews--;

		delete[] reviews;//evita memory leaks

		reviews = paux;

		return aux;
	}

	//todo faceti voi acasa celelalte 2 stergeri

	virtual int durataDeViata() {
		return 2;
	}

	int durataGarantieLuni() {
		return 12;
	}

	void scrieInFisierBinar(ofstream& fisBinarOut) {
		int dim = this->clasa.size() + 1; //+1 - pt '\0' de la finalul unui sir de caractere

		//fct write - compilatorul trebuie sa stie la CE adresa sa se uite in memorie si cat sa citeasca
		fisBinarOut.write((char*)&dim, sizeof(dim)); //tu ai un pointer de tip char CE are ca VALOARE adresa lui dim....
		fisBinarOut.write(this->clasa.c_str(), dim); //aici nu mai e sizeof, pt ca ai calculat deja dimensiunea string-ului

		fisBinarOut.write((char*)&this->pret, sizeof(this->pret));


		dim = strlen(this->marca) + 1; //+1 - pt '\0' de la finalul unui sir de caractere

		//fct write - compilatorul trebuie sa stie la CE adresa sa se uite in memorie si cat sa citeasca
		fisBinarOut.write((char*)&dim, sizeof(dim)); //tu ai un pointer de tip char CE are ca VALOARE adresa lui dim....
		fisBinarOut.write(this->marca, dim); //aici nu mai e sizeof, pt ca ai calculat deja dimensiunea string-ului

		fisBinarOut.write((char*)&this->nrReviews, sizeof(this->nrReviews));

		for (int i = 0; i < nrReviews; i++) {
			this->reviews[i].scrieInFisierBinar(fisBinarOut);
		}
	}

	void citireDinFisierBinar(ifstream& fisBinarIn) {
		int dim = 0;
		fisBinarIn.read((char*)&dim, sizeof(dim));

		char aux[200];
		fisBinarIn.read(aux, dim);
		this->clasa = aux;

		fisBinarIn.read((char*)&this->pret, sizeof(this->pret));

		fisBinarIn.read((char*)&dim, sizeof(dim));//citesti marca
		fisBinarIn.read(aux, dim);

		delete[] this->marca;
		this->marca = new char[strlen(aux) + 1];
		strcpy(this->marca, aux);

		fisBinarIn.read((char*)&this->nrReviews, sizeof(this->nrReviews));

		delete[] this->reviews;
		this->reviews = new Review[this->nrReviews];
		for (int i = 0; i < nrReviews; i++) {
			this->reviews[i].citireDinFisierBinar(fisBinarIn);
		}
	}
};


//is A Electrocasnice - mostenire
class Televizor : public Electrocasnice {
	float diagonala;
	string tipEcran; //led / oled / qled / 4k /3d

public:

	Televizor() :Electrocasnice() {
		this->diagonala = 20.9;
		this->tipEcran = "led";
	}

	Televizor(float diagonala, string tipEcran) : Electrocasnice("A", 1000.55, "Samsung", nullptr, 0) {
		this->diagonala = diagonala;
		this->tipEcran = tipEcran;
	}

	Televizor(float diagonala, string tipEcran, string clasa, float pret, const char* marca, Review* reviews, int nrReviews)
		:Electrocasnice(clasa, pret, marca, reviews, nrReviews)
	{
		this->diagonala = diagonala;
		this->tipEcran = tipEcran;
	}

	Televizor(const Televizor& t) : Electrocasnice(t) {
		this->diagonala = t.diagonala;
		this->tipEcran = t.tipEcran;
	}

	~Televizor() {
		//nu avem ce sa dezalocam in copil
	}


	Televizor& operator=(const Televizor& t) {
		if (this != &t) {
			Electrocasnice::operator=(t);//aici apelezi op= din parinte

			this->diagonala = t.diagonala;
			this->tipEcran = t.tipEcran;
		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, const Televizor& t) {
		out << "Televizor:\nDiagonala : " << t.diagonala << " Tip ecran : " << t.tipEcran << endl;
		out << (Electrocasnice)t; //transformi copilul in parinte si automat << stie ca tu incerci sa afis. un parinte

		return out;
	}

	friend ofstream& operator<<(ofstream& out, const Televizor& t) {
		out << t.diagonala << endl << t.tipEcran << endl;
		out << (Electrocasnice)t; //transformi copilul in parinte si automat << stie ca tu incerci sa afis. un parinte

		return out;
	}

	friend istream& operator>>(istream& in, Televizor& t) {
		cout << "Citire televizor\n";
		cout << "Diagonala : "; in >> t.diagonala;

		in.ignore();

		char aux[300];
		cout << "Tip ecran : ";
		in.getline(aux, 300);

		t.tipEcran = aux;


		in >> (Electrocasnice&)t; //a refolosi op >> din parinte

		return in;
	}

	friend ifstream& operator>>(ifstream& in, Televizor& t) {
		in >> t.diagonala;

		in.ignore();

		char aux[300];
		in.getline(aux, 300);

		t.tipEcran = aux;

		in >> (Electrocasnice&)t; //a refolosi op >> din parinte

		return in;
	}

	int durataDeViata() {
		return 4;
	}

	int durataGarantieLuni() {
		return 24;
	}

	void scrieInFisierBinar(ofstream& fisBinarOut) {
		fisBinarOut.write((char*)&this->diagonala, sizeof(this->diagonala));

		int dim = this->tipEcran.size() + 1; //+1 - pt '\0' de la finalul unui sir de caractere

		//fct write - compilatorul trebuie sa stie la CE adresa sa se uite in memorie si cat sa citeasca
		fisBinarOut.write((char*)&dim, sizeof(dim)); //tu ai un pointer de tip char CE are ca VALOARE adresa lui dim....
		fisBinarOut.write(this->tipEcran.c_str(), dim); //aici nu mai e sizeof, pt ca ai calculat deja dimensiunea string-ului

		Electrocasnice::scrieInFisierBinar(fisBinarOut);
	}

	void citireDinFisierBinar(ifstream& fisBinarIn) {

		fisBinarIn.read((char*)&this->diagonala, sizeof(this->diagonala));

		int dim = 0;
		fisBinarIn.read((char*)&dim, sizeof(dim));

		char aux[200];
		fisBinarIn.read(aux, dim);//tipEcran
		this->tipEcran = aux;

		Electrocasnice::citireDinFisierBinar(fisBinarIn);
	}
};


//is A Electrocasnice - mostenire
class Frigider : Electrocasnice {
	//faceti voi acasa ceva asemanator ca si in clasa Televizor
};

//supraincarcare => acelasi nume de functie si parametri diferiti
//suprascriere => acelasi antet al functiei si implementare diferita ( mostenire )

void main() {
	Review r1, r2, r3, r4, r5;

	Review r6(1000, "Super bun!");
	Review r7(1001, "M-a ars la pret!");
	Review r8(1002, "Chinezarie!");


	//vector de reviews
	Review reviews1[3] = { r1,r2,r8 };
	Review reviews2[4] = { r3,r4,r6,r7 };

	//electrocasnice
	Electrocasnice e1("A+", 1899.99, "LG", reviews1, 3);
	Electrocasnice e2("G+", 2199.99, "Samsung", reviews2, 4);

	cout << e1 << endl << endl;

	cout << e2 << endl << endl;


	Televizor t1;
	//cin >> t1;
	cout << endl << endl << t1 << endl << endl;

	Televizor t2(100.6, "4k", "A+", 2000.99, "Huawei", reviews2, 4);
	cout << t2 << endl << endl;


	//test try catch

	try {
		t2.setClasa("C");

		t2.setClasa("CC");
	}
	catch (int x) {
		cout << x << endl;
	}
	catch (exception* e) {
		cout << e->what() << endl;
	}



	try {
		t2.setClasa("BB");
	}
	catch (exception e) {
		cout << e.what() << endl;
	}


	try {
		t2.setClasa("BB bbb bbb bbb bbb");
	}
	catch (exception* e) {
		//aici se arunca ExceptieCustom, dar se face upcasting si prin polimorfism este afisat mesajul din ExceptieCustom
		//(am suprascris in ExceptieCustom fct what() -> polimorfism
		cout << e->what() << endl;
	}


	cout << "early-binding : \n\n";
	//early-binding:
	Electrocasnice e3;
	Electrocasnice e4 = t2; //(upcasting -> transformi un copil in parinte)

	cout << "Durata de viata : " << e3.durataDeViata() << endl;
	cout << "Durata de viata : " << e4.durataDeViata() << endl << endl;


	cout << "late-binding : \n\n";
	//late-binding - folosim pointeri pt a demonstra acest concept
	Electrocasnice* pointerEl1 = new Televizor();
	Electrocasnice* pointerEl2 = new Televizor();
	Electrocasnice* pointerEl3 = new Televizor();
	Electrocasnice* pointerEl4 = new Electrocasnice();

	cout << "Durata de viata : " << pointerEl1->durataDeViata() << endl;

	cout << "Durata de viata : " << pointerEl4->durataDeViata() << endl << endl;


	cout << "polimorfism : \n\n";
	Electrocasnice** vectorDePointeri = new Electrocasnice * [4];
	vectorDePointeri[0] = pointerEl1;
	vectorDePointeri[1] = pointerEl2;
	vectorDePointeri[2] = pointerEl3;
	vectorDePointeri[3] = pointerEl4;

	for (int i = 0; i < 4; i++) {
		cout << "durataDeViata : " << vectorDePointeri[i]->durataDeViata() << endl;
		cout << "durataGarantieLuni : " << vectorDePointeri[i]->durataGarantieLuni() << endl;
	}



	//fisiere text si binare

	//flag-uri
	//ios::app - adauga informatii la un fisier existent sau il va crea daca nu exista
	//ios::nocreate - deschide fisierul daca exista deja.
	//ios::in - pt citire dintr-un fisier
	//ios::out - scriere intr-un fisier
	//ios::truc - sterge tot din fisier inainte sa scrii in el 
	//ios::noreplace - doar pt a crea un nou fisier
	//ios::ate - deschide fisierul si merge la sfarsitul lui - fol pt adaugare informatii la final
	//ios::binary - fisierul deschis va contine doar informatii binare
	ofstream fisierElectrocasniceTxtOut("fisierElectrocasnice.txt", ios::out);
	if (fisierElectrocasniceTxtOut.is_open()) {
		for (int i = 0; i < 4; i++) {
			fisierElectrocasniceTxtOut << *vectorDePointeri[i];
		}

		fisierElectrocasniceTxtOut.close();
	}
	else {
		cout << "Fisierul fisierElectrocasniceTxtOut.txt nu poate fi deschis pentru scriere.\n";
	}

	cout << endl << endl << "FISIERE" << endl << endl;

	ifstream fisierElectrocasniceTxtIn("fisierElectrocasnice.txt", ios::in);
	if (fisierElectrocasniceTxtIn.is_open()) {
		for (int i = 0; i < 4; i++) {
			Electrocasnice el1;
			fisierElectrocasniceTxtIn >> el1;

			cout << el1 << endl;
		}

		fisierElectrocasniceTxtIn.close();
	}
	else {
		cout << "Fisierul fisierElectrocasniceTxtIn.txt nu poate fi deschis pentru citire.\n";
	}



	ofstream fisBinarOut("wwww.bin", ios::out | ios::binary);
	if (fisBinarOut.is_open()) {
		e4.scrieInFisierBinar(fisBinarOut);

		fisBinarOut.close();
	}
	else {
		cout << "Fisierul wwww.dat nu poate fi deschis pentru scriere.\n";
	}

	Electrocasnice eeee;
	ifstream fisBinarIn("wwww.bin", ios::in | ios::binary);
	if (fisBinarIn.is_open()) {
		eeee.citireDinFisierBinar(fisBinarIn);

		cout << "eeee din fisier binar:   " << eeee << " ";
		fisBinarIn.close();
	}
	else {
		cout << "Fisierul wwww.dat nu poate fi deschis pentru citire.\n";
	}

	delete[] vectorDePointeri;
}