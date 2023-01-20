#include<iostream>

#include<vector>
#include<list>
#include<map>

using namespace std;

/*
* Template = Sablon
*
* Folosit pentru reutilizarea codului.
* Fct sau clase template - este un mod utilizat de compilator pt a construi automat diverse functii.
*
* class sau typename
*
* La compilare are loc generarea de cod pentru entitatea template creata.
*
*/


template <typename BUNICA> BUNICA suma(BUNICA a, BUNICA b) {
	return a + b;
}

template <typename T, typename W> T suma(T a, W b) {
	return a + b;
}

template <class U> U suma(U ceva) {
	return ceva + 100;
}

template <typename ADRIAN> void afisareTemplate(ADRIAN a) {
	cout << a << endl;
}


template<typename T> class VectorTemplate {
private:
	int N;
	T* elemente;
public:
	VectorTemplate() {
		this->N = 0;
		this->elemente = nullptr;
	}

	VectorTemplate(int N, T* elemente) {
		this->N = N;
		this->elemente = new T[N];
		for (int i = 0; i < N; i++) {
			this->elemente[i] = elemente[i];
		}
	}

	VectorTemplate(const VectorTemplate& v) {
		this->N = v.N;

		if (v.elemente != nullptr) {
			this->elemente = new T[v.N];
			for (int i = 0; i < v.N; i++) {
				this->elemente[i] = v.elemente[i];
			}
		}
	}

	~VectorTemplate() {
		if (this->elemente != nullptr) {
			delete[] this->elemente;
		}
	}

	int getSize() {
		return N;
	}

	bool isEmpty() {
		return this->N == 0;
	}

	T* getElemente() {
		return this->elemente;
	}

	T* getElementeDeepCopy() {
		T* aux = new T[N];
		for (int i = 0; i < N; i++) {
			aux[i] = this->elemente[i];
		}

		return aux;
	}


	void addElement(T elNou) {
		T* aux = new T[N + 1];
		for (int i = 0; i < N; i++) {
			aux[i] = this->elemente[i];
		}

		aux[N++] = elNou;
		delete[] this->elemente;
		this->elemente = aux;
	}

	void removeElement(int position) {
		if (position >= 0 && position < N) {
			T* aux = new T[N - 1];
			int k = 0;
			for (int i = 0; i < N; i++) {
				if (i != position) {
					aux[k++] = this->elemente[i];
				}
			}

			N--;
			delete[] this->elemente;
			this->elemente = aux;
		}
		else {
			throw new exception("bad position provided");
		}
	}


	T operator[](int index) {
		if (index >= 0 && index < N) {
			return this->elemente[index];
		}
		else {
			throw exception("index is invalid");
		}
	}

	friend ostream& operator<<(ostream& out, VectorTemplate& v) {
		out << "N= " << v.N << endl;

		if (v.elemente != nullptr) {
			for (int i = 0; i < v.N; i++) {
				out << v.elemente[i] << " ";
			}
		}
		out << endl;

		return out;
	}

};

//CLASE - STL
//� reprezinta o librarie de clase template standard(standard template library)
//� acopera principalele structuri de date : vector, lista, stiva, coada, tabela de dispersie(hash - table);
//� pot fi utilizate fara alte modificari pentru tipuri fundamentale sau definite de programator.

//STL=Containere + ITERATORI + ALGORITMI

//Containere: 
//� un obiect ce stocheaza alte obiecte si are metode pentru a le accesa;

//TIP CONTAINERE
//� secventiale : 
		//� vector;
		//� list;
		//� deque; 
//� asociative(valoare � cheie) :
		//� set(multime de chei unice, sortate)
		//� multiset(multime de chei, sortate)
		//� map(multime valori - chei unice, sortate)
		//� multimap(multime valori - chei sortate)
//� adaptive :
		//� stack 
		//� queue
		//� priority_queue


//ITERATORI
	//� forma generalizata a pointerilor; 
	//� utilizati pentru a itera prin elementele containerelor
	//� se comporta ca interfata intre containere si algoritmi
	//� iteratori predefiniti :
			//� ostream_iterator; 
			//� istream_iterator;
			//� reverse_iterator; 
			//� insert_iterator;

//ALGORITMI
	//� functii generice independente de tipul containerului; 
	//� utilizate pentru a prelucra elementele containerelor
	//� folosesc iteratori pentru acces la elemente
	//� functii importante : 
		//� copy;
		//� for_each;
		//� sort;
		//� find;
		//� transform

////Mai multe exemple: https://www.sanfoundry.com/cpp-programming-examples-stl/


//pt containerul vector trebuie sa adaugi #include <vector> 
//pt containerul list trebuie sa adaugi #include <list> 
//pt containerul map trebuie sa adaugi #include <map> 
//la fel si pt alte containere...


class Persoana {
	string nume;

public:
	Persoana(string nume) {
		this->nume = nume;
	}


	friend ostream& operator<<(ostream& out, Persoana& p) {
		out << "Nume= " << p.nume << endl;

		return out;
	}
};

void main() {
	//functii si clase template
	cout << suma(2, 5.5) << endl;
	cout << suma(100, 100) << endl;

	afisareTemplate("un mesaj");
	afisareTemplate(5);
	afisareTemplate(5.111);

	VectorTemplate<double> vectorTemplate1;

	vectorTemplate1.addElement(22.1);
	vectorTemplate1.addElement(122.33);
	vectorTemplate1.addElement(222.53);
	vectorTemplate1.addElement(552.571);
	vectorTemplate1.addElement(72.3);
	vectorTemplate1.addElement(88.801);
	vectorTemplate1.addElement(128.801);
	vectorTemplate1.addElement(55.33);

	cout << vectorTemplate1;

	vectorTemplate1.removeElement(0);
	vectorTemplate1.removeElement(3);

	cout << vectorTemplate1;


	cout << "\n\nSTL\n\n";

	//STL
	Persoana p1("Ionica");
	Persoana p2("Iulian");
	Persoana p3("Vlad");

	Persoana* vectorDePers;

	vector<Persoana> vectorDePersoane;
	vectorDePersoane.push_back(p1);
	vectorDePersoane.push_back(p2);
	vectorDePersoane.push_back(p3);

	for (int i = 0; i < vectorDePersoane.size(); i++) {
		cout << vectorDePersoane[i] << endl;
	}

	vectorDePersoane.pop_back();//sterge din vector ultima valoare

	cout << "Parcurgere vector fara index [] \n";
	//Poti parcurge un vector si asa:
	for (Persoana j : vectorDePersoane) {
		cout << j << endl;
	}

	vector<Persoana>::iterator it1;

	cout << "Iterator VECTOR" << endl;
	//iteratorul este un pointer ce va pointa catre fiecare obiect Persoana din vector
	for (it1 = vectorDePersoane.begin(); it1 != vectorDePersoane.end(); it1++) {
		cout << *it1 << endl;
	}
}