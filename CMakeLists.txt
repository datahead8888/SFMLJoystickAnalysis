#References
#http://blog.beuc.net/posts/Build_a_SFML_project_with_CMake/
#http://igorbarbosa.com/articles/how-to-use-opengl-freeglut-and-cmake/
cmake_minimum_required(VERSION 2.6)
project(openglproject)

#From http://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()

include_directories(${PROJECT_BINARY_DIR})

set(EXECUTABLE_NAME "joystickexec")
add_executable(${EXECUTABLE_NAME} main.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})
MESSAGE(${CMAKE_MODULE_PATH})

#SFML
find_package(SFML 2.1 REQUIRED system window graphics network audio)
#include_directories(${SFML_INCLUDE_DIR})

target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES}) 

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

