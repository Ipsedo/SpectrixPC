#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <thread>
#include <iostream>

#include "drawable/modelvbo.h"
#include "drawable/objmtlvbo.h"
#include "utils/res.h"

#include "drawable/normalmap.h"

#include "./threads/record_thread.h"

void error_callback(int error, const char *description) {
	fputs(description, stderr);
}

int main(int argc, char **argv) {
	create_record_thread(44100, 256, 2);

	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

	chrono::duration<double> time_span = t1.time_since_epoch();
	srand((unsigned int) time_span.count());

	if (!glfwInit()) {
		fprintf(stderr, "Failed GLFW initialization\n");
		return -1;
	}

	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_SAMPLES, 4);
	GLFWwindow *window;
	window = glfwCreateWindow(1024, 768, "Tutorial 01", nullptr, nullptr);
	if (!window) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetErrorCallback(error_callback);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	//ModelVBO objVBO(getResFolder() + "/models/whale.obj");
	ObjMtlVBO objMtlVBO(getResFolder() + "/models/snow_baleine_obj.obj",
						getResFolder() + "/models/snow_baleine_mtl.mtl",
						true);
	/*NormalMapModel squareMap(getResFolder() + "/models/cube.obj",
							 getResFolder() + "/textures/white.png",
							 getResFolder() + "/textures/151_norm.png");*/

	glm::mat4 projectionMatrix = glm::frustum(-1.f, 1.f, -768.f / 1024.f, 768.f / 1024.f, 1.0f, 50.0f);
	glm::mat4 viewMatrix = glm::lookAt(
			glm::vec3(0., 0., -2.),
			glm::vec3(0., 0., 1.),
			glm::vec3(0, 1, 0)
	);

	glViewport(0, 0, 1024, 768);
	glClearColor(0.5, 0.0, 0.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);

	float angle = 0.0f;
	while (!glfwWindowShouldClose(window)) {
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle += 1e-3, glm::vec3(0.5f, 0.5f, 0.f));
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 2.f));
		glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(5e-2f));

		glm::mat4 modelMatrix = scale * translate * rotation;
		glm::mat4 mvMatrix = viewMatrix * modelMatrix;
		glm::mat4 mvpMatrix = projectionMatrix * mvMatrix;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//objVBO.draw(mvpMatrix, mvMatrix, glm::vec3(50.f*cos(angle),0.f,50.f*sin(angle)));
		objMtlVBO.draw(mvpMatrix, mvMatrix, glm::vec3(0.f, 0.f, 10.f), glm::vec3(0., 0., -2.));
		//squareMap.draw(mvpMatrix, mvMatrix, glm::vec3(0.f), cameraPosition);
		glfwSwapBuffers(window);
		glfwPollEvents();


		this_thread::sleep_for(chrono::milliseconds(1000 / 60));
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
