﻿#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

class HelloTriangleApplication 
{
public:
    void run() 
    {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    void initWindow()
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(width, height, "LearnVulkan", nullptr, nullptr);

    }

    void initVulkan() const
    {

    }

    void mainLoop() const
    {
        while (!glfwWindowShouldClose(window)) 
        {
            glfwPollEvents();
        }
    }

    void cleanup() const
    {
        glfwDestroyWindow(window);

        glfwTerminate();
    }

private:
    GLFWwindow* window;

    const uint32_t width = 800;
    const uint32_t height = 600;
};

int main() 
{
    HelloTriangleApplication app;

    try
    {
        app.run();
    }
    catch(const std::exception e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}