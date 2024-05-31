#include "Cube.h"
#include <iostream>
#include <cmath>

Cube::Cube() {
}

void Cube::init(float size, int n) {
	verts.reserve(54);
	verts.push_back({ glm::vec3(-1.f*size, -1.f*size,  -1.f*size), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.375f, 0.5f) });
	verts.push_back({ glm::vec3( 1.f *size,-1.f*size,  -1.f*size), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.625f, 0.5f) });
	verts.push_back({ glm::vec3( 1.f *size, 1.f *size, -1.f*size), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.75f, 0.625f)});
	verts.push_back({ glm::vec3(-1.f*size,  1.f *size, -1.f*size), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.375f, 0.75f)});
	verts.push_back({ glm::vec3(-1.f*size, -1.f*size,   1.f *size), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.375f, 0.25f)});
	verts.push_back({ glm::vec3( 1.f *size,-1.f*size,   1.f *size), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.625f, 0.25f)});
	verts.push_back({ glm::vec3( 1.f *size, 1.f *size,  1.f *size), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.625f, 1.0f) });
	verts.push_back({ glm::vec3(-1.f*size,  1.f *size,  1.f *size), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.375f, 1.0f) });
	//verts.push_back({ glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f) }); //Added to make center point!!!
	//CreateCube(size);
	


	for (Vertex ver : verts) {
		glm::vec3 Sphere(0.f);
		float Distance = glm::distance(ver.GetPosition(), glm::vec3(0.2f, 0.2f, 0.2f));
		if(Distance != 0.f) {
			Sphere.x = ver.x / Distance;
			Sphere.y = ver.y / Distance;
			Sphere.z = ver.z / Distance;
		}
		else {
			Sphere.x = ver.x;
			Sphere.y = ver.y;
			Sphere.z = ver.z;
		}

		ver.SetPosition(Sphere);
	}

	unsigned int indices[] = {
		0, 1, 2, 2, 3, 0,
		4, 6, 5, 4, 7, 6,
		0, 3, 7, 7, 4, 0,
		1, 5, 6, 1, 6, 2,
		2, 7, 3, 7, 2, 6,
		0, 4, 1, 1, 4, 5
	};

	CollPoints.push_back(glm::vec3(-2.f, -2.f, -1.0f));
	CollPoints.push_back(glm::vec3(2.f, 0.5f, -3.f));
	CollPoints.push_back(glm::vec3(-2.f, 0.5f, -3.f));
	CollPoints.push_back(glm::vec3(2.f, -2.f, -1.0f));


	for (glm::vec3 point : CollPoints) {
		std::cout << point.x << ", " << point.y << ", " << point.z << "\n";
 	}


	//unsigned int indices[] = {
	//	// Front face
	//0, 1, 2,
	//0, 2, 3,
	//4, 5, 6,
	//4, 6, 7,
	//8, 9, 10,
	//8, 10, 11,
	//12, 13, 14,
	//12, 14, 15,

	//// Right face
	//16, 17, 18,
	//16, 18, 19,
	//20, 21, 22,
	//20, 22, 23,
	//24, 25, 26,
	//24, 26, 27,
	//28, 29, 30,
	//28, 30, 31,

	//// Back face
	//32, 33, 34,
	//32, 34, 35,
	//36, 37, 38,
	//36, 38, 39,
	//40, 41, 42,
	//40, 42, 43,
	//44, 45, 46,
	//44, 46, 47,

	//// Left face
	//48, 49, 50,
	//48, 50, 51,
	//52, 53, 54,
	//52, 54, 55,
	//56, 57, 58,
	//56, 58, 59,
	//60, 61, 62,
	//60, 62, 63,

	//// Top face
	//64, 65, 66,
	//64, 66, 67,
	//68, 69, 70,
	//68, 70, 71,
	//72, 73, 74,
	//72, 74, 75,
	//76, 77, 78,
	//76, 78, 79,

	//// Bottom face
	//80, 81, 82,
	//80, 82, 83,
	//84, 85, 86,
	//84, 86, 87,
	//88, 89, 90,
	//88, 90, 91,
	//92, 93, 94,
	//92, 94, 95
	//};
	

	for (unsigned int in : indices) {
		index.push_back(in);
	}
	SPRING_CONSTANT *= size;
	calculateNormal();
	setSprings();
	setArray();

	for (Vertex ver : verts) {
		ver.SetMass(2.f);
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertsArray), vertsArray, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Vertex positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

