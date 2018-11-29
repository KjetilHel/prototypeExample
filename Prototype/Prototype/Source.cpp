#include <iostream>

class Figur {
public:
	static Figur *finnOgKlon(int figurID) { return prototyper[figurID]->klon(); }
	virtual void vis() = 0;
protected:
	virtual Figur *klon() = 0;
	static void nyPrototype(Figur *figur) { prototyper[teller++] = figur; }
private:
	static Figur *prototyper[2];
	static int teller;
};

Figur *Figur::prototyper[];
int Figur::teller = 0;

class Sirkel : public Figur {
public:
	Figur *klon() { return new Sirkel(1); }
	void vis() { std::cout << "Sirkel med id: " << id << '\n'; }
protected:
	Sirkel(int dummy) { id = teller++; }
private:
	static Sirkel sirkel;
	Sirkel() { nyPrototype(this); }
	int id;
	static int teller;
};

Sirkel Sirkel::sirkel;
int Sirkel::teller = 1;


class Firkant : public Figur {
public:
	Figur *klon() { return new Firkant(1); }
	void vis() { std::cout << "Firkant med id: " << id << '\n'; }
protected:
	Firkant(int dummy) { id = teller++; }
private:
	static Firkant firkant;
	Firkant() { nyPrototype(this); }
	int id;
	static int teller;
};

Firkant Firkant::firkant;
int Firkant::teller = 1;


const int ANTALL_FIGURER = 10;
int figurValg[ANTALL_FIGURER] = { 0, 0, 0, 1, 1, 0, 1, 1, 0, 1 };

int main() {
	Figur *figurer[ANTALL_FIGURER];

	for (int i = 0; i < ANTALL_FIGURER; i++) 
		figurer[i] = Figur::finnOgKlon(figurValg[i]);

	for (int i = 0; i < ANTALL_FIGURER; i++)
		figurer[i]->vis();

	for (int i = 0; i < ANTALL_FIGURER; i++)
		delete figurer[i];

	return 0;
}