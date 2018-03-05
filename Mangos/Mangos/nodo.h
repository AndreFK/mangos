#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

#include "Arbol.h"
#include "Mango.h"


struct nodo{
	Arbol * arbol;
	nodo * sig;
	nodo * ant;
	nodo(Arbol*);
	~nodo();
};

#endif //!NODO_H_INCLUDED