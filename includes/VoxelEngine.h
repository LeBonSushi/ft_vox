#pragma once

#include "Logger.h"
#include "Shader.h"

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
		static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
		void handleEvents();
		void update();
		void render();
		void updateDeltaTime();
	private: //Variables
		GLFWwindow* m_window;
		float m_deltaTime = 0;
		int m_currentWidth = Settings::Width;
		int m_currentHeight = Settings::Height;
	private: //Utils
		[[nodiscard]] float getDeltaTime() const { return m_deltaTime; }

};