#pragma once
#include "model.h"
#include "weapon.h"
#include "path.h"
#include "skinned_mesh.h"
#include "globalData.h"

class villain {

public:

	villain() {}

	villain(float x, float y, float z) : x(x), y(y), z(z) {}

	//coordinate
	float x;
	float y;
	float z;

	int botType;


	float rotationAngle; //angolo di rotazione corrente 

	// ---- variabili per gestire le rotazioni
	float angleToReach;  //angolo di rotazione che deve raggiungere quando effettua una rotazione
	bool sensoOrario;    //senso di rotazione 

	int old_direction; //Direzione da cui il bot arriva 
	float path_currentStep; //contatore dello step iesimo in cui si trova il bot 
	bool isOnPath; //true se � nella direzione (di rotazione) corretta del path -> viene setta a false quando il bot attacca, poich� cambia la rotazione verso il player

	int life; //vita del bot (cambia per modello di bot)
	float damage; //danno del bot (cambia per modello di bot)

	// modelli 3D con scheletro e animazione
	SkinnedMesh meshWalking;
	SkinnedMesh meshAttacking;
	SkinnedMesh meshHit;
	SkinnedMesh meshDead;

	// booleani per le azioni del bot
	bool animation_botWalking;
	bool animation_botAttacking;
	bool animation_botHit;
	bool animation_botDead;
	bool isDead;
	bool isColliding_vsPlayer;

	// tempo per le animazioni
	float animationTime_botWalking;
	float animationTime_botAttacking;
	float animationTime_botHit;
	float animationTime_botDead;
	bool soundWalkingAttacking;

	//Texture barra vita
	 unsigned int textureLifeVillain;
	 unsigned int textureShadow;

	
	//weapon* weapon;
	path* percorso;
	player* p;

	//Prototipi
	void drawVillain(Shader animShader , Shader simpleShader);
	void drawLifeVillain(Shader simpleShader);//disegna life
	void drawShadowVillain(Shader simpleShader);//disegna ombra
	void animate(Shader animShader);
	void initModel_Zombie1();
	void initModel_Zombie2();
	void initModel_Zombie3();
	void initVillain(path* path);


	//GET e SET
	float getX() {
		return x;
	}

	float getY() {
		return y;
	}

	float getZ() {
		return z;
	}

	float getRotationAngle() {
		return rotationAngle;
	}

	float getPath_currentStep() {
		return path_currentStep;
	}

	path* getPath() {
		return percorso;
	}

	void setX(float posx) {
		x = posx;
	}

	void setY(float posy) {
		y = posy;
	}

	void setZ(float posz) {
		z = posz;
	}

	void setRotationAngle(float angle) {
		rotationAngle = angle;
	}

	void setPath_currentStep(float valore) {
		path_currentStep = valore;
	}

};

void villain::initVillain(path* path) {
	
	if (botType == ZOMBIE_PRISONER) {
		life = ZOMBIE_PRISONER_LIFE;
		damage = ZOMBIE_PRISONER_DAMAGE;
	}
	else if (botType == ZOMBIE_DERRICK) {
		life = ZOMBIE_DERRICK_LIFE;
		damage = ZOMBIE_DERRICK_DAMAGE;
	}
	else if (botType == ZOMBIE_COP) {
		life = ZOMBIE_COP_LIFE;
		damage = ZOMBIE_COP_DAMAGE;
	}

	//assegno il path al bot
	percorso = path;

	//inizializzo le coordinate di spawn
	x = path->path_map[1].x;
	z = path->path_map[1].y;

	old_direction = path->path_StartDirectionBot; //setto la direzione di movimento iniziale 
	rotationAngle = path->path_startRotationBot;  //setto la rotazione iniziale

	angleToReach = rotationAngle;

	//setto lo step corrente (relativo al path) del villain
	path_currentStep = 1;

	isOnPath = true;

	isDead = false;
	isColliding_vsPlayer = false;

	animation_botWalking = true;
	animation_botHit = false;
	animation_botDead = false;
	animation_botAttacking = false;

	animationTime_botWalking = 0.0f;
	animationTime_botAttacking = 0.0f;
	animationTime_botHit = 0.08f;
	animationTime_botDead = 0.0f;

	soundWalkingAttacking = false;
}

void villain::initModel_Zombie1() {

	meshWalking.loadMesh("animation/1_zombie_prisoner/walking/Walking.dae");
	meshAttacking.loadMesh("animation/1_zombie_prisoner/attack/Zombie Punching.dae");
	meshHit.loadMesh("animation/1_zombie_prisoner/hit/Zombie Reaction Hit.dae");
	meshDead.loadMesh("animation/1_zombie_prisoner/dead/Zombie Death.dae");

	botType = ZOMBIE_PRISONER;
}

void villain::initModel_Zombie2() {

	meshWalking.loadMesh("animation/2_zombie_derrick/walking/Walking.dae");
	meshAttacking.loadMesh("animation/2_zombie_derrick/attack/Zombie Attack.dae");
	meshHit.loadMesh("animation/2_zombie_derrick/hit/Zombie Reaction Hit.dae");
	meshDead.loadMesh("animation/2_zombie_derrick/dead/Zombie Dying.dae");

	botType = ZOMBIE_DERRICK;
}

