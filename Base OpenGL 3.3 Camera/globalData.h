#pragma once

//GAME SETTINGS

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

float RENDER_SPEED = 0.03f; //Pi� � alto e pi� rallenta; pi� � basso e pi� velocizza

const int DIM = 40; //Dimensione floor 20x20
float TILE_DIM = 1.0; //Dimensione singola mattonella

float MOVE_STEP = TILE_DIM / 10; // = 0.1000f; //Incremento dello spostamento del player 
float BOT_MOVE_STEP = TILE_DIM / 30; // = 0.05; //Incremento dello spostamento del BOT 

float EPSILON_1 = TILE_DIM / 100; // epsilon di collisione tra player e gameObject
float EPSILON_2 = BOT_MOVE_STEP / 100;
float EPSILON_3 = 0.25f; // epsilon di collisione tra player e bot

//glm::vec3 lightPos(-10.0f, 25.0f,-10.0f); //posizione luce
glm::vec3 lightPos(0.0f, 25.0f, 0.0f); //posizione luce
//glm::vec3 lightPos(0.0f, -1.0f, 0.0f); //DIREZIONE luce


const int WEAPON_SHOTGUN = 1;
const float LENGTH_RANGE_SHOTGUN = 3.0f; //lunghezza di mira
const float LENGTH_BASE_SHOTGUN = 4.0f;
const float ANGLE_RANGE_SHOTGUN = 90.0f;
const float SHOTGUN_DAMAGE = 100.0f;

const int WEAPON_SNIPER = 2;
const float LENGTH_RANGE_SNIPER = 9.0f; //lunghezza di mira
const float LENGTH_BASE_SNIPER = 1.0f;
const float ANGLE_RANGE_SNIPER = 90.0f;
const float SNIPER_DAMAGE = 50.0f;

// ---- //
const int STONE1 = 1;
const int STONE2 = 2;
const int STONE3 = 3;
const int STONE4 = 4;
const int STONE5 = 5;
const int STONE6 = 6;
const int STONE7 = 7;
const int TREE1 = 8;
const int TREE2 = 9;
const int TREE3 = 10;
const int TREE4 = 11;
const int GRASS = 12;
const int BUSH1 = 13;
const int BUSH2 = 14;
const int CHEST = 15;

const int DIRECTION_RIGHT = 0;
const int DIRECTION_LEFT = 1;
const int DIRECTION_DOWN = 2;
const int DIRECTION_UP = 3;

const int ZOMBIE_PRISONER = 1;
const int ZOMBIE_DERRICK = 2;
const int ZOMBIE_COP = 3;

const int POWERUP_BULLET = 1;
const int POWERUP_SIGHT = 2;

//specular
const int HIGH = 2;
const int MODERATE = 1;
const int NONE = 0;

//SHOT
const int numShot = 3; //numero proiettili
const float SHOT_SPEED = 3.0f; //velocit� proiettili
const float SHOT_DIM = 0.5f; //dimensione x,z del proiettile
const float SHOT_DIM2 = 1.5f; //dimensione x,z del proiettile
const float ejection_bullet_SHOTGUN_TIME = 1.1f; //secondi per l'ejectingBullet SHOTGUN
const float ejection_bullet_SNIPER_TIME = 2.0f; //secondi per l'ejectingBullet SNIPER

//Movimenti
bool muoviDx = false;
bool muoviSx = false;
bool muoviSu = false;
bool muoviGiu = false;
bool mouseSx = false;

bool startPlayerShot = false;
