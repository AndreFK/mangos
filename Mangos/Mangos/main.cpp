#include <iostream>
#include <SFML\Graphics.hpp>
#include "Arbol.h"
#include "cursor.h"
#include "ListaArbol.h"
#include "Mango.h"
#include "nodo.h"

using namespace std;
using namespace sf;

int main() {
	cout << "MANGOS" << endl;
	cout << "N" << " para plantar un arbol" << endl;
	cout << "M" << " para hacer crecer un arbol" << endl;
	cout << "X" << " para cortar un arbol" << endl;
	cout << "Clcik Izq para hacer crecer un mango" << endl;
	cout << "Click Der para cortar un mango y mover al inventario" << endl << endl;
	RenderWindow w(sf::VideoMode(1200, 700), "Mangos");

	Texture arbolGpls;
	arbolGpls.loadFromFile("res/img/arbolgF.png");
	
	Texture background;
	Texture Inv;
	Texture Vender;
	Texture tcursor;

	background.loadFromFile("res/img/background.png");
	Inv.loadFromFile("res/img/btInv.png");
	Vender.loadFromFile("res/img/btVender.png");
	
	Sprite backg(background);
	
	Sprite btInv(Inv);
	btInv.setPosition(1050, 30);
	
	Sprite btVender(Vender);
	btVender.setPosition(1050, 90);

	Font font;
	font.loadFromFile("res/font/MixComic.ttf");
	Text text;
	text.setFont(font);
	text.setCharacterSize(120);
	text.setPosition(50, 150);
	text.setString("Consola");

	//estos son todos los obejtos qu se van a usar
	cursor * curs = new cursor();
	ListaArbol ListaArboles;
	Arbol * arbolAux;
	
	Mango * mangoAux;

	while (w.isOpen()) {

		Event event;
		Vector2i posMouse = Mouse::getPosition(w);

		while (w.pollEvent(event)) {

			switch (event.type)
			{
			case sf::Event::Closed:
				w.close();
				break;

			//cases para agregar y eliminar mangos
			case Event::MouseButtonPressed:
				//Esta parte del codigo funciona bien
				for (int i = 0; i < ListaArboles.getTam(); i++) {
					arbolAux = ListaArboles.getArbol(i);
					if (arbolAux->getSprite().getGlobalBounds().contains(posMouse.x, posMouse.y)) {
						if (event.key.code == Mouse::Left) {
							w.draw(text);
							w.display();
							if (arbolAux->getGrowth() == 1) {
								cout << "Este arbol aun no ha crecido :(" << endl << endl;
							}
							else {
								int masa;
								cout << "Peso del nuevo mango: ";
								cin >> masa;
								arbolAux->addM(masa, posMouse.x, posMouse.y);
								cout << "Un nuevo mango ha crecido!" << endl;
								cout << "Cantidad de mangos en este arbol: " << arbolAux->cantM() << endl << endl;
							}
						}
						//Aqui se corta el mango del arbol.
						//Ya funciona esto
						for (int c = 0; c < arbolAux->cantM(); c++/*lol*/) {
							mangoAux = arbolAux->getMango(c);
							if (arbolAux->getSprite().getGlobalBounds().contains(posMouse.x,posMouse.y)) {
								//mangoAux->getSprite().getGlobalBounds().contains(posMouse.x, posMouse.y)
								if (event.key.code == Mouse::Right) {
									while (arbolAux->cantM() != 0) {
										curs->inv.push(mangoAux);
										arbolAux->delet(c);
									}
									cout << "Los mangos han sido cortados y agregados a tu inventario." << endl << endl;
								}
							}
						}
					}
				}

				//esta es la funcion del boton vender
				if (btVender.getGlobalBounds().contains(posMouse.x, posMouse.y)) {
					if (event.key.code == Mouse::Left) {
						if (curs->inv.size() == 0) {
							cout << "No tienes nada que vender" << endl << endl;
						}
						else{
							int opc = 0;
							cout << "Vender todo inventario?"<<endl;
							cout << "1.) si" << endl;
							cout << "2.) no" << endl;
							cout << "Opcion: ";
							cin >> opc;
							cout << endl;	
							if (opc == 1) {
								curs->VenderM();
								cout << "Se han vendido todos los mangos en tu invetario!" << endl << endl;
							}
						}
					}
				}
				//esta es la funcion del boton inventario
				if (btInv.getGlobalBounds().contains(posMouse.x, posMouse.y)) {
					if (event.key.code == Mouse::Left) {
						cout << "Mangos en tu inventario: " << curs->inv.size() << endl;
						cout << "Dinero: " << curs->pisto << endl << endl;
					}
				}
				break;
				//fin de cases de agregar y eliminar mangos

			//inicio de creacion y eliminacion de arboles
			case Event::KeyPressed:
				Arbol * nArbol = new Arbol(curs->sCursor.getPosition().x, curs->sCursor.getPosition().y);
				if (event.key.code == Keyboard::Left || event.key.code == Keyboard::A) {
					curs->sCursor.move(-50, 0);
				}
				if (event.key.code == Keyboard::Right || event.key.code == Keyboard::D) {
					curs->sCursor.move(50, 0);
				}

				//Aqui se crea un nuevo Arbol
					if (event.key.code == Keyboard::N) {
						if (curs->sCursor.getGlobalBounds().contains(nArbol->getSprite().getPosition().x, nArbol->getSprite().getPosition().y)) {
							cout << "No puedes crecer un arbol aqui" << endl;
						}
						else {
							ListaArboles.addArbol(nArbol);
						}
						
					}
				
				for (int i = 0; i < ListaArboles.getTam(); i++) {
					Arbol * arboltmp = ListaArboles.getArbol(i);
					//Funcion para hacer crecer un arbol
					if (event.key.code == Keyboard::M) {
						if (arboltmp->getSprite().getGlobalBounds().contains(curs->sCursor.getPosition().x,curs->sCursor.getPosition().y)) {
							arboltmp->grow();
						}
					}
					//Funcion para cortar un arbol
					if (event.key.code == Keyboard::X) {
						if (curs->sCursor.getGlobalBounds().contains(arboltmp->getSprite().getPosition().x, arboltmp->getSprite().getPosition().y) || arboltmp->getSprite().getGlobalBounds().contains(curs->sCursor.getPosition().x,curs->sCursor.getPosition().y)) {
							if (arboltmp->cantM() == 0) {
								ListaArboles.deletA(i);
							}
							else {
								cout << "No puedes cortar un arbol que tenga mangos" << endl << endl;
							}
						}
						
					}
				}
				break;
			}
		}
		w.clear();
		w.draw(backg);
		for (int i = 0; i < ListaArboles.getTam(); i++) {
			arbolAux = ListaArboles.getArbol(i);
			w.draw(arbolAux->getSprite());
				/*
				for (int c = 0; i < arbolAux->cantM(); c++) {
					w.draw(arbolAux->getMango(c)->mango);
				}
				*/
		}
		w.draw(btInv);
		w.draw(btVender);
		w.draw(curs->sCursor);
		//w.draw(mendS);
		w.display();
	}
	return 0;
}