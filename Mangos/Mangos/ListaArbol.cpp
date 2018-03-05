#include "ListaArbol.h"
#include <iostream>

ListaArbol::ListaArbol()
{
	first = NULL;
	cant_A = 0;
}

void ListaArbol::addArbol(Arbol* nuevo) {
	insertarA(nuevo, cant_A);
}

void ListaArbol::insertarA(Arbol* nuevo, int pos) {
	if (pos < 0 || pos > cant_A) {
		return;
	}
	nodo* nodo_n = new nodo(nuevo);
	if (pos == 0 && first == NULL) {
		first = nodo_n;
		cant_A += 1;
	}
	else if (pos == 0 && first != NULL) {
		nodo_n->sig = first;
		first = nodo_n;
		cant_A += 1;
	}
	else {
		nodo * tmp = first;
		if (pos == cant_A) {
			for (int i = 0; i < (cant_A-1); i++) {
				tmp = tmp->sig;
			}
			tmp->sig = nodo_n;
			nodo_n->ant = tmp;
			cant_A += 1;
		}
		else if (pos <= cant_A) {
			for (int i = 0; i < pos - 1; i++) {
				tmp = tmp->sig;
			}
			tmp->sig->ant = nodo_n;
			nodo_n->ant = tmp;
			nodo_n->sig = tmp->sig;
			tmp->sig = nodo_n;
			cant_A += 1;
		}
	}
}

void ListaArbol::deletA(int pos) {
	if (pos < 0 || pos>cant_A || cant_A == 0) {
		return;
	}
	nodo * borrador;
	if (cant_A == 1) {
		borrador = first;
		first = NULL;
		cant_A = cant_A - 1;
	}
	else if (pos == 0) {
		borrador = first;
		first = first->sig;
		delete borrador;
		cant_A = cant_A - 1;
	}
	else if (pos == cant_A - 1) {
		nodo * tmp = first;
		for (int i = 0; i < (pos - 1); i++) {
			tmp = tmp->sig;
		}
		borrador = tmp->sig;
		delete borrador;
		tmp->sig = NULL;
		cant_A = cant_A - 1;
	}
	else {
		nodo*tmp = first;
		for (int i = 0; i < (pos - 1); i++) {
			tmp = tmp->sig;
		}
		borrador = tmp->sig;
		tmp->sig = borrador->sig;
		borrador->sig->ant = tmp;
		delete borrador;
		cant_A = cant_A - 1;
	}
}

int ListaArbol::getTam() {
	return cant_A;
}

Arbol * ListaArbol::getArbol(int pos) {
	nodo * tmp = first;
	for (int i = 0; i < pos; i++) {
		tmp = tmp->sig;
	}
	return tmp->arbol;
}

ListaArbol::~ListaArbol()
{
}
