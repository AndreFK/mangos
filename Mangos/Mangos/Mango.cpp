#include "Mango.h"

using namespace sf;

Mango::Mango(int peso, int x, int y) {
	t_mango.loadFromFile("res/img/mangoF.png");
	mango.setTexture(t_mango);
	mango.setPosition(x, y);
	this->peso = peso;
	ant = NULL;
	sig = NULL;
}

Sprite Mango::getSprite() {
	return mango;
}

Mango::~Mango()
{
}
