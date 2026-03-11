#include <iostream>
#include <GLFW/glfw3.h>

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Hello, Vulkan!" << std::endl;

    return EXIT_SUCCESS;
}