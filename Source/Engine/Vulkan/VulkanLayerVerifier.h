//
// Created by erik on 05.05.24.
//

#ifndef VULKANLAYERVERIFIER_H
#define VULKANLAYERVERIFIER_H



class VulkanLayerVerifier {

public:
    VulkanLayerVerifier() = delete;
    static bool Verify(const std::vector<const char*>& requiredLayers);

};



#endif //VULKANLAYERVERIFIER_H
