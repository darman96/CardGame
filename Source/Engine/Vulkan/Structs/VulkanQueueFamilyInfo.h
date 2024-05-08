//
// Created by erik on 05.05.24.
//

#ifndef VULKANQUEUEFAMILYINFO_H
#define VULKANQUEUEFAMILYINFO_H

struct VulkanQueueFamilyInfo {

    std::optional<uint32> GraphicsFamilyIndex = std::nullopt;
    std::optional<uint32> PresentFamilyIndex = std::nullopt;

    [[nodiscard]] bool IsComplete() const {
        return GraphicsFamilyIndex.has_value() && PresentFamilyIndex.has_value();
    }

};

#endif //VULKANQUEUEFAMILYINFO_H
