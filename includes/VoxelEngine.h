#pragma once

#include "Logger.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

struct Settings {
    inline static constexpr int Width = 800;
    inline static constexpr double Height = 600;
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
		void handleEvents();
		void update();
		void render();
	private: //Variables
		GLFWwindow* m_window;
		bool m_shouldClose = false;
	private: //Utils
		void setWindowClose(const bool should = true) { m_shouldClose = should; }
		[[nodiscard]] bool windowShouldClose() const { return m_shouldClose; }

};