Cube::~Cube() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Cube::render(bool simulate) {

	if (simulate) update();

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, 32, GL_UNSIGNED_INT, 0);
	glGetError();

	glBindVertexArray(0);
}

void Cube::update() {

	verletIntegration();
	calculateNormal();
	setArray();

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertsArray), vertsArray); // Update entire buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
}

void Cube::calculateNormal() {
	for (size_t i = 0; i < index.size(); i += 3) {
		glm::vec3 v0 = glm::vec3(verts[index[i]].GetPosition());
		glm::vec3 v1 = glm::vec3(verts[index[i + 1]].GetPosition());
		glm::vec3 v2 = glm::vec3(verts[index[i + 2]].GetPosition());


		glm::vec3 faceNormal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
		for (int j = 0; j < 3; ++j) {
			verts[index[i + j]].normal += faceNormal;
		}
	}

	for (auto& vert : verts) {
		vert.normal = glm::normalize(vert.normal);
	}
}

void Cube::setSprings() {
	//Front

	springs.push_back({ verts[0], verts[1], glm::length(verts[0].GetPosition() - verts[1].GetPosition()), SPRING_CONSTANT});
	springs.push_back({ verts[0], verts[2], glm::length(verts[0].GetPosition() - verts[2].GetPosition()), SPRING_CONSTANT});
	springs.push_back({ verts[0], verts[3], glm::length(verts[0].GetPosition() - verts[3].GetPosition()), SPRING_CONSTANT});
	springs.push_back({ verts[1], verts[2], glm::length(verts[1].GetPosition() - verts[2].GetPosition()), SPRING_CONSTANT});
	springs.push_back({ verts[1], verts[3], glm::length(verts[1].GetPosition() - verts[3].GetPosition()), SPRING_CONSTANT});
	springs.push_back({ verts[2], verts[3], glm::length(verts[2].GetPosition() - verts[3].GetPosition()), SPRING_CONSTANT});

	//Left
	springs.push_back({ verts[0], verts[7], glm::length(verts[0].GetPosition() - verts[7].GetPosition()), SPRING_CONSTANT });
	springs.push_back({ verts[0], verts[4], glm::length(verts[0].GetPosition() - verts[4].GetPosition()), SPRING_CONSTANT });
	springs.push_back({ verts[3], verts[7], glm::length(verts[3].GetPosition() - verts[7].GetPosition()), SPRING_CONSTANT });
	springs.push_back({ verts[3], verts[4], glm::length(verts[3].GetPosition() - verts[4].GetPosition()), SPRING_CONSTANT });
	springs.push_back({ verts[7], verts[4], glm::length(verts[7].GetPosition() - verts[4].GetPosition()), SPRING_CONSTANT });

	// Right
	springs.push_back({ verts[1], verts[5], glm::length(verts[1].GetPosition() - verts[5].GetPosition()), SPRING_CONSTANT });
	springs.push_back({ verts[1], verts[6], glm::length(verts[1].GetPosition() - verts[6].GetPosition()), SPRING_CONSTANT });
	springs.push_back({ verts[5], verts[6], glm::length(verts[5].GetPosition() - verts[6].GetPosition()), SPRING_CONSTANT });
	springs.push_back({ verts[5], verts[2], glm::length(verts[5].GetPosition() - verts[2].GetPosition()), SPRING_CONSTANT });
	springs.push_back({ verts[6], verts[2], glm::length(verts[6].GetPosition() - verts[2].GetPosition()), SPRING_CONSTANT });

	// Back
	springs.push_back({ verts[4], verts[6], glm::length(verts[4].GetPosition() - verts[6].GetPosition()), SPRING_CONSTANT });
	springs.push_back({ verts[4], verts[5], glm::length(verts[4].GetPosition() - verts[5].GetPosition()), SPRING_CONSTANT });
	springs.push_back({ verts[7], verts[6], glm::length(verts[7].GetPosition() - verts[6].GetPosition()), SPRING_CONSTANT });
	springs.push_back({ verts[7], verts[5], glm::length(verts[7].GetPosition() - verts[5].GetPosition()), SPRING_CONSTANT });

	// Bottom
	springs.push_back({ verts[0], verts[5], glm::length(verts[0].GetPosition() - verts[5].GetPosition()), SPRING_CONSTANT });
	springs.push_back({ verts[4], verts[1], glm::length(verts[4].GetPosition() - verts[1].GetPosition()), SPRING_CONSTANT });

	// Top
	springs.push_back({ verts[2], verts[7], glm::length(verts[2].GetPosition() - verts[7].GetPosition()), SPRING_CONSTANT });
	springs.push_back({ verts[3], verts[6], glm::length(verts[3].GetPosition() - verts[6].GetPosition()), SPRING_CONSTANT });

	// Diagonal
	springs.push_back({ verts[0], verts[6], glm::length(verts[0].GetPosition() - verts[6].GetPosition()), SPRING_CONSTANT });
	springs.push_back({ verts[1], verts[7], glm::length(verts[1].GetPosition() - verts[7].GetPosition()), SPRING_CONSTANT });
	springs.push_back({ verts[2], verts[4], glm::length(verts[2].GetPosition() - verts[4].GetPosition()), SPRING_CONSTANT });
	springs.push_back({ verts[3], verts[5], glm::length(verts[3].GetPosition() - verts[5].GetPosition()), SPRING_CONSTANT });

	//// Additional Diagonal
	//springs.push_back({ verts[0], verts[5], glm::length(verts[0].GetPosition() - verts[5].GetPosition()), SPRING_CONSTANT });
	//springs.push_back({ verts[1], verts[4], glm::length(verts[1].GetPosition() - verts[4].GetPosition()), SPRING_CONSTANT });
	//springs.push_back({ verts[2], verts[6], glm::length(verts[2].GetPosition() - verts[6].GetPosition()), SPRING_CONSTANT });
	//springs.push_back({ verts[3], verts[7], glm::length(verts[3].GetPosition() - verts[7].GetPosition()), SPRING_CONSTANT });

	
	// Initialize springs between adjacent vertices of each face
	//for (size_t i = 0; i < verts.size(); ++i) {
	//	for (size_t j = i + 1; j < verts.size(); ++j) {
	//		float length = glm::length(verts[i].GetPosition() - verts[j].GetPosition());

	//		springs.push_back({ verts[i], verts[j], length, SPRING_CONSTANT });
	//	}
	//}
}



