cmake_minimum_required(VERSION 3.5.1)
project(SpectrixPC C CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

set(OpenGL_GL_PREFERENCE "LEGACY")

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

find_library(SOIL SOIL lib/libsoil.a)

set(SPECTRIX_LIBS_DIR "libs")
set(RTAUDIO_DIR "${SPECTRIX_LIBS_DIR}/rtaudio-5.1.0")

include_directories(
  ${GLM_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
  ${GLFW_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIRS}
  ${RTAUDIO_DIR}
  "${RTAUDIO_DIR}/include"
)

link_libraries(
  ${GLEW_LIBRARIES}
  ${GLFW_LIBRARIES}
  ${OPENGL_LIBRARIES}
)

link_directories("${RTAUDIO_DIR}/librtaudio_la-RtAudio.o")

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(SpectrixPC ${SOURCE_FILES})

target_link_libraries(SpectrixPC ${SOIL})