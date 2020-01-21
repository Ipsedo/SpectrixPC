//
// Created by samuel on 18/11/18.
//

#include <glm/gtc/type_ptr.hpp>
#include "shadow.h"
#include "../utils/graphics/shader.h"
#include "../utils/res.h"

void Shadow::createProgram() {
	mProgram = glCreateProgram();
	GLuint vs = loadShader(GL_VERTEX_SHADER, getShaderFolder() + "/shadow_vs.glsl");
	GLuint fs = loadShader(GL_FRAGMENT_SHADER, getShaderFolder() + "/shadow_fs.glsl");
	glAttachShader(mProgram, vs);
	glAttachShader(mProgram, fs);
	glLinkProgram(mProgram);
}

void Shadow::bind() {
	mVertexHandle = (GLuint) glGetAttribLocation(mProgram, "a_vertex");
	mLightMVPMatrixHandle = (GLuint) glGetUniformLocation(mProgram, "u_depth_mvp");
}

void Shadow::initFrameBuffer() {
// Le tampon d'image, qui regroupe 0, 1, ou plus de textures et 0 ou 1 tampon de profondeur.

	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// Texture de profondeur. Plus lent qu'un tampon de profondeur, mais vous pouvez l'échantillonner plus tard dans votre shader
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 1024, 1024, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

	// Toujours vérifier que le tampon d'image est OK
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		exit(698);
}

void Shadow::draw(GLuint buffer, int size, int stride, glm::mat4 mLightMVPMatrix) {
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glEnableVertexAttribArray(mVertexHandle);
	glVertexAttribPointer(mVertexHandle, size, GL_FLOAT, GL_FALSE,
						  stride, nullptr);
	glUniformMatrix4fv(mLightMVPMatrixHandle, 1, GL_FALSE, glm::value_ptr(mLightMVPMatrix));

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);
	glDrawBuffer(GL_NONE); // Aucun tampon de couleur n'est dessiné
}
