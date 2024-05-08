//
// Created by erik on 05.05.24.
//

#include "VulkanImageViewCreator.h"

#include "Structs/VulkanSwapchainInfo.h"

std::vector<vk::ImageView> VulkanImageViewCreator::Create(const vk::Device &logicalDevice, const vk::Format &format, const std::vector<vk::Image> &images) {
    std::cout << "Creating image views" << std::endl;
    auto imageViews = std::vector<vk::ImageView>(images.size());

    for (auto i = 0; i < images.size(); i++) {
        const auto createInfo = vk::ImageViewCreateInfo {
            .image = images[i],
            .viewType = vk::ImageViewType::e2D,
            .format = format,
            .components = {
                .r = vk::ComponentSwizzle::eIdentity,
                .g = vk::ComponentSwizzle::eIdentity,
                .b = vk::ComponentSwizzle::eIdentity,
                .a = vk::ComponentSwizzle::eIdentity
            },
            .subresourceRange = {
                .aspectMask = vk::ImageAspectFlagBits::eColor,
                .baseMipLevel = 0,
                .levelCount = 1,
                .baseArrayLayer = 0,
                .layerCount = 1
            }
        };

        imageViews[i] = logicalDevice.createImageView(createInfo);
    }

    return imageViews;
}