void Cube::setArray() {
	for (int i = 0; i < verts.size(); ++i) {
		vertsArray[i * 8] = verts[i].x; // x
		vertsArray[i * 8 + 1] = verts[i].y; // y
		vertsArray[i * 8 + 2] = verts[i].z; // z
		vertsArray[i * 8 + 3] = verts[i].normal.x;
		vertsArray[i * 8 + 4] = verts[i].normal.y;
		vertsArray[i * 8 + 5] = verts[i].normal.z;
		vertsArray[i * 8 + 6] = verts[i].uv.x;
		vertsArray[i * 8 + 7] = verts[i].uv.y;
	}
}

void Cube::verletIntegration() {

	for (int i = 0; i < verts.size(); ++i) {
		//Add all acceleration
		Vertex& vert = verts[i];
		vert.SetAcceleration(glm::vec3(0.f)); //Set the current vertex acceleration to zero
		vert.AddAcceleration(calculateForces() + vert.externalForce); //Calculate forces -> Only gravity at the moment. Externalforce is jump and other movement.

		glm::vec3 CurrentPos = vert.GetPosition();
		checkCollision(CurrentPos, vert, false); //<-To check if the current vertex already hits a surface, simulate a bit of friction
		vert.externalForce = glm::vec3(0.f);
	}

	//Calculate springforce
	springForce();
		
	
	for (int i = 0; i < verts.size(); ++i) {
		//Velocity Verlet
		Vertex& vert = verts[i];

		glm::vec3 TempVel = (vert.GetPosition() - vert.GetOldPos());
		TempVel *= 0.98f;

		glm::vec3 newPos =  vert.GetPosition() + TempVel + vert.GetAcceleration() * DELTATIME * DELTATIME * 0.5f;

		checkCollision(newPos, vert, true); //Check if the new position collide with something and adjust it
		vert.SetOldPos(vert.GetPosition()); //Set the old position to the current position
		vert.SetPosition(newPos); //Set the new position

		//Cap velocity
		glm::vec3 newVel = (newPos - vert.GetOldPos()) / DELTATIME * 0.5f;

		float maxVel = 8.f;
		float currentVelMag = glm::length(newVel);

		if (currentVelMag > maxVel) {
			newVel = glm::normalize(newVel) * maxVel;
		}

		vert.SetVelocity(newVel);

		/*std::cout << vert.GetPosition().x << ", " << vert.GetPosition().y << ", " << vert.GetPosition().z << "\n";*/
	}
};


glm::vec3 Cube::calculateForces() {
	glm::vec3 gravAcc = glm::vec3(0.f, GRAVITY, 0.f);
	return gravAcc;
};

