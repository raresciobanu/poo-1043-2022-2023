#include<iostream>

using namespace std;

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
		cout << "Review\n";


		cout << "Mesaj : ";
		char aux[300];
		in.getline(aux, 300);

		review.mesaj = aux;

		return in;
	}
};

int Review::counter = 1;

class Electrocasnice {
	string clasa;
	float pret;
	char* marca;

	//Electrocasnice has A vector of Review - compunere
	Review* reviews;
	int nrReviews;


public:

	Electrocasnice() {
		//todo next sem
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

	friend ostream& operator<<(ostream& out, const Electrocasnice& electrocasnic) {
		out << electrocasnic.clasa << " " << electrocasnic.pret << " " << electrocasnic.marca << endl;
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

		cout << "Reviews : ";
		delete[] electrocasnic.reviews;
		electrocasnic.reviews = new Review[electrocasnic.nrReviews];
		for (int i = 0; i < electrocasnic.nrReviews; i++) {
			in >> electrocasnic.reviews[i];
		}

		return in;
	}
};



//is A Electrocasnice - mostenire
class Televizor : Electrocasnice {
	float diagonala;
	string tipEcran; //led / oled / qled / 4k /3d

public:

	Televizor() :Electrocasnice() {
		//todo next sem
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
};


//is A Electrocasnice - mostenire
class Frigider : Electrocasnice {

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

}