void villain::initModel_Zombie3() {

	meshWalking.loadMesh("animation/3_zombie_cop/walking/Walking.dae");
	meshAttacking.loadMesh("animation/3_zombie_cop/attack/Zombie Attack.dae");
	meshHit.loadMesh("animation/3_zombie_cop/hit/Zombie Reaction Hit.dae");
	meshDead.loadMesh("animation/3_zombie_cop/dead/Zombie Dying.dae");
	
	botType = ZOMBIE_COP;
}


void villain::drawVillain(Shader animShader, Shader simpleShader){

	animShader.use();

	//model
	glm::mat4 model = glm::mat4(UNIT);
	model = glm::translate(model, glm::vec3(x, 0.5f, z));
	model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(0.0f, UNIT, 0.0f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	animShader.setMat4("model", model);

	// material properties
	animShader.setVec3("material.ambient", UNIT, UNIT, UNIT);
	animShader.setVec3("material.diffuse", UNIT, UNIT, UNIT);
	animShader.setVec3("material.specular", UNIT, UNIT, UNIT);
	animShader.setFloat("material.shininess", 76.8f);

	animate(animShader); //animazione
	drawShadowVillain(simpleShader);

	drawLifeVillain(simpleShader);
}

void villain::drawShadowVillain(Shader simpleShader) {

	simpleShader.use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, textureShadow);
	glBindVertexArray(cubeVAO);

	//simpleShader.setVec3("colorcube", UNIT, 0.0f, 0.0f);
	glm::mat4 modelSV = glm::mat4(UNIT);


	modelSV = glm::translate(modelSV, glm::vec3(x, y + 0.55f, z));
	modelSV = glm::rotate(modelSV, 3.14f / 2.0f, glm::vec3(0.0f, UNIT, 0.0f));
	modelSV = glm::translate(modelSV, glm::vec3(0.0f, 0.0f, 0.0f));
	modelSV = glm::scale(modelSV, glm::vec3(1.5f, 0.02f, 1.5f));

	simpleShader.setMat4("model", modelSV);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisable(GL_BLEND);
}

void villain::drawLifeVillain(Shader simpleShader) {
	
	simpleShader.use();
	float lifeMax;

	if (botType == ZOMBIE_PRISONER) {
		lifeMax = ZOMBIE_PRISONER_LIFE;
	}
	else if (botType == ZOMBIE_DERRICK) {
		lifeMax = ZOMBIE_DERRICK_LIFE;
	}
	else if (botType == ZOMBIE_COP) {
		lifeMax = ZOMBIE_COP_LIFE;
	}

	float offSet = 0.0f;

	if (life != lifeMax) {
		offSet = ((lifeMax - life) / 2) / lifeMax;
	}

	float lifeLenght = life / lifeMax;


	if (life < 0.0f) {
		lifeLenght = 0.0f;
	}
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureLifeVillain);
	glBindVertexArray(cubeVAO);

	//lightShader.setVec3("colorcube", UNIT, 0.0f, 0.0f);
	glm::mat4 modelLife = glm::mat4(UNIT);

	modelLife = glm::translate(modelLife, glm::vec3(x - offSet, y + 2.5f, z));
	modelLife = glm::rotate(modelLife, 3.14f / 2.0f, glm::vec3(UNIT, 0.0f, 0.0f));
	modelLife = glm::translate(modelLife, glm::vec3(0.0f, 0.0f, 0.0f));
	modelLife = glm::scale(modelLife, glm::vec3(lifeLenght, 0.01f, 0.15f));

	simpleShader.setMat4("model", modelLife);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void villain::animate(Shader animShader) {

	vector <glm::mat4> transforms;

	if (animation_botWalking && !animation_botHit && !animation_botAttacking && !animationTime_botDead) {
		meshWalking.boneTransform(animationTime_botWalking, transforms);
		glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
			transforms.size(),
			GL_FALSE,
			glm::value_ptr(transforms[0]));
		meshWalking.render();
	}
	else if (!animation_botWalking && animation_botAttacking && !animation_botHit && !animationTime_botDead) {
		meshAttacking.boneTransform(animationTime_botAttacking, transforms);
		glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
			transforms.size(),
			GL_FALSE,
			glm::value_ptr(transforms[0]));
		meshAttacking.render();
	}
	else if (((animation_botHit && animation_botWalking) || (animation_botHit && animation_botAttacking)) && !animation_botDead ) {
		meshHit.boneTransform(animationTime_botHit, transforms);
		glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
			transforms.size(),
			GL_FALSE,
			glm::value_ptr(transforms[0]));
		meshHit.render();
	}

	else if (animation_botDead) {
		meshDead.boneTransform(animationTime_botDead, transforms);
		glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
			transforms.size(),
			GL_FALSE,
			glm::value_ptr(transforms[0]));
		meshDead.render();
	}

}