void Cube::checkCollision(glm::vec3& position, Vertex& vert, bool check) {
	bool collision = false;
	float velocityMag = glm::length(vert.GetVelocity());
	glm::vec3 motionDir = glm::normalize(vert.GetVelocity());
	float thresholdVel = 0.01f;
	
	//std::cout << position.x << "\n";
	glm::vec3 Temp(position.x, position.y, position.z);
	//std::cout << Temp.x << "\n";


	if (position.y <= -2.f) {
		position.y = -2.f;
		collision = true;
	} 
	else if (position.y >= 2.f) {
		position.y = 2.f;
		collision = true;
	}
    if (position.x < -2.f) {
		position.x = -2.f;
		collision = true;
	}
	else if (position.x > 2.f) {
		position.x = 2.f;
		collision = true;

	}
	if (position.z < -2.f) {
		position.z = -2.f;
		collision = true;

	}
	else if (position.z > 2.f) {
		position.z = 2.f;
		collision = true;
	}

	//if (check && !collision){
	//	Temp = CollidesWithRamp(Temp, collision);
	//	position.x = Temp.x;
	//	position.y = Temp.y;
	//	position.z = Temp.z;
	//}

	
	
	if (collision) {

		float dynamicFriction;
		glm::vec3 frictionForce;

		if (velocityMag < thresholdVel) {
			dynamicFriction = STATICFRICTION * GRAVITY;
		}
		else {
			dynamicFriction = KINETICFRICTION * GRAVITY;
		}

		frictionForce = -dynamicFriction * motionDir;

		glm::vec3 newVel = vert.GetVelocity() + frictionForce * DELTATIME;
		
		if (glm::dot(newVel, motionDir) < 0.f) {
			newVel = glm::vec3(0.f);
		}

		vert.AddVelocity(newVel);
	}
}

void Cube::springForce() {
	for (int i = 0; i < springs.size(); ++i) {
		
		Spring& spring = springs[i];

		glm::vec3 displacement = spring.vert2.GetPosition() - spring.vert1.GetPosition();
		float currentLength = glm::length(displacement);
		
		
		if (currentLength < spring.RestLength * 0.4f) {
			displacement = glm::normalize(displacement) * spring.RestLength * 0.4f;
		}

		float springForce = springs[i].stiffness * (currentLength - spring.RestLength);
		glm::vec3 distNormal = glm::normalize(displacement);
		
		
		spring.vert1.AddAcceleration((springForce / spring.vert1.GetMass() - DAMPING * spring.vert1.GetVelocity())/ currentLength * distNormal);
		spring.vert2.AddAcceleration((-springForce / spring.vert2.GetMass() - DAMPING * spring.vert2.GetVelocity())/ currentLength * distNormal);
			
	}
}

//Input methods
void Cube::jump() {
	for (Vertex& ver : verts) {
		ver.AddToExternalForce(glm::vec3(0.f, jumpHeight, 0.f));
	}
}

void Cube::move(int dir) {
	for (Vertex& ver : verts) {
		if (dir > 0) {
			ver.AddToExternalForce(glm::vec3(moveSpeed, 0.0f, 0.0f));
		}
		else {
			ver.AddToExternalForce(glm::vec3(-moveSpeed, 0.0f, 0.0f));
		}
	}
	
}

void Cube::SetSpringConstant(float amount, bool& bOnce) {
	if (!bOnce) {
		bOnce = true;
		SPRING_CONSTANT += amount;
		for (Spring& spring : springs) {
			spring.stiffness = SPRING_CONSTANT;
		}
		std::cout << SPRING_CONSTANT << "\n";
	}


}

