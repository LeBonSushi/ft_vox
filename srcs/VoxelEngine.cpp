#include "VoxelEngine.h"

static VoxelEngine* g_engineInstance = nullptr;

VoxelEngine::VoxelEngine()
{
	g_engineInstance = this;
	m_player = nullptr;
	m_cubeShader = nullptr;
	m_cube = nullptr;
	init();
}

VoxelEngine::~VoxelEngine()
{
	delete m_player;
	delete m_cubeShader;
	delete m_cube;
}

void VoxelEngine::stop()
{
	if (m_window)
	{
		glfwDestroyWindow(m_window);
	}
	glfwTerminate();
	g_engineInstance = nullptr;
}

void VoxelEngine::windowSizeCallback(GLFWwindow* window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
	
	// Update the current window dimensions in the engine instance
	if (g_engineInstance) {
		g_engineInstance->m_currentWidth = width;
		g_engineInstance->m_currentHeight = height;
	}
}

void VoxelEngine::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	(void)window;
	g_engineInstance->m_player->processMouse(xpos, ypos);
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
	glfwSetCursorPosCallback(m_window, mouseCallback);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	m_player = new Player(glm::vec3(0.0f, 0.0f, 3.0f));
	
	m_cubeShader = new Shader();
	if (!m_cubeShader->loadFromFile("shaders/cube.vert", "shaders/cube_simple.frag"))
	{
		Logger::log(LOG_ERROR, "Failed to load cube shader");
		this->setWindowClose();
		return;
	}
	
	m_cube = new Cube();
	m_cube->init();
	m_cube->setColor(glm::vec3(1.0f, 0.5f, 0.2f)); // Orange cube
	m_cube->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	
	Logger::log(LOG_INFO, "VoxelEngine initialized successfully.");
}

void VoxelEngine::run()
{
	while (!this->windowShouldClose() && !glfwWindowShouldClose(m_window))
	{
		this->handleEvents();
		this->update();
		this->render();
	}
}

void VoxelEngine::handleEvents()
{
	glfwPollEvents();

	m_player->processInput(m_window, m_deltaTime);
}

void VoxelEngine::update()
{
	updateDeltaTime();
	

	Logger::log(LOG_INFO, "DeltaTime: ", m_deltaTime);
	m_player->update(m_deltaTime);
}

void VoxelEngine::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	
	if (m_player && m_cube && m_cubeShader)
	{
		// Get view and projection matrices from player
		glm::mat4 view = m_player->getViewMatrix();
		glm::mat4 projection = m_player->getProjectionMatrix(
			(float)m_currentWidth / (float)m_currentHeight
		);
		
		// Get model matrix from cube
		glm::mat4 model = m_cube->getModelMatrix();
		
		// Render the cube
		m_cube->render(*m_cubeShader, model, view, projection);
	}
	
	glfwSwapBuffers(m_window);
}

void VoxelEngine::updateDeltaTime()
{
	static float lastTime = 0;
	float t = glfwGetTime();

	m_deltaTime = t - lastTime;
	lastTime = t;
}