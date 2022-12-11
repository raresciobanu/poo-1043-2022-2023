#include<iostream>

using namespace std;


//interfete -> o clasa ce contine DOAR functii virtuale pure si trebuie neaparat implementate aceste metode in toti copiii

//clase abstracte -> clase ce contin cel PUTIN 1 fct. virtuala pura; clasele abstracte NU pot fi instantiate;
class InterfataElectrocasnice {
	virtual string putere() = 0;//fct virtuala pura
};

//exceptii custom
class ExceptieCustom :exception {
	string message;
public:
	ExceptieCustom(string message) {
		this->message = message;
	}

	string afisareEroare() {
		return this->message;
	}

	//todo next week virtual char const* what() const
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

	friend istream& operator>>(istream& in, Review& review) {
		cout << "Mesaj : ";
		char aux[300];
		in.getline(aux, 300);

		review.mesaj = aux;

		return in;
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
		out << "Clasa : " << electrocasnic.clasa << " Pret : " << electrocasnic.pret << " Marca : " << electrocasnic.marca << endl;
		for (int i = 0; i < electrocasnic.nrReviews; i++) {
			out << electrocasnic.reviews[i];
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
			throw new ExceptieCustom("Clasa nu poate sa aiba mai mult de 10 caractere");
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


	virtual int durataGarantieLuni() {
		return 12;
	}

	string putere() {
		return "120W";
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


	int durataGarantieLuni() {
		return 24;
	}

	string putere() {
		return "220W";
	}




	void test() {
		//doar o functie publica specifica copilului Televizor
	}
};


//is A Electrocasnice - mostenire
class Frigider : Electrocasnice {
	//faceti voi acasa ceva asemanator ca si in clasa Televizor
};


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
		t2.setClasa("veravrev wefcwever crewcewrre");
	}
	catch (ExceptieCustom* e) {
		cout << e->afisareEroare() << endl;
	}

	//polimorfism
	//supraincarcare - doar numele functiei este la fel si parametrii pot fi in orice ordine si de orice tip
	//suprascriere - se aplica la mostenire - 
	// -> antetul functiei trebuie sa fie acelasi mereu...diferenta este in ce o sa faca metoda
	//(ai nevoie de functii virtuale)
	// 


	//early-binding - stii de la compilare ce se afiseaza
	cout << endl << "early - binding" << endl;
	Electrocasnice e4;
	Electrocasnice e5 = t2; // aici se face upcasting -> copilul se transf in parinte 

	cout << "Durata garantie luni : " << e4.durataGarantieLuni() << endl;
	cout << "Durata garantie luni : " << e5.durataGarantieLuni() << endl;


	//late-binding -  stii abia la runtime ce se afiseaza - te fol. de pointeri!!!!!!!!
	cout << endl << "late - binding" << endl;
	Electrocasnice* pointerEl1 = new Electrocasnice();
	Electrocasnice* pointerEl2 = new Televizor();
	Electrocasnice* pointerEl3 = new Televizor();
	Electrocasnice* pointerEl4 = new Televizor();


	cout << "Durata garantie luni : " << pointerEl1->durataGarantieLuni() << endl;
	cout << "Durata garantie luni : " << pointerEl2->durataGarantieLuni() << endl;

	Electrocasnice** vectorDinamicDePointeri = new Electrocasnice * [4];
	vectorDinamicDePointeri[0] = pointerEl1;
	vectorDinamicDePointeri[1] = pointerEl2;
	vectorDinamicDePointeri[2] = pointerEl3;
	vectorDinamicDePointeri[3] = pointerEl4;

	cout << "polimorfism\n\n";

	for (int i = 0; i < 4; i++) {
		cout << "Durata garantie luni : " << vectorDinamicDePointeri[i]->durataGarantieLuni() << endl;
		cout << "Putere : " << vectorDinamicDePointeri[i]->putere() << endl;
	}
}