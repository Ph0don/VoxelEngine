set (SOURCE_DIR "src")

set (SOURCES
     src/main.cpp
     src/Application.h
     src/Application.cpp
     src/Shader.h
     src/Shader.cpp
     src/Geometry/Vertex.h
)

add_executable(VoxelEngine ${SOURCES})

target_link_libraries(VoxelEngine glfw)
target_link_libraries(VoxelEngine glad)