cmake_minimum_required(VERSION 3.21.3)

# Название проекта
set(PROJECT_NAME lab_04)
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES C CXX)

# Стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Исходный код
set(SOURCES
    src/main.cpp
	src/data.hpp
	src/data.cpp
	src/imgui_utils.hpp
	src/imgui_utils.cpp
	src/timer.hpp
	src/timer.cpp
)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_USE_HYBRID_HPG ON CACHE BOOL "" FORCE)

# ImGui 
set(IMGUI_DIRECTORY external/imgui)
set(IMGUI_SOURCE ${IMGUI_DIRECTORY}/imconfig.h
	${IMGUI_DIRECTORY}/imgui.h
	${IMGUI_DIRECTORY}/imgui.cpp
	${IMGUI_DIRECTORY}/imgui_draw.cpp
	${IMGUI_DIRECTORY}/imgui_internal.h
	${IMGUI_DIRECTORY}/imgui_widgets.cpp
	${IMGUI_DIRECTORY}/imstb_rectpack.h
	${IMGUI_DIRECTORY}/imstb_textedit.h
	${IMGUI_DIRECTORY}/imstb_truetype.h
    ${IMGUI_DIRECTORY}/imgui_tables.cpp
	${IMGUI_DIRECTORY}/imgui_demo.cpp
	${IMGUI_DIRECTORY}/backends/imgui_impl_glfw.cpp
	${IMGUI_DIRECTORY}/backends/imgui_impl_opengl3.cpp
)

# GLM
set(GLM_DIRECTORY external/glm/glm)

# stb_image
set(STB_IMAGE_PATH external/stb/stb_image.h)

# Подмодули
add_subdirectory(external/glad)
add_subdirectory(external/glfw)

add_executable(${PROJECT_NAME} ${SOURCES} ${STB_IMAGE_PATH} ${IMGUI_SOURCE})
target_link_libraries(${PROJECT_NAME} glad glfw)
target_include_directories(${PROJECT_NAME} PUBLIC ${IMGUI_DIRECTORY} ${GLM_DIRECTORY})
