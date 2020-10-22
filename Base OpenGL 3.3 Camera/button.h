#pragma once
#include "cube.h"
#include "model.h"

class button
{
public:

	button(){}

	button(float posx, float posy, float posz, float d, float a, float rotatex, float rotatey, float rotatez) {
		x = posx;
		y = posy;
		z = posz;

		dim = d;

		angle = a;
		rotate_x = rotatex;
		rotate_y = rotatey;
		rotate_z = rotatez;
	}

	float x;
	float y;
	float z;

	float dim;

	float angle;
	float rotate_x;
	float rotate_y;
	float rotate_z;

	Model* buttonSelection;

	bool isSelected;

	void init(string path_button);
	void drawButton(Shader shader);

};

void button::init(string path_button) {

	isSelected = false;
	buttonSelection = new Model();
	buttonSelection->loadModel(path_button);

}

void button::drawButton(Shader shader) {

	shader.use();

	// material properties
	shader.setVec3("material.ambient", 0.9f, 0.9f, 0.9f);
	shader.setVec3("material.diffuse", 1.0f, 1.0f, 1.0f);
	shader.setVec3("material.specular", 1.0f, 1.0f, 1.0f);
	shader.setFloat("material.shininess", 76.8f);

	if (!isSelected) {	
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(x, y, z));
		model = glm::rotate(model, angle, glm::vec3(rotate_x, rotate_y, rotate_z));
		model = glm::scale(model, glm::vec3(dim, dim, dim));
		shader.setMat4("model", model);

		buttonSelection->Draw(shader);
	}
	else if (isSelected) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(x, y - 0.1f, z));
		model = glm::rotate(model, angle, glm::vec3(rotate_x, rotate_y, rotate_z));
		model = glm::scale(model, glm::vec3(dim, dim, dim));
		shader.setMat4("model", model);

		buttonSelection->Draw(shader);
	}



}




