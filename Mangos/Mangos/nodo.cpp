#include "nodo.h"

nodo::nodo(Arbol*arbol)
{
	this->arbol = arbol;
	sig = NULL;
	ant = NULL;
}


nodo::~nodo()
{
}
