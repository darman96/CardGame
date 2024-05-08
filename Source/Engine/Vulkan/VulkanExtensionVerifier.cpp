//
// Created by erik on 05.05.24.
//

#include "VulkanExtensionVerifier.h"

#include <cstring>
#include <vulkan/vulkan.hpp>

bool VulkanExtensionVerifier::VerifyInstanceExtensions(const std::vector<const char *> &extensions) {
    std::cout << "Verifying instance extensions:" << std::endl;
    const auto availableExtensions = vk::enumerateInstanceExtensionProperties();
    return verifyExtensions(extensions, availableExtensions);
}

bool VulkanExtensionVerifier::VerifyDeviceExtensions(const vk::PhysicalDevice &device,
                                                     const std::vector<const char *> &extensions) {
    std::cout << "Verifying device extensions:" << std::endl;
    const auto availableExtensions = device.enumerateDeviceExtensionProperties();
    return verifyExtensions(extensions, availableExtensions);
}

bool VulkanExtensionVerifier::verifyExtensions(const std::vector<const char *> &requiredExtensions,
                                               const std::vector<vk::ExtensionProperties> &availableExtensions) {
    bool missingExtension = false;
    for (const auto& requiredExtension: requiredExtensions) {
        bool found = false;
        std::cout << "\t" << requiredExtension << ": ";
        for (const auto& availableExtension: availableExtensions) {
            if (strcmp(requiredExtension, availableExtension.extensionName) == 0) {
                std::cout << "Ok" << std::endl;
                found = true;
                break;
            }
        }

        if (!found) {
            missingExtension = true;
            std::cout << "Not found" << std::endl;
        }
    }

    if (missingExtension)
        return false;

    return true;
}
