#pragma once
#include "model.h"
#include "weapon.h"
#include "skinned_mesh.h"
#include "globalData.h"
#include "playerShot.h"
//#include "villain.h"


class player {

public:

	player() {}

	player(float x, float y, float z) : x(x), y(y), z(z) {}

	//coordinate
	float x;
	float y;
	float z;

	int life; //vita del player aggiornata 
	int numShotsAvailable; //colpi a disposizione
	float chargingTime; //tempo di ricarica del colpo
	float timeLastShot; //tempo dell'ultimo colpo. servir� in update per calcolare se � passato abbastanza tempo per ricaricare  
	float anglePlayer;
	// modello 3D del player
	SkinnedMesh meshRunning;
	SkinnedMesh meshStanding;
	SkinnedMesh meshAttacking;

	//float animationCounter = 0.0f;

	weapon* wea = new weapon(3.0f, 90.0f, 2.0f); //arma posseduta al momento
	
	bool mouseSxIsSelected = false;
	bool startPlayerShot = false;
	//lista colpi
	playerShot listShot[numShot];


	unsigned int texturePlayer;

	//prototipi
	void drawPlayer(Shader animShader, Shader lightShader, glm::mat4 view, glm::vec3 mousePoint); //disegna il player
	void initPlayer(); //inizializza il player

	//get e set
	float getX() {
		return x;
	}

	float getY() {
		return y;
	}

	float getZ() {
		return z;
	}

	float getAnglePlayer() {
		return anglePlayer;
	}

	void setX(float new_x) {
		x = new_x;
	}

	void setY(float new_y) {
		y = new_y;
	}

	void setZ(float new_z) {
		z = new_z;
	}

	void setAnglePlayer(float angle) {
		anglePlayer = angle;
	}

};

void player::initPlayer() {

	//punto in cui nasce
	x = 0.0f;
	y = 0.5f;
	z = 0.0f;

	anglePlayer = 0.0f;
	//vita iniziale
	life = 100;

	//numero colpi a disposizione
	numShotsAvailable = 3;

	//tempo ricarica colpo
	chargingTime = 0.0;

	//tempo ultimo colpo
	timeLastShot = 0.0;


	//inizializzo la lista dei colpi
	for (int i = 0; i < numShot; i++) {
		listShot[i].inizializza();
	}

	//loading meshes with animation
	meshRunning.loadMesh("animation/player_michelle/running/Running.dae");
	meshStanding.loadMesh("animation/player_michelle/standing/Idle.dae");
	meshAttacking.loadMesh("animation/player_michelle/kick/Flying Kick.dae");

}

float angleBetween(const glm::vec3 a, const glm::vec3 b) {

	float angle = atan2(b.x, a.x) - atan2(b.z, a.y);
	return angle;
}

bool checkShotIsAvaiable(int numShot, float chargingTime, float timeLastShot) {

	return true;
}

void player::drawPlayer(Shader animShader, Shader lightShader, glm::mat4 view, glm::vec3 mousePoint) {
	
	animShader.use();
	
	//projection
	glm::mat4 projection = glm::mat4(1.0f);	//identity matrix
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	animShader.setMat4("projection", projection);

	//view
	animShader.setMat4("view", view);
	
	//model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, 0.5f, z));
	model = glm::rotate(model, glm::radians(anglePlayer), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	animShader.setMat4("model", model);

	vector <glm::mat4> transforms;

	if (muoviDx == false && muoviSx == false && muoviSu == false && muoviGiu == false) { //se non mi muovo -> meshStanding
		meshStanding.boneTransform(animationTime_player, transforms);
		glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
			transforms.size(),
			GL_FALSE,
			glm::value_ptr(transforms[0]));
		meshStanding.render();
	}
	else if (muoviDx == true || muoviSx == true || muoviSu == true || muoviGiu == true) { //se mi muovo -> meshRunning
		
		meshRunning.boneTransform(animationTime_player, transforms);
		glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
			transforms.size(),
			GL_FALSE,
			glm::value_ptr(transforms[0]));
		meshRunning.render();

	}



	float mouseX = mousePoint.x;
	float mouseY = mousePoint.z;

	float d1 = mouseX - x;
	float d2 = mouseY - z;

	float angle = atan2(d1, d2);



	//controllo la lista dei colpi e ne setto gli angoli 
	if (startPlayerShot) {
		bool shotIsAvaiable = checkShotIsAvaiable(numShotsAvailable, chargingTime, timeLastShot);
		if (shotIsAvaiable) {
			listShot[numShotsAvailable - 1].x = x;
			listShot[numShotsAvailable - 1].y = y;
			listShot[numShotsAvailable - 1].z = z;
			listShot[numShotsAvailable - 1].startX = x;
			listShot[numShotsAvailable - 1].startZ = z;
			listShot[numShotsAvailable - 1].angle = angle;
			listShot[numShotsAvailable - 1].isShot = true;
			numShotsAvailable = numShotsAvailable - 1;
		}
		startPlayerShot = false;
	}

	if (mouseSxIsSelected) {
		wea->drawTarget(lightShader, view, x, y, z, texturePlayer, angle);
	}

	// material properties
	lightShader.setVec3("material.ambient", 1.0f, 1.0f, 1.0f);
	lightShader.setVec3("material.diffuse", 1.0f, 1.0f, 1.0f);
	lightShader.setVec3("material.specular", 1.0f, 1.0f, 1.0f);
	lightShader.setFloat("material.shininess", 76.8f);


	for (int i = 0; i < numShot; i++) {
		if (listShot[i].isShot) {
			listShot[i].draw(lightShader, texturePlayer);
		}
	}

}
