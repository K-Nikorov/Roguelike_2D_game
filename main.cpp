#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game.h"
#include "resource_manager.h"
#include "common.h"

#include <iostream>

constexpr unsigned int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
constexpr unsigned int PANEL_WIDTH = 200;

void OnKeyboardPressed(GLFWwindow* window, int key, int scancode, int action, int mode);
void OnFramebufferSizeCallback(GLFWwindow* window, int width, int height);

int initGL();


Game MyRoguelike(WINDOW_WIDTH, WINDOW_HEIGHT, PANEL_WIDTH);

int main() {
    if (!glfwInit())
    {
      return -1;
    }

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow*  window = glfwCreateWindow(WINDOW_WIDTH + PANEL_WIDTH, WINDOW_HEIGHT, "task1 base project", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if(initGL() != 0)
	{
		return -1;
    }

	GLenum gl_error = glGetError();
	while (gl_error != GL_NO_ERROR)
	{
		gl_error = glGetError();
    }

    glfwSetKeyCallback            (window, OnKeyboardPressed);


    glViewport(0, 0, WINDOW_WIDTH + PANEL_WIDTH, WINDOW_HEIGHT); GL_CHECK_ERRORS;
    glEnable(GL_BLEND); GL_CHECK_ERRORS;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); GL_CHECK_ERRORS;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); GL_CHECK_ERRORS;


    MyRoguelike.Init();

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;


	while (!glfwWindowShouldClose(window))
	{

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
        glfwPollEvents();


        MyRoguelike.ProcessInput(deltaTime);

        MyRoguelike.Update(deltaTime);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); GL_CHECK_ERRORS;
		glClear(GL_COLOR_BUFFER_BIT); GL_CHECK_ERRORS;
        MyRoguelike.Render();

		glfwSwapBuffers(window);
	}

    ResourceManager::Clear();

    glfwTerminate();
    return 0;
}


int initGL()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

  std::cout << "Controls: "<< std::endl;
  std::cout << "press right mouse button to capture/release mouse cursor  "<< std::endl;
  std::cout << "W, A, S, D - movement  "<< std::endl;
  std::cout << "press ESC to exit" << std::endl;

	return 0;
}


void OnKeyboardPressed(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	switch (key) {
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		break;
    case GLFW_KEY_1:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        break;
    case GLFW_KEY_2:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        break;
	default:
        if (key >= 0 && key < 1024) {
            if (action == GLFW_PRESS)
                MyRoguelike.Keys[key] = true;
            else if (action == GLFW_RELEASE)
                MyRoguelike.Keys[key] = false;
        }
	}
}
