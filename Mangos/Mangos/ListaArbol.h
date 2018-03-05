#ifndef LISTAARBOL_H_INCLUDED
#define LISTAARBOL_H_INCLUDED

#include "Arbol.h"
#include "nodo.h"

class ListaArbol
{
private:
	nodo * first;
	int cant_A;
public:
	void addArbol(Arbol*);
	void insertarA(Arbol*, int);
	void deletA(int);
	int getTam();
	Arbol * getArbol(int);
	ListaArbol();
	~ListaArbol();
};

#endif // !LISTAARBOL_H_INCLUDED
