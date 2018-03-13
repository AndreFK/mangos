#pragma once
#ifndef MANGO_H_INCLUDED
#define MANGO_H_INCLUDED

#include <SFML\Graphics.hpp>

struct Mango {
	//sf::Texture t_mango;
	//sf::Sprite mango;
	Mango *ant;
	Mango *sig;
	int peso;

	Mango(int, int, int);
	//sf::Sprite getSprite();
	~Mango();
};

#endif // !MANGO_H_INCLUDED
