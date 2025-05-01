set (SOURCE_DIR "src")

set (SOURCES
     src/main.cpp
     src/Application.h
     src/Application.cpp
     src/Rendering/Shader.h
     src/Rendering/Shader.cpp
     src/Rendering/VertexBuffer.h
     src/Rendering/VertexBuffer.cpp
     src/Rendering/IndexBuffer.h
     src/Rendering/IndexBuffer.cpp
     src/Rendering/VertexArray.h
     src/Rendering/VertexArray.cpp
     src/Geometry/Vertex.h
)

add_executable(VoxelEngine ${SOURCES})

target_link_libraries(VoxelEngine glfw)
target_link_libraries(VoxelEngine glad)