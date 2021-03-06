#pragma once
#include<stdio.h>
#include "game.h"
#include "cube.h"
#include "mapObject.h"
#include "utility.h"
#include "globalData.h"
#include <vector>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

						  // x = colonna; z = riga;
						  // 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
int mapMatrix[DIM][DIM] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 1
							{0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 2
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 3
							{0,0,0,0,0,11,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0}, // 4
							{0,0,0,10,4,1,2,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,4,3,2,0,0,0,0}, // 5
							{0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0}, // 6
							{0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,0,1,0,0,0,0}, // 7
							{0,0,0,0,2,0,0,5,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,0,12,0,0,0,0,0,1,0,4,0,0,0,0}, // 8
							{0,0,0,0,1,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0}, // 9 
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 10
							{0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0}, // 11
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,5,7,0,0,0,0,0,0,0,0}, // 12
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,5,0,0,0,0,0,10,0,0}, // 13
							{0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,7,10,0,0,0,0,0,0,0,0}, // 14
							{0,0,10,0,0,0,0,0,0,0,0,0,0,0,10,3,2,0,0,0,0,0,3,1,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 15
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0}, // 16
							{0,0,0,0,0,0,0,0,0,11,0,0,0,12,4,1,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 17
							{0,0,0,0,0,0,0,0,0,1,2,1,4,1,2,2,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 18
							{0,10,0,0,0,12,0,0,0,0,0,0,0,10,4,3,0,0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 19
							{0,0,0,0,0,0,0,12,0,0,0,0,0,0,2,4,0,0,0,16,0,0,0,2,4,0,0,0,0,0,0,12,0,0,0,0,6,0,0,0}, // 20
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,1,0,0,0,0,0,0,0,4,2,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0}, // 21
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0}, // 22
							{0,0,0,9,7,0,0,0,0,0,0,0,0,0,4,1,0,0,0,0,0,0,0,1,4,0,0,0,0,0,0,0,0,0,0,0,6,11,0,11}, // 23
							{0,0,5,7,6,3,0,0,0,0,0,0,0,0,1,2,14,0,0,0,0,0,11,4,2,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0}, // 24
							{0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,1,2,0,0,0,0,0,1,3,13,0,0,0,0,0,0,0,0,0,0,11,6,0,0,0}, // 25
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0}, // 26
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 27
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,0,0,0,0}, // 28
							{0,0,0,0,0,0,0,0,0,0,11,0,0,0,0,0,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 29
							{0,0,12,0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 30
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,10,7,6,0,0,0,0,0,0,0,0,0,0}, // 31
							{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,5,6,11,0,0,0,0,0,1,0,0,0,0}, // 32
							{0,0,0,0,2,0,0,14,0,0,0,0,0,0,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0}, // 33
							{0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0}, // 34
							{0,0,0,0,4,10,0,0,0,0,0,0,0,0,0,0,0,12,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,2,0,0,0,0}, // 35
							{0,0,0,11,1,2,4,3,1,0,0,0,0,0,0,0,0,7,11,3,0,0,0,0,0,0,0,0,0,0,0,1,4,2,4,1,0,0,0,0}, // 36
							{0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 37
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0}, // 38
							{0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 39
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 40
};


vector <glm::vec2> mapObjectsCoord;
vector <glm::vec2> mapTree;


class gameMap {

public:

	gameMap() {}

	unsigned int texturePrato;
	unsigned int textureShadow;

	cube* floor;

	vector <mapObject*> objects; //lista di tutti i mapObjects che possono essere instanziati

	vector <mapObject*> mapObjects; //lista di oggetti da renderizzare all'interno della mappa (con cui il player pu� collidere)
	vector <mapObject*> externalMapObject; //lista di oggetti esterni alla mappa

	void initMap(); //inizializza e posiziona la mappa con i relativi oggetti 
	void initObjectsList(); //inizializza la lista di objects
	void drawMap(Shader simpleShader, Shader lightShader, glm::mat4 view); 
	void drawMapObject(Shader simpleShader, Shader lightShader, glm::mat4 view);

};

void gameMap::initObjectsList() {

	mapObject* stone1_model = new mapObject();
	stone1_model->initMapObject("models/stones/stone1/stone1.dae");
	objects.push_back(stone1_model);
	objects.push_back(stone1_model);

	mapObject* stone2_model = new mapObject();
	stone2_model->initMapObject("models/stones/stone2/stone2.dae");
	objects.push_back(stone2_model);

	mapObject* stone3_model = new mapObject();
	stone3_model->initMapObject("models/stones/stone3/stone3.dae");
	objects.push_back(stone3_model);

	mapObject* stone4_model = new mapObject();
	stone4_model->initMapObject("models/stones/stone4/stone4.dae");
	objects.push_back(stone4_model);

	mapObject* stone5_model = new mapObject();
	stone5_model->initMapObject("models/stones/stone5/stone5.dae");
	objects.push_back(stone5_model);

	mapObject* stone6_model = new mapObject();
	stone6_model->initMapObject("models/stones/stone6/stone6.dae");
	objects.push_back(stone6_model);

	mapObject* stone7_model = new mapObject();
	stone7_model->initMapObject("models/stones/stone7/stone7.dae");
	objects.push_back(stone7_model);

	mapObject* tree1_model = new mapObject();
	tree1_model->initMapObject("models/trees/tree1/tree1.dae");
	objects.push_back(tree1_model);

	mapObject* tree2_model = new mapObject();
	tree2_model->initMapObject("models/trees/tree2/tree2.dae");
	objects.push_back(tree2_model);

	mapObject* tree3_model = new mapObject();
	tree3_model->initMapObject("models/trees/tree3/tree3.dae");
	objects.push_back(tree3_model);

	mapObject* tree4_model = new mapObject();
	tree4_model->initMapObject("models/trees/tree4/tree4.dae");
	objects.push_back(tree4_model);

	mapObject* grass_model = new mapObject();
	grass_model->initMapObject("models/grass/grass1.dae");
	objects.push_back(grass_model);

	mapObject* bush1_model = new mapObject();
	bush1_model->initMapObject("models/bushes/bush1/bush1.dae");
	objects.push_back(bush1_model);

	mapObject* bush2_model = new mapObject();
	bush2_model->initMapObject("models/bushes/bush2/bush2.dae");
	objects.push_back(bush2_model);

	mapObject* fence_model = new mapObject();
	fence_model->initMapObject("models/fence_chain/chain.dae");
	objects.push_back(fence_model);
	cout << "objects inizializzata" << endl;
}

void gameMap::initMap() {

	initObjectsList();

	// ---- FLOOR ---- //
	floor = new cube(DIM+12, DIM+12, DIM+12, 0.0f, UNIT, 0.0f, 0.0f, -0.5f, ((DIM+12)/2) + 0.5f, 0.5f);

	// ---- MAP OBJECT ---- //
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {

			if (mapMatrix[i][j] != 0) {

				//conversione coordinate matrice -> game
				int x = j - 20;
				int z = i - 19;

				if (mapMatrix[i][j] == STONE1) {
					mapObject* stone1 = new mapObject(x, 0.7f, z, 0.4f, 0.0f, UNIT, 0.0f, 0.0f);
					stone1->objectModel = objects[STONE1]->objectModel;
					mapObjects.push_back(stone1);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == STONE2) {
					mapObject* stone2 = new mapObject(x, 0.7f, z, 0.4f, 0.0f, UNIT, 0.0f, 0.0f);
					stone2->objectModel = objects[STONE2]->objectModel;
					mapObjects.push_back(stone2);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == STONE3) {
					mapObject* stone3 = new mapObject(x, 0.7f, z, 0.5f, 0.0f, UNIT, 0.0f, 0.0f);
					stone3->objectModel = objects[STONE3]->objectModel;
					mapObjects.push_back(stone3);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == STONE4) {
					mapObject* stone4 = new mapObject(x, 0.7f, z, 0.5f, 0.0f, UNIT, 0.0f, 0.0f);
					stone4->objectModel = objects[STONE4]->objectModel;
					mapObjects.push_back(stone4);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == STONE5) {
					mapObject* stone5 = new mapObject(x, 1.8f, z, 0.28f, 0.0f, UNIT, 0.0f, 0.0f);
					stone5->objectModel = objects[STONE5]->objectModel;
					mapObjects.push_back(stone5);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == STONE6) {
					mapObject* stone6 = new mapObject(x, 1.8f, z, 0.28f, 0.0f, UNIT, 0.0f, 0.0f);
					stone6->objectModel = objects[STONE6]->objectModel;
					mapObjects.push_back(stone6);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == STONE7) {
					mapObject* stone7 = new mapObject(x, 1.8f, z, 0.28f, 0.0f, UNIT, 0.0f, 0.0f);
					stone7->objectModel = objects[STONE7]->objectModel;
					mapObjects.push_back(stone7);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == TREE1) {
					mapObject* tree1 = new mapObject(x, 1.8f, z, 0.2f, 0.0f, UNIT, 0.0f, 0.0f);
					tree1->objectModel = objects[TREE1]->objectModel;
					tree1->specular = NONE;
					tree1->shadowObject = textureShadow;
					tree1->shadow = true;

					mapObjects.push_back(tree1);
					mapObjectsCoord.push_back(glm::vec2(x, z));
					mapTree.push_back(glm::vec2(x, z));

				}
				else if (mapMatrix[i][j] == TREE2) {
					mapObject* tree2 = new mapObject(x, 1.8f, z, 0.2f, 0.0f, UNIT, 0.0f, 0.0f);
					tree2->objectModel = objects[TREE2]->objectModel;
					tree2->specular = NONE;
					tree2->shadowObject = textureShadow;
					tree2->shadow = true;

					mapObjects.push_back(tree2);
					mapObjectsCoord.push_back(glm::vec2(x, z));
					mapTree.push_back(glm::vec2(x, z));

				}
				else if (mapMatrix[i][j] == TREE3) {
					mapObject* tree3 = new mapObject(x, 1.8f, z, 0.25f, 0.0f, UNIT, 0.0f, 0.0f);
					tree3->objectModel = objects[TREE3]->objectModel;
					tree3->specular = NONE;
					tree3->shadowObject = textureShadow;
					tree3->shadow = true;

					mapObjects.push_back(tree3);
					mapObjectsCoord.push_back(glm::vec2(x, z));
					mapTree.push_back(glm::vec2(x, z));

				}
				else if (mapMatrix[i][j] == TREE4) {
					mapObject* tree4 = new mapObject(x, 1.8f, z, 0.25f, 0.0f, UNIT, 0.0f, 0.0f);
					tree4->objectModel = objects[TREE4]->objectModel;
					tree4->specular = NONE;
					tree4->shadowObject = textureShadow;
					tree4->shadow = true;
					mapObjects.push_back(tree4);
					mapObjectsCoord.push_back(glm::vec2(x, z));
					mapTree.push_back(glm::vec2(x, z));

				}
				else if (mapMatrix[i][j] == BUSH1) {
					mapObject* bush1 = new mapObject(x, 0.6f, z, 0.3f, 0.0f, UNIT, 0.0f, 0.0f);
					bush1->objectModel = objects[BUSH1]->objectModel;
					bush1->specular = NONE;
					mapObjects.push_back(bush1);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == BUSH2) {
					mapObject* bush2 = new mapObject(x, 0.6f, z, 0.3f, 0.0f, UNIT, 0.0f, 0.0f);
					bush2->objectModel = objects[BUSH2]->objectModel;
					bush2->specular = NONE;
					mapObjects.push_back(bush2);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == GRASS) {
					float x_rand = frandMToN(x - 0.5f, x + 0.5f);
					float z_rand = frandMToN(z - 0.5f, z + 0.5f);
					mapObject* grass = new mapObject(x_rand, 0.6f, z_rand, UNIT, 0.0f, UNIT, 0.5f, 0.0f);
					grass->objectModel = objects[GRASS]->objectModel;
					mapObjects.push_back(grass);
				}
				else if (mapMatrix[i][j] == CHEST) {
					mapObject* chest1 = new mapObject(x, 0.6f, z, 0.035f, 0.0f, UNIT, 0.5f, 0.0f);
					chest1->initMapObject("models/chest/chest1.dae");
					mapObjects.push_back(chest1);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
			}
		}
	}

	// ---- MOUNTAINS ---- //
	//front
	mapObject* cliff_front = new mapObject(0.0f, 0.2f, -25.0f, 5.0f, glm::radians(-180.0f), 0.0f, 0.0f, UNIT);
	cliff_front->initMapObject("models/mountains/cliff_front.dae");
	cliff_front->specular = MODERATE;
	externalMapObject.push_back(cliff_front);

	//left
	mapObject* cliff_left = new mapObject(-24.4f, 0.2f, -UNIT, 5.0f, glm::radians(-180.0f), 0.0f, 0.0f, UNIT);
	cliff_left->initMapObject("models/mountains/cliff_left.dae");
	cliff_left->specular = MODERATE;
	externalMapObject.push_back(cliff_left);

	//right
	mapObject* cliff_right = new mapObject(23.5f, 0.2f, -UNIT, 5.0f, glm::radians(-180.0f), 0.0f, 0.0f, UNIT);
	cliff_right->initMapObject("models/mountains/cliff_right.dae");
	cliff_right->specular = MODERATE;
	externalMapObject.push_back(cliff_right);

	//back
	mapObject* mountain_back = new mapObject(0.0f, 0.1f, 35.0f, 0.015f, 0.0f, UNIT, 0.0f, 0.0f);
	mountain_back->initMapObject("models/mountains/mountain_back.dae");
	externalMapObject.push_back(mountain_back);

	// ---- FENCE ---- //
	mapObject* fence1 = new mapObject(17.4f, UNIT, 21.5f, 0.27f, -90.0f, UNIT, 0.0f, 0.0f);
	fence1->objectModel = objects[FENCE]->objectModel;
	externalMapObject.push_back(fence1);

	mapObject* fence2 = new mapObject(13.4f, UNIT, 21.5f, 0.27f, -90.0f, UNIT, 0.0f, 0.0f);
	fence2->objectModel = objects[FENCE]->objectModel;
	externalMapObject.push_back(fence2);
	
	mapObject* fence3 = new mapObject(9.4f, UNIT, 21.5f, 0.27f, -90.0f, UNIT, 0.0f, 0.0f);
	fence3->objectModel = objects[FENCE]->objectModel;
	externalMapObject.push_back(fence3);

	mapObject* fence4 = new mapObject(5.4f, UNIT, 21.5f, 0.27f, -90.0f, UNIT, 0.0f, 0.0f);
	fence4->objectModel = objects[FENCE]->objectModel;
	externalMapObject.push_back(fence4);

	mapObject* fence5 = new mapObject(1.4f, UNIT, 21.5f, 0.27f, -90.0f, UNIT, 0.0f, 0.0f);
	fence5->objectModel = objects[FENCE]->objectModel;
	externalMapObject.push_back(fence5);

	mapObject* fence6 = new mapObject(-2.6f, UNIT, 21.5f, 0.27f, -90.0f, UNIT, 0.0f, 0.0f);
	fence6->objectModel = objects[FENCE]->objectModel;
	externalMapObject.push_back(fence6);

	mapObject* fence7 = new mapObject(-6.6f, UNIT, 21.5f, 0.27f, -90.0f, UNIT, 0.0f, 0.0f);
	fence7->objectModel = objects[FENCE]->objectModel;
	externalMapObject.push_back(fence7);

	mapObject* fence8 = new mapObject(-10.6f, UNIT, 21.5f, 0.27f, -90.0f, UNIT, 0.0f, 0.0f);
	fence8->objectModel = objects[FENCE]->objectModel;
	externalMapObject.push_back(fence8);

	mapObject* fence9 = new mapObject(-14.6f, UNIT, 21.5f, 0.27f, -90.0f, UNIT, 0.0f, 0.0f);
	fence9->objectModel = objects[FENCE]->objectModel;
	externalMapObject.push_back(fence9);

	mapObject* fence10 = new mapObject(-18.6f, UNIT, 21.5f, 0.27f, -90.0f, UNIT, 0.0f, 0.0f);
	fence10->objectModel = objects[FENCE]->objectModel;
	externalMapObject.push_back(fence10);

	// ---- OTHERS ---- //
	mapObject* campfire_tent = new mapObject(0.5f, UNIT, 23.5f, 0.65f, glm::radians(60.0f), 0.0f, UNIT, 0.0f);
	campfire_tent->initMapObject("models/others/campfire_tent.dae");
	externalMapObject.push_back(campfire_tent);

	mapObject* log_pile = new mapObject(-1.6f, 0.6f, 24.2f, 0.015f, glm::radians(52.5f), 0.0f, UNIT, 0.0f);
	log_pile->initMapObject("models/others/log_pile.dae");
	externalMapObject.push_back(log_pile);

	mapObject* tree_external1 = new mapObject(8.0f, 1.8f, 25.6f, 0.2f, 0.0f, UNIT, 0.0f, 0.0f);
	tree_external1->objectModel = objects[TREE2]->objectModel;
	tree_external1->specular = NONE;
	tree_external1->shadowObject = textureShadow;
	tree_external1->shadow = true;
	mapObjects.push_back(tree_external1);

	mapObject* tree_external2 = new mapObject(8.9f, 1.8f, 25.0f, 0.2f, 0.0f, UNIT, 0.0f, 0.0f);
	tree_external2->objectModel = objects[TREE2]->objectModel;
	tree_external2->specular = NONE;
	tree_external2->shadowObject = textureShadow;
	tree_external2->shadow = true;
	mapObjects.push_back(tree_external2);

	mapObject* tree_external3 = new mapObject(9.8f, 1.8f, 24.2f, 0.2f, 0.0f, UNIT, 0.0f, 0.0f);
	tree_external3->objectModel = objects[TREE2]->objectModel;
	tree_external3->specular = NONE;
	tree_external3->shadowObject = textureShadow;
	tree_external3->shadow = true;
	mapObjects.push_back(tree_external3);

	mapObject* tree_external4 = new mapObject(-3.0f, 1.8f, 25.5f, 0.2f, 0.0f, UNIT, 0.0f, 0.0f);
	tree_external4->objectModel = objects[TREE2]->objectModel;
	tree_external4->specular = NONE;
	tree_external4->shadowObject = textureShadow;
	tree_external4->shadow = true;
	mapObjects.push_back(tree_external4);

}

void gameMap::drawMap(Shader simpleShader, Shader lightShader, glm::mat4 view) {

	// ---- Floor ---- //
	floor->drawCube(simpleShader, texturePrato);

}

void gameMap::drawMapObject(Shader simpleShader, Shader lightShader, glm::mat4 view) {

	// ---- Objects ---- //
	for (int i = 0; i < mapObjects.size(); i++) {
		lightShader.setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
		lightShader.setVec3("light.diffuse", 0.7f, 0.7f, 0.7f);
		lightShader.setVec3("light.specular", UNIT, UNIT, UNIT);
		lightShader.setVec3("colormodel", UNIT, UNIT, UNIT);
		mapObjects[i]->drawMapObject(lightShader, simpleShader);
	}

	//---- External Objects ---- //
	for (int i = 0; i < externalMapObject.size(); i++) {
		externalMapObject[i]->drawMapObject(lightShader, simpleShader);
	}


}