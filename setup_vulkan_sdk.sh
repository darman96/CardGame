#!/bin/bash

# Define constants
VULKAN_SDK_DIR="/opt/vulkan-sdk"
TEMP_DIR=$(mktemp -d)

# Check if Vulkan SDK is already installed
if [ -d "$VULKAN_SDK_DIR" ]; then
    echo "Vulkan SDK is already installed at $VULKAN_SDK_DIR"
    exit 0
fi

# Fetch the latest Vulkan SDK versions JSON
fetch_latest_version() {
    LATEST_JSON=$(curl -s https://vulkan.lunarg.com/sdk/latest.json)
    LINUX_VERSION=$(echo "$LATEST_JSON" | jq -r '.linux')

    if [ "$LINUX_VERSION" == "null" ]; then
        echo "Failed to retrieve latest Vulkan version"
        exit 1
    fi

    echo "Latest Vulkan SDK version for Linux: $LINUX_VERSION"
}

# Download the Vulkan SDK binaries
download_sdk() {
    VULKAN_SDK_URL="https://sdk.lunarg.com/sdk/download/$LINUX_VERSION/linux/vulkansdk-linux-x86_64-$LINUX_VERSION.tar.xz"
    echo "Downloading Vulkan SDK from $VULKAN_SDK_URL"

    wget -qO- https://sdk.lunarg.com/sdk/download/$LINUX_VERSION/linux/vulkansdk-linux-x86_64-$LINUX_VERSION.tar.xz | tar xJ -C "$TEMP_DIR"

    if [ $? -ne 0 ]; then
        echo "Failed to download or extract Vulkan SDK"
        exit 1
    fi
}

# Copy the extracted SDK to /opt
copy_sdk_to_opt() {
    sudo cp -r "$TEMP_DIR/$LINUX_VERSION" "$VULKAN_SDK_DIR"

    if [ $? -ne 0 ]; then
        echo "Failed to copy Vulkan SDK to $VULKAN_SDK_DIR"
        exit 1
    fi
}

# Set up environment variables
setup_environment_variables() {
    export VULKAN_SDK="$VULKAN_SDK_DIR/x86_64"
    export PATH="$VULKAN_SDK/bin:$PATH"
    export LD_LIBRARY_PATH="$VULKAN_SDK/lib:$LD_LIBRARY_PATH"
    export VK_ICD_FILENAMES="$VULKAN_SDK/etc/vulkan/icd.d/nvidia_icd.json"
    export VK_LAYER_PATH="$VULKAN_SDK/etc/vulkan/explicit_layer.d"

    VULKAN_ENV_FILE="$VULKAN_SDK_DIR/setup-env.sh"

    echo "source $VULKAN_ENV_FILE" >> ~/.bashrc
    echo "source $VULKAN_ENV_FILE" >> ~/.zshrc
}

# Clean up the temporary directory
cleanup() {
    rm -rf "$TEMP_DIR"
    echo "Temporary directory cleaned up."
}

# Main script flow
fetch_latest_version
download_sdk
copy_sdk_to_opt
setup_environment_variables
cleanup

echo "Vulkan SDK setup complete. Please restart your terminal or run 'source ~/.bashrc' or 'source ~/.zshrc' to apply the changes."