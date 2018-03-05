#include "cursor.h"

#include <SFML\Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

cursor::cursor()
{
	tCursor.loadFromFile("res/img/cursor.png");
	sCursor.setTexture(tCursor);
	sCursor.setPosition(900, 630);
	pisto = 0;
}

void cursor::VenderM() {
	int peso = 0;
	while (!inv.empty()) {
		peso = inv.top()->peso;
		pisto = (pisto + peso) * 2.5;
		inv.pop();
		cout << "El peso total es: " << peso << endl;
		cout << "ha obtenido " << pisto << " lempiras." << endl;
	}
}

cursor::~cursor(){}