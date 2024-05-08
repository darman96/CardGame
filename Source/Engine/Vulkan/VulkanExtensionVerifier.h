//
// Created by erik on 05.05.24.
//

#ifndef VULKANEXTENSIONVERIFIER_H
#define VULKANEXTENSIONVERIFIER_H

namespace vk {
    class PhysicalDevice;
    class ExtensionProperties;
}

class VulkanExtensionVerifier {

public:
    VulkanExtensionVerifier() = delete;
    static bool VerifyInstanceExtensions(const std::vector<const char *> &extensions);
    static bool VerifyDeviceExtensions(const vk::PhysicalDevice &device, const std::vector<const char *> &extensions);

private:
    static bool verifyExtensions(const std::vector<const char *> &requiredExtensions,
                                 const std::vector<vk::ExtensionProperties> &availableExtensions);

};



#endif //VULKANEXTENSIONVERIFIER_H
