//
// Created by erik on 05.05.24.
//

#ifndef VULKANINSTANCECREATOR_H
#define VULKANINSTANCECREATOR_H

namespace vk {
    class Instance;
    class ApplicationInfo;
    class InstanceCreateInfo;
}

class VulkanInstanceCreator {

public:
    VulkanInstanceCreator() = delete;
    static vk::Instance Create();

private:
    static vk::ApplicationInfo createApplicationInfo();
    static vk::InstanceCreateInfo createInstanceCreateInfo(const vk::ApplicationInfo& appInfo);

};



#endif //VULKANINSTANCECREATOR_H
