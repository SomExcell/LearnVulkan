find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)

add_subdirectory(libraries/glm)
target_link_libraries(${PROJECT_NAME} glm)

add_subdirectory(libraries/glfw)
target_link_libraries(${PROJECT_NAME} glfw)