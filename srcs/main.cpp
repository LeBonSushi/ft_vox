#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VoxelEngine.h"

// void framebuffer_size_callback(GLFWwindow* window, int width, int height)
// {
// 	(void) window;
//     glViewport(0, 0, width, height);
// }

int main() {
    // Initialize GLFW
    // glfwInit();
    
    // // Create window...
    // GLFWwindow* window = glfwCreateWindow(800, 600, "SCOP", NULL, NULL);
    // glfwMakeContextCurrent(window);
    
    // // Initialize GLAD
    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    //     // Handle error
    //     return -1;
    // }

    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
	// while (!glfwWindowShouldClose(window))
	// {
	// 	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	// 	glClear(GL_COLOR_BUFFER_BIT);
	// 	glfwSwapBuffers(window);
	// 	glfwPollEvents();
	// }
	// glfwTerminate();

	VoxelEngine voxelEngine;

	voxelEngine.run();
	// voxelEngine.stop();
	return 0;
}