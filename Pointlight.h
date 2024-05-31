#pragma once
#include <glm/glm.hpp>

class Pointlight {
public:
	Pointlight(glm::vec3 _position, glm::vec3 _color, float _strength);
	glm::vec3 GetPosition() { return Position; };
	glm::vec3 GetColor() { return Color; };
	float GetStrength() { return Strength; };
	glm::vec3 GetSpecularColor() { return SpecularColor; };
	float GetLinear() { return Linear; };
	float GetQuadratic() { return Quadratic; };

private:
	glm::vec3 Position;
	glm::vec3 Color;
	glm::vec3 SpecularColor;

	float Constant = 1.0f;
	float Linear;
	float Quadratic;
	
	float Strength;
};