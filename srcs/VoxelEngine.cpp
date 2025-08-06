#include "VoxelEngine.h"

VoxelEngine::VoxelEngine()
{
	init();
}

void VoxelEngine::windowSizeCallback(GLFWwindow* window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}


void VoxelEngine::init()
{
	glfwInit();
	m_window = glfwCreateWindow(Settings::Width, Settings::Height, Settings::WinName, nullptr, nullptr);
	if (m_window == nullptr)
	{
		this->setWindowClose();
		logger.log(LOG_ERROR, "Failed to initialize the window.");
		return ;
	}

	glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		this->setWindowClose();
        return ;
    }

	glfwSetFramebufferSizeCallback(m_window, windowSizeCallback);
	return ;
}

void VoxelEngine::run()
{
	while (!this->windowShouldClose())
	{
		this->handleEvents();
		this->update();
		this->render();
	}
}

void VoxelEngine::handleEvents()
{
	;
}

void VoxelEngine::update()
{

}

void VoxelEngine::render()
{

}