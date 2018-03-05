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
	cout << "ALGO" << endl;
	cout << "N" << " para plantar un arbol" << endl;
	cout << "M" << " para hacer crecer un arbol" << endl;
	cout << "X" << " para cortar un arbol" << endl;
	cout << "Clcik Izq para hacer crecer un mango" << endl;
	cout << "Click Der para cortar un mango y mover al inventario" << endl;
	RenderWindow w(sf::VideoMode(1200, 700), "Mangos");
	
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

	/*Texture mendezT;
	mendezT.loadFromFile("res/img/mendez.png");
	Sprite mendS(mendezT);
	mendS.setPosition(600, 350);
	*/

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
								cout << "El arbol aun no ha crecido :( " << endl;
							}
							else {
								int masa;
								cout << "Peso del nuevo mango: ";
								cin >> masa;
								arbolAux->add(masa, posMouse.x, posMouse.y);
								cout << "Un nuevo mango ha crecido!" << endl;
							}
						}
						//No he podido probar esto por que no puedo poner mangos.
						for (int c = 0; c < arbolAux->cantM(); c++/*lol*/) {
							mangoAux = arbolAux->getMango(c);
							if (mangoAux->getSprite().getGlobalBounds().contains(posMouse.x, posMouse.y)) {
								if (event.key.code == Mouse::Right) {
									curs->inv.push(mangoAux);
									arbolAux->delet(c);
									cout << "El mango ha sido cortado y agregado a tu inventario." << endl;
								}
							}
						}
					}
				}
				if (btVender.getGlobalBounds().contains(posMouse.x, posMouse.y)) {
					if (event.key.code == Mouse::Left) {
						if (curs->inv.size() == 0) {
							cout << "No tienes nada que vender" << endl;
						}
						else{
							int opc = 0;
							cout << "Vender todo inventario?"<<endl;
							cout << "1.) si" << endl;
							cout << "2.) no" << endl;
							cin >> opc;
							if (opc == 1) {
								curs->VenderM();
								cout << "Se han vendido todos los mangos en tu invetario!" << endl;
							}
						}
					}
				}
				if (btInv.getGlobalBounds().contains(posMouse.x, posMouse.y)) {
					if (event.key.code == Mouse::Left) {
						cout << "Mangos en tu inventario: " << curs->inv.size() << endl;
						cout << "Dinero: " << curs->pisto << endl;
					}
				}
				break;
				//fin de cases de agregar y eliminar

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
					arbolAux = ListaArboles.getArbol(i);
					//Funcion para hacer crecer un arbol
					if (event.key.code == Keyboard::M) {
						if (curs->sCursor.getGlobalBounds().contains(arbolAux->getSprite().getPosition().x,arbolAux->getSprite().getPosition().y)) {
							arbolAux->grow();
							//El arbol no crece y no estoy seguro por que ::thinking:: . Tenemos que arreglar eso 
						}
					}
					//Funcion para cortar un arbol
					if (event.key.code == Keyboard::X) {
						if (curs->sCursor.getGlobalBounds().contains(arbolAux->getSprite().getPosition().x, arbolAux->getSprite().getPosition().y) || nArbol->getSprite().getGlobalBounds().contains(curs->sCursor.getPosition().x,curs->sCursor.getPosition().y)) {
							if (nArbol->cantM()==0) {
								ListaArboles.deletA(i);
							}
							else {
								cout << "No puedes cortar un arbol que tenga mangos" << endl;
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
			for (int c = 0; i < arbolAux->cantM(); c++) {
				w.draw(arbolAux->getMango(c)->mango);
			}
		}
		w.draw(btInv);
		w.draw(btVender);
		w.draw(curs->sCursor);
		//w.draw(mendS);
		w.display();
	}
	return 0;
}