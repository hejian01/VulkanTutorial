#ifndef TRANGLES_H
#define TRANGLES_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <optional>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;

    bool isComplete() {
        return graphicsFamily.has_value();
    }
};


class HelloTriangleApplication {
public:
    explicit HelloTriangleApplication(uint32_t& width, uint32_t& height);
    void run();

private:
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();
    void createInstance();

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void setupDebugMessenger();
    std::vector<const char*> getRequiredExtensions();
    bool checkValidationLayerSupport();
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
    
    void pickPhysicalDevice();
    bool isDeviceSuitable(VkPhysicalDevice device);
    
    /*! 查找指定物理设备上支持图形队列的队列族索引 */
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    
    void createLogicalDevice();
    
private:
    GLFWwindow*                             window;
    VkInstance                              instance;
    VkDebugUtilsMessengerEXT                debugMessenger;
    VkPhysicalDevice physicalDevice     =   VK_NULL_HANDLE;
    VkDevice                                device;
    VkQueue                                 graphicsQueue;
    
    uint32_t                                m_width;
    uint32_t                                m_height;
};

#endif