void Cube::CreateCube(float size) {
	// Front face
	verts.push_back({ glm::vec3(-0.5f * size, 0.5f * size, 0.5f * size), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f) }); // Top-left corner
	verts.push_back({ glm::vec3(-0.5f * size, -0.5f * size, 0.5f * size), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // Bottom-left corner
	verts.push_back({ glm::vec3(0.5f * size, -0.5f * size, 0.5f * size), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f) }); // Bottom-right corner
	verts.push_back({ glm::vec3(0.5f * size, 0.5f * size, 0.5f * size), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) }); // Top-right corner

	// Vertices on the edges
	verts.push_back({ glm::vec3(-0.5f * size, 0.0f, 0.5f * size), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 0.5f) }); // Left edge
	verts.push_back({ glm::vec3(0.0f, -0.5f * size, 0.5f * size), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 0.0f) }); // Bottom edge
	verts.push_back({ glm::vec3(0.5f * size, 0.0f, 0.5f * size), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.5f) }); // Right edge
	verts.push_back({ glm::vec3(0.0f, 0.5f * size, 0.5f * size), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f) }); // Top edge

	// Vertex at the center
	verts.push_back({ glm::vec3(0.0f, 0.0f, 0.5f * size), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 0.5f) }); // Center vertex

	// Back face
	verts.push_back({ glm::vec3(-0.5f * size, 0.5f * size, -0.5f * size), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f) }); // Top-left corner
	verts.push_back({ glm::vec3(-0.5f * size, -0.5f * size, -0.5f * size), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f) }); // Bottom-left corner
	verts.push_back({ glm::vec3(0.5f * size, -0.5f * size, -0.5f * size), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f) }); // Bottom-right corner
	verts.push_back({ glm::vec3(0.5f * size, 0.5f * size, -0.5f * size), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f) }); // Top-right corner

	// Vertices on the edges
	verts.push_back({ glm::vec3(-0.5f * size, 0.0f, -0.5f * size), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.5f, 0.5f) }); // Left edge
	verts.push_back({ glm::vec3(0.0f, -0.5f * size, -0.5f * size), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.5f, 0.0f) }); // Bottom edge
	verts.push_back({ glm::vec3(0.5f * size, 0.0f, -0.5f * size), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.5f) }); // Right edge
	verts.push_back({ glm::vec3(0.0f, 0.5f * size, -0.5f * size), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.5f, 1.0f) }); // Top edge

	// Vertex at the center
	verts.push_back({ glm::vec3(0.0f, 0.0f, -0.5f * size), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.5f, 0.5f) }); // Center vertex

	// Top face
	verts.push_back({ glm::vec3(-0.5f * size, 0.5f * size, -0.5f * size), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f) }); // Back-left corner
	verts.push_back({ glm::vec3(-0.5f * size, 0.5f * size, 0.5f * size), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) }); // Front-left corner
	verts.push_back({ glm::vec3(0.5f * size, 0.5f * size, 0.5f * size), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) }); // Front-right corner
	verts.push_back({ glm::vec3(0.5f * size, 0.5f * size, -0.5f * size), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f) }); // Back-right corner

	// Vertices on the edges
	verts.push_back({ glm::vec3(-0.25f * size, 0.5f * size, -0.25f * size), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.5f, 0.75f) }); // Back edge
	verts.push_back({ glm::vec3(-0.5f * size, 0.5f * size, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.25f, 0.5f) }); // Left edge
	verts.push_back({ glm::vec3(-0.25f * size, 0.5f * size, 0.5f * size), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.5f, 0.25f) }); // Front edge
	verts.push_back({ glm::vec3(0.0f, 0.5f * size, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.75f, 0.5f) }); // Right edge

	// Vertex at the center
	verts.push_back({ glm::vec3(0.0f, 0.5f * size, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.5f, 0.5f) }); // Center vertex

	// Bottom face
	verts.push_back({ glm::vec3(-0.5f * size, -0.5f * size, -0.5f * size), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f) }); // Back-left corner
	verts.push_back({ glm::vec3(-0.5f * size, -0.5f * size, 0.5f * size), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f) }); // Front-left corner
	verts.push_back({ glm::vec3(0.5f * size, -0.5f * size, 0.5f * size), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f) }); // Front-right corner
	verts.push_back({ glm::vec3(0.5f * size, -0.5f * size, -0.5f * size), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f) }); // Back-right corner

	// Vertices on the edges
	verts.push_back({ glm::vec3(-0.25f * size, -0.5f * size, -0.25f * size), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.5f, 0.75f) }); // Back edge
	verts.push_back({ glm::vec3(-0.5f * size, -0.5f * size, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.25f, 0.5f) }); // Left edge
	verts.push_back({ glm::vec3(-0.25f * size, -0.5f * size, 0.5f * size), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.5f, 0.25f) }); // Front edge
	verts.push_back({ glm::vec3(0.0f, -0.5f * size, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.75f, 0.5f) }); // Right edge

	// Vertex at the center
	verts.push_back({ glm::vec3(0.0f, -0.5f * size, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.5f, 0.5f) }); // Center vertex

	// Right face
	verts.push_back({ glm::vec3(0.5f * size, 0.5f * size, -0.5f * size), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f) }); // Top-right corner
	verts.push_back({ glm::vec3(0.5f * size, 0.5f * size, 0.5f * size), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) }); // Bottom-right corner
	verts.push_back({ glm::vec3(0.5f * size, -0.5f * size, 0.5f * size), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) }); // Bottom-left corner
	verts.push_back({ glm::vec3(0.5f * size, -0.5f * size, -0.5f * size), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f) }); // Top-left corner

	// Vertices on the edges
	verts.push_back({ glm::vec3(0.5f * size, 0.25f * size, -0.25f * size), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.5f, 0.75f) }); // Top edge
	verts.push_back({ glm::vec3(0.5f * size, -0.5f * size, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.25f, 0.5f) }); // Bottom edge
	verts.push_back({ glm::vec3(0.5f * size, -0.25f * size, 0.5f * size), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.5f, 0.25f) }); // Front edge
	verts.push_back({ glm::vec3(0.5f * size, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.75f, 0.5f) }); // Back edge

	// Vertex at the center
	verts.push_back({ glm::vec3(0.5f * size, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.5f, 0.5f) }); // Center vertex

	// Left face
	verts.push_back({ glm::vec3(-0.5f * size, 0.5f * size, -0.5f * size), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f) }); // Top-left corner
	verts.push_back({ glm::vec3(-0.5f * size, 0.5f * size, 0.5f * size), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) }); // Bottom-left corner
	verts.push_back({ glm::vec3(-0.5f * size, -0.5f * size, 0.5f * size), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) }); // Bottom-right corner
	verts.push_back({ glm::vec3(-0.5f * size, -0.5f * size, -0.5f * size), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f) }); // Top-right corner

	// Vertices on the edges
	verts.push_back({ glm::vec3(-0.5f * size, 0.25f * size, -0.25f * size), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.5f, 0.75f) }); // Top edge
	verts.push_back({ glm::vec3(-0.5f * size, -0.5f * size, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.25f, 0.5f) }); // Bottom edge
	verts.push_back({ glm::vec3(-0.5f * size, -0.25f * size, 0.5f * size), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.5f, 0.25f) }); // Front edge
	verts.push_back({ glm::vec3(-0.5f * size, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.75f, 0.5f) }); // Back edge

	// Vertex at the center
	verts.push_back({ glm::vec3(-0.5f * size, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.5f, 0.5f) }); // Center vertex
}

