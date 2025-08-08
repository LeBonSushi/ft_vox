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
	VoxelEngine* engine = static_cast<VoxelEngine *>(glfwGetWindowUserPointer(window));
	glViewport(0, 0, width, height);
	
	engine->m_currentWidth = width;
	engine->m_currentHeight = height;
}

void VoxelEngine::keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	VoxelEngine* engine = static_cast<VoxelEngine *>(glfwGetWindowUserPointer(window));

	(void)engine; // TO remove
	(void)key;
	(void)scancode;
	(void)action;
	(void)mods;
	//if (engine) engine->player->move(key);
}


void VoxelEngine::init()
{
	glfwInit();
	m_window = glfwCreateWindow(Settings::Width, Settings::Height, Settings::WinName, nullptr, nullptr);
	if (m_window == nullptr)
	{
		glfwSetWindowShouldClose(m_window, true);
		Logger::log(LOG_ERROR, "Failed to initialize the window.");
		return ;
	}

	glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwSetWindowShouldClose(m_window, true);
		Logger::log(LOG_ERROR, "Failed to initialize GLAD.");
        return ;
    }

	glfwSetWindowUserPointer(m_window, this);
	glfwSetFramebufferSizeCallback(m_window, windowSizeCallback);
	glfwSetKeyCallback(m_window, keyCallBack);
	// glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	Logger::log(LOG_INFO, "VoxelEngine initialized successfully.");
}

void VoxelEngine::run()
{
	while (!glfwWindowShouldClose(m_window))
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
	updateDeltaTime();
	
	Logger::log(LOG_INFO, "DeltaTime: ", m_deltaTime);
}

void VoxelEngine::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_DEPTH_TEST);
	
	glfwSwapBuffers(m_window);
}

void VoxelEngine::updateDeltaTime()
{
	static float lastTime = 0;
	float t = glfwGetTime();

	m_deltaTime = t - lastTime;
	lastTime = t;
}