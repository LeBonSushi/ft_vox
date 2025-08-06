#include "VoxelEngine.h"

VoxelEngine::VoxelEngine()
{
	init();
}

VoxelEngine::~VoxelEngine()
{
	
}

void VoxelEngine::stop()
{
	if (m_window)
	{
		glfwDestroyWindow(m_window);
	}
	glfwTerminate();
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
		Logger::log(LOG_ERROR, "Failed to initialize the window.");
		return ;
	}

	glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		this->setWindowClose();
		Logger::log(LOG_ERROR, "Failed to initialize GLAD.");
        return ;
    }

	glfwSetFramebufferSizeCallback(m_window, windowSizeCallback);
	Logger::log(LOG_INFO, "VoxelEngine initialized successfully.");
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
	glfwPollEvents();
}

void VoxelEngine::update()
{

}

void VoxelEngine::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glfwSwapBuffers(m_window);
}