//
// Created by erik on 05.05.24.
//

#ifndef VULKANIMAGEVIEWCREATOR_H
#define VULKANIMAGEVIEWCREATOR_H

namespace vk {
    class Image;
    class Device;
    class ImageView;
    enum class Format;

}

class VulkanImageViewCreator {

public:
    VulkanImageViewCreator() = delete;
    static std::vector<vk::ImageView> Create(const vk::Device& logicalDevice, const vk::Format& format, const std::vector<vk::Image>& images);

};



#endif //VULKANIMAGEVIEWCREATOR_H
