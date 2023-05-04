#ifndef TRANGLES_H
#define TRANGLES_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <optional>
#include <set>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;


    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class HelloTriangleApplication {
public:
    explicit HelloTriangleApplication(uint32_t& width, uint32_t& height);
    void run();

private:
    void initWindow();
    void initVulkan();
    
    void mainLoop();
    void drawFrame();
    
    void cleanup();
    void createInstance();

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void setupDebugMessenger();
    std::vector<const char*> getRequiredExtensions();
    bool checkValidationLayerSupport();
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
    
    void createSurface();
    void pickPhysicalDevice();
    bool isDeviceSuitable(VkPhysicalDevice device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    
    /*! 查找指定物理设备上支持图形队列的队列族索引 */
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    
    void createLogicalDevice();
    
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    
    void createSwapChain();
    void createImageViews();
    void createGraphicsPipeline();
    static std::vector<char> readFile(const std::string& filename);
    VkShaderModule createShaderModule(const std::vector<char>& code);
    void createRenderPass();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffer();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    void createSyncObjects();
    
private:
    GLFWwindow*                             window;
    VkInstance                              instance;
    VkDebugUtilsMessengerEXT                debugMessenger;
    VkPhysicalDevice physicalDevice     =   VK_NULL_HANDLE;
    VkDevice                                device;
    VkQueue                                 graphicsQueue;
    VkQueue                                 presentQueue;
    VkSurfaceKHR                            surface;
    VkSwapchainKHR                          swapChain;
    std::vector<VkImage>                    swapChainImages;
    VkFormat                                swapChainImageFormat;
    VkExtent2D                              swapChainExtent;
    std::vector<VkImageView>                swapChainImageViews;
    std::vector<VkFramebuffer>              swapChainFramebuffers;
    
    VkRenderPass                            renderPass;
    VkPipelineLayout                        pipelineLayout;
    VkPipeline                              graphicsPipeline;
    
    VkCommandPool                           commandPool;
    VkCommandBuffer                         commandBuffer;
    VkSemaphore                             imageAvailableSemaphore;
    VkSemaphore                             renderFinishedSemaphore;
    VkFence                                 inFlightFence;
    
    uint32_t                                m_width;
    uint32_t                                m_height;
};

#endif
