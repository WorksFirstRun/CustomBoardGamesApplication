cmake_minimum_required(VERSION 3.28)
project(BoardGames)

set(CMAKE_CXX_STANDARD 17)

# Add source files
if(WIN32)
    add_executable(BoardGames WIN32
            src/main.cpp
            src/BoardGamesGUI.cpp
            include/imgui/imgui.cpp
            include/imgui/imgui_demo.cpp
            include/imgui/imgui_draw.cpp
            include/imgui/imgui_tables.cpp
            include/imgui/imgui_widgets.cpp
            include/imgui/backends/imgui_impl_glfw.cpp
            include/imgui/backends/imgui_impl_opengl3.cpp
            src/glad.c
    )
else()
    add_executable(BoardGames
            src/main.cpp
            src/BoardGamesGUI.cpp
            include/imgui/imgui.cpp
            include/imgui/imgui_demo.cpp
            include/imgui/imgui_draw.cpp
            include/imgui/imgui_tables.cpp
            include/imgui/imgui_widgets.cpp
            include/imgui/backends/imgui_impl_glfw.cpp
            include/imgui/backends/imgui_impl_opengl3.cpp
            src/glad.c
    )
endif()

# Include directories
target_include_directories(BoardGames PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/imgui
        ${CMAKE_SOURCE_DIR}/src
)

# Find OpenGL
find_package(OpenGL REQUIRED)

if(MINGW)
    target_link_libraries(BoardGames PRIVATE
            ${CMAKE_SOURCE_DIR}/lib/libglfw3.a  # or glfw3.dll.a if you're using DLL
            OpenGL::GL
            gdi32
            user32
            kernel32
    )
endif()

add_custom_command(TARGET BoardGames POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Assets $<TARGET_FILE_DIR:BoardGames>/Assets)