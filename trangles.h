#ifndef TRANGLES_H
#define TRANGLES_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <array>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <optional>
#include <set>

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

        return attributeDescriptions;
    }
};

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
    
    void createDescriptorSetLayout();
    
    void createGraphicsPipeline();
    static std::vector<char> readFile(const std::string& filename);
    VkShaderModule createShaderModule(const std::vector<char>& code);
    
    void createFramebuffers();
    
    void createCommandPool();
    void createDepthResources();
    VkFormat findDepthFormat();
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    bool hasStencilComponent(VkFormat format);
    void createTextureImage();
    void createTextureImageView();
    void createTextureSampler();
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    void createVertexBuffer();
    void createIndexBuffer();
    void createUniformBuffers();
    void createDescriptorPool();
    void createDescriptorSets();
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void createCommandBuffers();
    
    void createSyncObjects();
    void updateUniformBuffer(uint32_t currentImage);
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    
private:
    GLFWwindow*                             window;
    VkInstance                              instance;
    VkDebugUtilsMessengerEXT                debugMessenger;
    VkSurfaceKHR                            surface;
    VkPhysicalDevice physicalDevice       = VK_NULL_HANDLE;
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
    VkDescriptorSetLayout                   descriptorSetLayout;
    VkPipelineLayout                        pipelineLayout;
    VkPipeline                              graphicsPipeline;
    
    VkImage                                 depthImage;
    VkDeviceMemory                          depthImageMemory;
    VkImageView                             depthImageView;
    
    VkCommandPool                           commandPool;
    VkImage                                 textureImage;
    VkDeviceMemory                          textureImageMemory;
    VkImageView                             textureImageView;
    VkSampler                               textureSampler;
    
    VkBuffer                                vertexBuffer;
    VkDeviceMemory                          vertexBufferMemory;
    VkBuffer                                indexBuffer;
    VkDeviceMemory                          indexBufferMemory;
    std::vector<VkBuffer>                   uniformBuffers;
    std::vector<VkDeviceMemory>             uniformBuffersMemory;
    std::vector<void*>                      uniformBuffersMapped;
    
    VkDescriptorPool                        descriptorPool;
    std::vector<VkDescriptorSet>            descriptorSets;
    
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
