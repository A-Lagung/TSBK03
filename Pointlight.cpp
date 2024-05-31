#include "Pointlight.h"

Pointlight::Pointlight(glm::vec3 _position, glm::vec3 _color, float _strength) : Position(_position), Color(_color), Strength(_strength) {
	if (Color.x > 1.f || Color.y > 1.f || Color.z > 1.f) {
		Color /= 255;
		glm::ceil(Color);
	}

	SpecularColor = Color + glm::vec3(0.5f);
	
	glm::clamp(SpecularColor, 0.f, 1.f);

	if (Strength > 0.f && Strength < 0.2f) {
		Linear = 0.07f;
		Quadratic = 0.017f;
	}
	else if (Strength >= 0.2f && Strength < 0.4f) {
		Linear = 0.09f;
		Quadratic = 0.032f;
	}
	else if (Strength >= 0.4f && Strength < 0.6f) {
		Linear = 0.14f;
		Quadratic = 0.07f;
	}
	else if (Strength >= 0.6f && Strength < 0.8f) {
		Linear = 0.22f;
		Quadratic = 0.2f;
	}
	else if (Strength >= 0.8f && Strength < 1.f) {
		Linear = 0.35f;
		Quadratic = 0.44f;
	}
	else {
		Linear = 0.7f;
		Quadratic = 1.8f;
	}
	
};