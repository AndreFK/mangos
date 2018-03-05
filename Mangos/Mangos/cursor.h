#ifndef CURSOR_H_INCLUDED
#define CURSOR_H_INCLUDED


#include<SFML\Graphics.hpp>
#include "Mango.h"
#include <stack>

using namespace sf;
using namespace std;

struct cursor {
	Texture tCursor;
	Sprite sCursor;
	stack<Mango*> inv;
	float pisto;
	void VenderM();
	cursor();
	~cursor();
};



#endif // !CURSOR_H_INCLUDED

