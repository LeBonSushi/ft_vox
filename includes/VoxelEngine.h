#pragma once

#include "Logger.h"
#include "Player.h"
#include "Shader.h"
#include "Cube.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>
#include <memory>

struct Settings {
    inline static constexpr int Width = 800;
    inline static constexpr int Height = 600;
	inline static constexpr auto WinName = "ft_vox";
};

class VoxelEngine
{
	public:
		VoxelEngine();
		~VoxelEngine();
		void init();
		void run(); //TODO
		void stop(); //TODO
	private:
		static void windowSizeCallback(GLFWwindow* window, int w, int h);
		static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
		void handleEvents();
		void update();
		void render();
		void updateDeltaTime();
	private: //Variables
		GLFWwindow* m_window;
		bool m_shouldClose = false;
		float m_deltaTime = 0;
		Player* m_player;
		Shader* m_cubeShader;
		Cube* m_cube;
		int m_currentWidth = Settings::Width;
		int m_currentHeight = Settings::Height;
	private: //Utils
		void setWindowClose(const bool should = true) { m_shouldClose = should; }
		[[nodiscard]] float getDeltaTime() const { return m_deltaTime; }
		[[nodiscard]] bool windowShouldClose() const { return m_shouldClose; }

};