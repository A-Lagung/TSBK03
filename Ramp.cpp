#include "Ramp.h"

Ramp::Ramp(float size) {
    GLfloat vertices[] = {
        // Positions           // Normals          // UVs
        -1.0f*size, -1.0f*size,  -0.5f*size,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,  // Vertex A
         1.0f*size,  0.25f*size, -1.5f*size,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,  // Vertex B
        -1.0f*size,  0.25f*size, -1.5f*size,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,  // Vertex C

        -1.0f*size, -1.0f*size,  -0.5f*size,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,  // Vertex D (same as A)
         1.0f*size, -1.0f*size,  -0.5f*size,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,  // Vertex E
         1.0f*size,  0.25f*size, -1.5f*size,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f   // Vertex F (same as B)
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

void Ramp::render(bool bSimulate) {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}