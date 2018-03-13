#pragma once
#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <SFML\Graphics.hpp>
#include "Mango.h"

class Arbol
{
private:
	sf::Texture t_arbol, tg_arbol;
	sf::Sprite arbol;
	Mango *first;
	int cant_M;
	int growth; 
public:

	Arbol();
	Arbol(int, int);
	~Arbol();
	void addM(int, int, int);
	void addM(Mango*);
	void insert(int, int, int, int);
	void delet(int);
	void masa();
	int cantM();
	Mango *getMango(int);
	sf::Sprite getSprite();
	void grow();
	int getGrowth();
};

#endif // !ARBOL_H_INCLUDED