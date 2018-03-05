#include "Arbol.h"
#include "Mango.h"
#include <iostream>

using namespace sf;
using namespace std;
Arbol::Arbol()
{
}

Arbol::Arbol(int x, int y) {
	t_arbol.loadFromFile("res/img/arbolF.png");
	tg_arbol.loadFromFile("res/img/arbolgF.png");
	arbol.setTexture(t_arbol);
	arbol.setPosition(x, 600);
	first = NULL;
	cant_M = 0;
	growth = 1;
}

void Arbol::add(int peso, int x, int y) {
	if (growth == 2) {
		insert(peso, cant_M, x, y);
	}
}

void Arbol::add(Mango*mango) {
	if (first == NULL) {
		first = mango;
	}
	else {
		Mango * tmp = first;
		for (int i = 0; i < (cant_M - 1); i++) {
			tmp = tmp->sig;
		}
		tmp->sig = mango;
	}
	cant_M += 1;
}

void Arbol::insert(int peso, int pos, int x, int y) {
	if (pos < 0 || pos > cant_M) {
		return;
	}
	Mango *mango_n = new Mango(peso, x, y);
	if (pos == 0 && first == NULL) {
		first = mango_n;
		cant_M += 1;
	}
	else if (pos == 0 && first != NULL) {
		mango_n->sig = first;
		first = mango_n;
		cant_M += 1;
	}
	else {
		Mango * tmp = first;
		if (pos == cant_M) {
			for (int i = 0; i < cant_M; i++) {
				tmp = tmp->sig;
			}
			tmp->sig = mango_n;
			mango_n->ant = tmp;
			cant_M += 1;
		}
		else if (pos <= cant_M) {
			for (int i = 0; i < pos-1; i++) {
				tmp = tmp->sig;
			}
			tmp->sig->ant = mango_n;
			mango_n->ant = tmp;
			mango_n->sig = tmp->sig;
			tmp->sig = mango_n;
			cant_M += 1;
		}
	}
}

void Arbol::delet(int pos) {
	if (pos < 0 || pos>cant_M || cant_M == 0) {
		return;
	}
	Mango * borrador;
	if (cant_M == 1) {
		borrador = first; 
		first = NULL;
		cant_M = cant_M - 1;
	}
	else if (pos == 0) {
		borrador = first;
		first = first->sig;
		delete borrador;
		cant_M = cant_M - 1;
	}
	else if (pos == cant_M - 1) {
		Mango * tmp = first;
		for (int i = 0; i < (pos - 1); i++) {
			tmp = tmp->sig;
		}
		borrador = tmp->sig; 
		delete borrador;
		tmp->sig = NULL;
		cant_M = cant_M - 1;
	}
	else {
		Mango *tmp = first; 
		for(int i = 0; i < (pos - 1); i++) {
			tmp = tmp->sig;
		}
		borrador = tmp->sig;
		tmp->sig = borrador->sig;
		borrador->sig->ant = tmp;
		delete borrador;
		cant_M = cant_M - 1;
	}
}

void Arbol::masa() {
	Mango * tmp = first;
	for (int i = 0; i < cant_M; i++) {
		cout<< tmp->peso << endl;
	}
}

int Arbol::cantM() {
	return cant_M;
}

Mango * Arbol::getMango(int pos) {
	Mango * tmp = first;
	for (int i = 0; i < pos; i++) {
		tmp = tmp->sig;
	}
	return tmp;
}

Sprite Arbol::getSprite() {
	return arbol;
}

void Arbol::grow() {
	if (growth == 1) {
		arbol.setTexture(tg_arbol);
		arbol.setPosition(arbol.getPosition().x, 300);
		arbol.setTextureRect(IntRect(0, 0, 180, 350));
		growth++;
	}
}

int Arbol::getGrowth() {
	return growth;
}

Arbol::~Arbol()
{
}


