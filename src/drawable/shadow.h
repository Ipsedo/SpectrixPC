//
// Created by samuel on 18/11/18.
//

#ifndef MEDIEFIGHT_SHADOW_H
#define MEDIEFIGHT_SHADOW_H

#include <glm/glm.hpp>
#include <GL/glew.h>

class Shadow {
private:

	GLuint mProgram;
	GLuint mVertexHandle;
	GLuint mLightMVPMatrixHandle;

	GLuint framebuffer;
	GLuint depthTexture;

	void createProgram();
	void bind();
	void initFrameBuffer();

public:
	void draw(GLuint buffer, int size, int stride, glm::mat4 mLightMVPMatrix);
};


#endif //MEDIEFIGHT_SHADOW_H
