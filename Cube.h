#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Definitions.h"
#include "glm/glm.hpp"
struct Spring;


struct Vertex {
	glm::vec3 position;
	glm::vec3 oldPos;
	glm::vec3 normal;
	glm::vec2 uv;
	glm::vec3 velocity = glm::vec3(0.f);
	glm::vec3 acc = glm::vec3(0.f);
	glm::vec3 externalForce = glm::vec3(0.f);
	float mass = 1.f;
	float x, y, z;
	
	Vertex(const glm::vec3& pos, const glm::vec3& norm, glm::vec2 st) : position(pos), normal(norm), uv(st) {
		x = pos.x;
		y = pos.y;
		z = pos.z;
		SetOldPos(pos);
	};

	glm::vec3 GetPosition() { return position; };

	void SetPosition(glm::vec3 NewPos) { 
		position = NewPos;
		x = position.x;
		y = position.y;
		z = position.z;
	}

	void SetOldPos(glm::vec3 OldPos) { oldPos = OldPos; };
	glm::vec3 GetOldPos() { return oldPos; };

	void SetVelocity(glm::vec3 NewVelocity) { velocity = NewVelocity; };
	glm::vec3 GetVelocity() { return velocity; };


	void SetAcceleration(glm::vec3 NewAcc) { acc = NewAcc; };
	void AddAcceleration(glm::vec3 AddAcc) { acc += AddAcc; };

	void AddVelocity(glm::vec3 AddVel) { velocity += AddVel; };

	void AddToExternalForce(glm::vec3 Add) { externalForce += Add; };

	glm::vec3 GetAcceleration() { return acc; };
	
	void SetMass(float in) { mass = in; };
	float GetMass() { return mass; };
};

struct Spring {
	Vertex& vert1;
	Vertex& vert2;
	float RestLength;
	float stiffness;
};

class Cube {
public:
	Cube();
	void init(float size, int n);
	~Cube();
	void render(bool simulate);
	void jump();
	void move(int direction);
	void SetSpringConstant(float amount, bool& bOnce);
	glm::vec3 CollidesWithRamp(glm::vec3 position, bool& collision);



private:
	void verletIntegration();
	void calculateNormal();
	void setSprings();
	void setArray();
	glm::vec3 calculateForces();
	void springForce();
	void checkCollision(glm::vec3& position, Vertex& vert, bool check);
	void update();
	void CreateCube(float size);

	std::vector<Vertex> verts;
	std::vector<Spring> springs;
	std::vector <unsigned int> index;

	float SPRING_CONSTANT = 600.f;
	float vertsArray[64];
	float jumpHeight = 200.f;
	float moveSpeed = 30.f;

	//For demo purpose, should not be hardcoded in.
	std::vector<glm::vec3> CollPoints;



	unsigned int VAO, VBO, EBO;
};

