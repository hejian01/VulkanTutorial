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
    VkSurfaceCapabilitiesKHR capabilities;          // 描述surface的基本能力
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
    bool checkValidationLayerSupport();
    std::vector<const char*> getRequiredExtensions();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
    
    void setupDebugMessenger();
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

    void createSurface();
    
    void pickPhysicalDevice();
    bool isDeviceSuitable(VkPhysicalDevice device);
    /*! 查找指定物理设备上支持图形队列的队列族索引 */
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    /// 检查物理设备是否支持deviceExtensions所需要的扩展
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    
    void createLogicalDevice();
    
    void createSwapChain();
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    void recreateSwapChain();
    void cleanupSwapChain();
    
    void createImageViews();
    
    void createRenderPass();
    
    void createGraphicsPipeline();
    static std::vector<char> readFile(const std::string& filename);
    VkShaderModule createShaderModule(const std::vector<char>& code);
    
    void createFramebuffers();
    
    void createCommandPool();
    
    void createCommandBuffer();
    
    void createSyncObjects();
    
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    
private:
    GLFWwindow*                             window;
    VkInstance                              instance;
    VkDebugUtilsMessengerEXT                debugMessenger;
    VkSurfaceKHR                            surface;
    VkPhysicalDevice physicalDevice     =   VK_NULL_HANDLE;
    VkDevice                                device;
    VkQueue                                 graphicsQueue;
    VkQueue                                 presentQueue;
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
    std::vector<VkCommandBuffer>            commandBuffers;
    std::vector<VkSemaphore>                imageAvailableSemaphores;
    std::vector<VkSemaphore>                renderFinishedSemaphores;
    std::vector<VkFence>                    inFlightFences;
    
    const int                               MAX_FRAMES_IN_FLIGHT = 2;
    uint32_t                                currentFrame = 0;
    
    uint32_t                                m_width;
    uint32_t                                m_height;
    
    bool                                    framebufferResized = false;
};

#endif
