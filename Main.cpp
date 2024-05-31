#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Cube.h"
#include "Room.h"
#include "Ramp.h"
#include "Pointlight.h"

#include <iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void processInput(GLFWwindow* window);
void LoadImage(int& width, int& height, int& nrChannels, bool flip, std::string imageToLoad, GLuint& TextureID, GLuint TextureUnit);

// Constants
const int WIDTH = 800;
const int HEIGHT = 600;

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 8.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// simulate

bool bSimulate = true;
bool SimulatedPressed = false;
bool SetSpringPressed = false;

Cube cube;
Pointlight light(glm::vec3(0.f, 1.9f, 5.f), glm::vec3(255.f, 255.f, 255.f), 0.5f);


int main() {


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Meat Cube", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);

	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Här skapas shaders!!!
	Shader defaultShader("meatVert.vert", "meatFrag.frag");
	Shader roomShader("roomVert.vert", "roomFrag.frag");
	Shader rampShader("rampVert.vert", "rampFrag.frag");
	
	cube.init(0.8f, 1);
	Room room(2.0f);
	Ramp ramp(2.0f);

	GLuint texture1, texture2, texture3, texture4, texture5, texture6, texture7, texture8, texture9;

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;

	LoadImage(width, height, nrChannels, true, "MeatDiffuse.png", texture1, 0);
	LoadImage(width, height, nrChannels, true, "MeatNormal.png", texture2, 1);
	LoadImage(width, height, nrChannels, true, "MeatSpec.png", texture3, 2);

	defaultShader.use(); 
	defaultShader.setInt("texture1", 0);
	defaultShader.setInt("texture2", 1);
	defaultShader.setInt("texture3", 2);
	defaultShader.setVec3("LightPos", light.GetPosition());
	defaultShader.setVec3("LightColor", light.GetColor());
	defaultShader.setVec3("SpecularColor", light.GetSpecularColor());
	defaultShader.setFloat("LightStrength", light.GetStrength());
	defaultShader.setFloat("linear", light.GetLinear());
	defaultShader.setFloat("qudratic", light.GetQuadratic());

	LoadImage(width, height, nrChannels, false, "container.jpg", texture4, 3);
	LoadImage(width, height, nrChannels, false, "container2_normal.png", texture5, 4);
	LoadImage(width, height, nrChannels, false, "container2_specular.png", texture6, 5);
	
	roomShader.use();
	roomShader.setInt("texture1", 3);
	roomShader.setInt("texture2", 4);
	roomShader.setInt("texture3", 5);
	roomShader.setVec3("LightPos", light.GetPosition());
	roomShader.setVec3("LightColor", light.GetColor());
	roomShader.setVec3("SpecularColor", light.GetSpecularColor());
	roomShader.setFloat("LightStrength", light.GetStrength());
	roomShader.setFloat("linear", light.GetLinear());
	roomShader.setFloat("qudratic", light.GetQuadratic());



	LoadImage(width, height, nrChannels, true, "RockAlbedo.png", texture7, 6);
	LoadImage(width, height, nrChannels, true, "RockNormal.png", texture8, 7);
	LoadImage(width, height, nrChannels, true, "RockSpec.png", texture9, 8);

	rampShader.use();
	rampShader.setInt("texture1", 6);
	rampShader.setInt("texture2", 7);
	rampShader.setInt("texture3", 8);
	rampShader.setVec3("LightPos", light.GetPosition());
	rampShader.setVec3("LightColor", light.GetColor());
	rampShader.setVec3("SpecularColor", light.GetSpecularColor());
	rampShader.setFloat("LightStrength", light.GetStrength());
	rampShader.setFloat("linear", light.GetLinear());
	rampShader.setFloat("qudratic", light.GetQuadratic());
	
	while (!glfwWindowShouldClose(window))
	{
		//glfwSetCursorPosCallback(window, mouse_callback);
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		//RENDERING
		glClearColor(0.0f, 0.0, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);



		float DimLight = glm::abs(glm::sin(glfwGetTime()));

		defaultShader.use();
		/*defaultShader.setFloat("LightStrength", DimLight);*/
		cube.render(bSimulate);
	
		// pass projection matrix to shader (note that in this case it could change every frame)
		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		defaultShader.setMat4("projection", projection);

		// camera/view transformation
		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		defaultShader.setMat4("view", view);

		//// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.f));

		defaultShader.setMat4("model", model);

		defaultShader.setVec3("viewPos", cameraPos);

		roomShader.use();

		room.render(bSimulate);

		// pass projection matrix to shader (note that in this case it could change every frame)
		roomShader.setMat4("projection", projection);

		// camera/view transformation
		roomShader.setMat4("view", view);

		//// calculate the model matrix for each object and pass it to shader before drawing
		roomShader.setMat4("model", model);

		roomShader.setVec3("viewPos", cameraPos);

		rampShader.use();

		ramp.render(bSimulate);

		// pass projection matrix to shader (note that in this case it could change every frame)
		rampShader.setMat4("projection", projection);

		// camera/view transformation
		rampShader.setMat4("view", view);

		//// calculate the model matrix for each object and pass it to shader before drawing
		rampShader.setMat4("model", model);
		rampShader.setVec3("viewPos", cameraPos);


		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = static_cast<float>(2.5 * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && bSimulate) cube.move(-1);
	
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && bSimulate) cube.move(1);
		
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if (!SimulatedPressed) { 
			bSimulate = !(bSimulate);
			SimulatedPressed = true;
		};
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) SimulatedPressed = false;
		
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && bSimulate) cube.jump();
	
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		if (!SetSpringPressed) {

			cube.SetSpringConstant(-10.f, SetSpringPressed);
		};
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		if (!SetSpringPressed) {

			cube.SetSpringConstant(10.f, SetSpringPressed);
		};
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE || glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE) SetSpringPressed = false;

	

	
}
void LoadImage(int& width, int& height, int &nrChannels, bool flip, std::string imageToLoad, GLuint& TextureID, GLuint TextureUnit) {
	stbi_set_flip_vertically_on_load(flip); // tell stb_image.h to flip loaded texture's on the y-axis.
	
	std::string input = "Images/" + imageToLoad;

	
	unsigned char* data = stbi_load(input.c_str(), &width, &height, &nrChannels, 0);
	
	if (data)
	{	
		glGenTextures(1, &TextureID);
		glActiveTexture(GL_TEXTURE0 + TextureUnit);
		glBindTexture(GL_TEXTURE_2D, TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

}
