#include <iostream>

// Figur er hovedklassen for alle figurene
class Figur {
public:
	//Blir tilsent et tall og finner ut av hvilken av underklassene som skal klones
	static Figur *finnOgKlon(int figurID) { return prototyper[figurID]->klon(); } 
	virtual void vis() = 0; //Virtuell funksjon som underklassene arver slik at deres "vis"-funksjoner kan kalles opp
protected:
	virtual Figur *klon() = 0; //Virtuell funksjon som gjør at underklassene kan klones
	//Når en underklasse blir deklarert blir den lagret som en prototype som er klar til å klones
	static void nyPrototype(Figur *figur) { prototyper[teller++] = figur; }
private:
	static Figur *prototyper[2]; //Array som holder på de klonbare underklassene
	static int teller; //Teller som holder orden på hvor mange underklasser som har blitt registrert
};

//Initsialiserer variblene for"Figur"-klassen
Figur *Figur::prototyper[]; 
int Figur::teller = 0;


class Sirkel : public Figur {
public:
	//Når figuren skal klones blir konstruktoren med en variabel kalt opp
	Figur *klon() { return new Sirkel(1); }
	void vis() { std::cout << "Sirkel med id: " << id << '\n'; }
protected:
	//Denne konstruktoren lager en ny klone av "Sirkel"-klassen
	Sirkel(int dummy) { id = teller++; }
private:
	static Sirkel sirkel;
	//Denne konstruktoren registrerer "Sirkel"-klassen som klonbar i "Figur"-klassen
	Sirkel() { nyPrototype(this); }
	int id;
	static int teller;
};

//Intsialiserer variablene til "Sirkel"-klassen
Sirkel Sirkel::sirkel;
int Sirkel::teller = 1;


//Helt lik som "Sirkel"-klassen
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

//Initialiserer variablene til "Firkant"-klassen
Firkant Firkant::firkant;
int Firkant::teller = 1;

//Simulerer at den skal klones 10 ulike figurer
const int ANTALL_FIGURER = 10;
//Hvert tall reresenterer hvilken type figur man ønsker at skal klones, 0 = sirkel og 1 = firkant
int figurValg[ANTALL_FIGURER] = { 0, 0, 0, 1, 1, 0, 1, 1, 0, 1 };

int main() {
	//Lager en liste som skal holde på de klonede elementene
	Figur *figurer[ANTALL_FIGURER];

	//Går igjennom simuleringen og lager 10 kloner
	for (int i = 0; i < ANTALL_FIGURER; i++) 
		figurer[i] = Figur::finnOgKlon(figurValg[i]);

	//Går igjennom alle de klonede elementene og ber dem skrive ut informasjonen om seg selv
	for (int i = 0; i < ANTALL_FIGURER; i++)
		figurer[i]->vis();

	//Sletter klonene for å frigjøre minnet
	for (int i = 0; i < ANTALL_FIGURER; i++)
		delete figurer[i];

	return 0;
}