#include "Room.h"

Room::Room(float size) {
	//Set up walls
    GLfloat vertices[] = {
        // Floor
        -size, -size, -size,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // 0
         size, -size, -size,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // 1
         size, -size,  size,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // 2
        -size, -size,  size,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // 3

        // Ceiling
        -size,  size, -size,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // 4
         size,  size, -size,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 5
         size,  size,  size,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // 6
        -size,  size,  size,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // 7

        // Left wall
        -size, -size, -size,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 8
        -size, -size,  size,  -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 9
        -size,  size,  size,  -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 10
        -size,  size, -size,  -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // 11

        // Right wall
         size, -size, -size,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 12
         size, -size,  size,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 13
         size,  size,  size,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 14
         size,  size, -size,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // 15

         // Back wall
         -size, -size, -size,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // 16
          size, -size, -size,  0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // 17
          size,  size, -size,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // 18
         -size,  size, -size,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f  // 19
    };

    // Use a VAO to encapsulate all vertex attribute state
  
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create a VBO and bind it to GL_ARRAY_BUFFER
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copy vertices data into VBO's memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Set the normal attributes pointers
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Set the texture coordinate attribute pointers
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);


}

void Room::render(bool bSimulate) {
    // Unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Draw the cube
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);  // Floor
    glDrawArrays(GL_TRIANGLE_FAN, 4, 4);  // Ceiling
    glDrawArrays(GL_TRIANGLE_FAN, 8, 4);  // Left wall
    glDrawArrays(GL_TRIANGLE_FAN, 12, 4); // Right wall
    glDrawArrays(GL_TRIANGLE_FAN, 16, 4); // Back wall
    glBindVertexArray(0);

 
}