add_subdirectory(glfw)
add_subdirectory(glad)

target_include_directories(VoxelEngine PRIVATE glfw/include)
target_include_directories(VoxelEngine PRIVATE glad/include)