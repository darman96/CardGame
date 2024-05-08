//
// Created by erik on 05.05.24.
//

#include "VulkanLayerVerifier.h"

#include <vulkan/vulkan.hpp>

bool VulkanLayerVerifier::Verify(const std::vector<const char*>& requiredLayers) {
    std::cout << "Verifying layers:" << std::endl;
    const auto availableLayers = vk::enumerateInstanceLayerProperties();

    bool missingLayer = false;
    for (const auto requiredLayer: requiredLayers) {
        bool found = false;
        std::cout << "\t" << requiredLayer << ": ";
        for (const auto& availableLayer: availableLayers) {
            if (strcmp(requiredLayer, availableLayer.layerName) == 0) {
                std::cout << "Ok" << std::endl;
                found = true;
                break;
            }
        }

        if (!found) {
            missingLayer = true;
            std::cout << "Not found" << std::endl;
        }
    }

    if (missingLayer)
        return false;

    return true;
}