glm::vec3 Cube::CollidesWithRamp(glm::vec3 position, bool& collision) {
	//Triangle 1
	{
		glm::vec3 v0 = CollPoints[1] - CollPoints[0];
		glm::vec3 v1 = CollPoints[2] - CollPoints[0];
		/*std::cout << position.x << ", " << position.y << ", " << position.z << "\n";*/
		glm::vec3 v2 = position - CollPoints[0];

		float d00 = glm::dot(v0, v0);
		
		float d01 = glm::dot(v0, v1);
		float d11 = glm::dot(v1, v1);
		float d20 = glm::dot(v2, v0);
		float d21 = glm::dot(v2, v1);

		float denom = d00 * d11 - d01 * d01;
		
	
		float v = (d11 * d20 - d01 * d21) / denom;
		float w = (d00 * d21 - d01 * d20) / denom;
		float u = 1.0f - v - w;
	
		if ((u >= 0.0f) && (v >= 0.0f) && (w >= 0.0f) && (u <= 1.0f) && (v <= 1.0f) && (w <= 1.0f)) {
			collision = true;
			 
			return u * CollPoints[0] + v * CollPoints[1] + w * CollPoints[2];
		}
	}

	//Triangle 2
	{
		glm::vec3 v0 = CollPoints[3] - CollPoints[0];
		glm::vec3 v1 = CollPoints[2] - CollPoints[0];
		glm::vec3 v2 = position - CollPoints[0];
		
		float d00 = glm::dot(v0, v0);
		float d01 = glm::dot(v0, v1);
		float d11 = glm::dot(v1, v1);
		float d20 = glm::dot(v2, v0);
		float d21 = glm::dot(v2, v1);
		float denom = d00 * d11 - d01 * d01;

		float v = (d11 * d20 - d01 * d21) / denom;
		float w = (d00 * d21 - d01 * d20) / denom;
		float u = 1.0f - v - w;
			
		if ((u >= 0.0f) && (v >= 0.0f) && (w >= 0.0f) && (u <= 1.0f) && (v <= 1.0f) && (w <= 1.0f)) {
			collision = true; 
			return u * CollPoints[0] + v * CollPoints[3] + w * CollPoints[2];
		}
	}
	collision = false;
	return position;
}
