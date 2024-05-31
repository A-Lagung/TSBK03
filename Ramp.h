#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Definitions.h"
#include "glm/glm.hpp"

class Ramp {
public:
	Ramp(float size);
	void render(bool bSimulate);

private:
	GLuint VAO, VBO;
};
