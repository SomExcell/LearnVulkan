#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

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
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(width, height, "LearnVulkan", nullptr, nullptr);
    }

    void initVulkan()
    {
        createInstance();
        CheckGlfwAvailableExtensions();
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
        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();
    }

private:

    void createInstance()
    {
        auto applicationInfo = CreateApplicationInfo();
        auto createInfo = CreateInstanceCreateInfo(applicationInfo);
        auto createInstanceResult = vkCreateInstance(&createInfo, nullptr, &instance);

        if (createInstanceResult != VK_SUCCESS)
        {
            throw std::runtime_error("Failed create glfw instance");
        }
    }

    static VkInstanceCreateInfo CreateInstanceCreateInfo(const VkApplicationInfo &applicationInfo)
    {
        VkInstanceCreateInfo createInfo{};
        createInfo.pApplicationInfo = &applicationInfo;
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
    	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        return createInfo;
    }

	static VkApplicationInfo CreateApplicationInfo()
    {
        VkApplicationInfo applicationInfo{};
        applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        applicationInfo.pApplicationName = "LearnVulkan";
        applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        applicationInfo.pEngineName = "No Engine";
        applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        applicationInfo.apiVersion = VK_API_VERSION_1_0;

        return applicationInfo;
    }

    static void CheckGlfwAvailableExtensions()
    {
        auto extensions = GetExtensionsSupport();
        uint32_t glfwExtensionCount = 0;
        auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    }

    static std::vector<VkExtensionProperties> GetExtensionsSupport()
    {   
        uint32_t extensionsCount = 0;

        vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionsCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, extensions.data());

        return extensions;
    }

private:
    GLFWwindow* window;
    VkInstance instance;

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