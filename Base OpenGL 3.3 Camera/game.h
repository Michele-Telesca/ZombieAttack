#pragma once
#include "gameMap.h"

/*classe game qui vengono gestiti tutte le azioni relatie
alla partita e inizializzati tutti gli oggetti*/
class game {
public:
	game() {};

	void inizializza();

	unsigned int texturePrato;
	gameMap gameMap;

};

void game::inizializza() {

	gameMap.inizializza(texturePrato);

}