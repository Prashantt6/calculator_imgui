cmake_minimum_required(VERSION 3.10)
project(ImGuiCalculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_WIN32_EXECUTABLE OFF)  # Ensure it expects main(), not WinMain()

# Disable building extra GLFW components
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Add GLFW subdirectory
add_subdirectory(libs/glfw)

# Add GLAD
add_library(glad STATIC libs/glad/src/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)

# Add ImGui source files
set(IMGUI_SRC
    libs/imgui/imgui.cpp
    libs/imgui/imgui_draw.cpp
    libs/imgui/imgui_tables.cpp
    libs/imgui/imgui_widgets.cpp
    libs/imgui/backends/imgui_impl_glfw.cpp
    libs/imgui/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC
    libs/imgui
    libs/imgui/backends
)

# Main executable
add_executable(ImGuiCalculator main.cpp operation.cpp)


# Include directories for the main target
target_include_directories(ImGuiCalculator PRIVATE
    libs/glad/include
    libs/imgui
    libs/imgui/backends
    libs/glfw/include
)

# Link all libraries to the main executable
target_link_libraries(ImGuiCalculator PRIVATE glfw glad imgui)

# Link against OpenGL on Windows
if (WIN32)
    target_link_libraries(ImGuiCalculator PRIVATE opengl32)
endif()
