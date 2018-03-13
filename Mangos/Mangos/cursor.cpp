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
	int pe = 0;
	float dinero;
	while(inv.size() != 0 ) {
		pe = pe + inv.top()->peso;	
		inv.pop();
	}
	dinero = pe * 2.5;
	pisto = dinero + pisto;
	cout << "El peso total es: " << pe << endl;
	cout << "ha obtenido " << pisto << " lempiras." << endl;
}

cursor::~cursor(){}