cmake_minimum_required(VERSION 3.10)

# Set some basic project attributes
project (MinecraftClone
	VERSION 0.1
	DESCRIPTION "A Hello World Project")

set(CMAKE_CXX_STANDARD 20)
set(LIB_DIR "${PROJECT_SOURCE_DIR}/libs")

# Add source files
file(GLOB SRC_FILES 
	"src/Game.cpp"
	"src/Window.cpp"
	"src/Shader.cpp"
	"src/Mesh.cpp"
	"src/Block.cpp"
)

# This project will output an executable file
add_executable(${PROJECT_NAME} ${SRC_FILES})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

set(GLFW_DIR ${LIB_DIR}/glfw-3.3.8)
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory(${GLFW_DIR})
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_DIR}/include)
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

set(GLAD_DIR ${LIB_DIR}/glad)
add_library(glad ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PRIVATE ${GLAD_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLAD_DIR}/include)
target_link_libraries(${PROJECT_NAME} glad ${CMAKE_DL_LIBS})

find_package(glm REQUIRED)
target_link_libraries(${PROJECT_NAME} glm::glm)
