add_subdirectory(glfw)
add_subdirectory(glad)
add_subdirectory(glm)

target_include_directories(VoxelEngine PRIVATE glfw/include)
target_include_directories(VoxelEngine PRIVATE glad/include)
target_include_directories(VoxelEngine PRIVATE glm)
target_include_directories(VoxelEngine PRIVATE stb)