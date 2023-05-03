cmake_minimum_required(VERSION 3.0.2)
project(computational_geometry)


# test_mergesort section
add_executable(test src/test.cpp)
target_include_directories(test PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(test PRIVATE ${PROJECT_SOURCE_DIR}/libs)


# test OpenGl section
add_executable(test_openGL src/testOpenGl.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

target_include_directories(test_openGL PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(test_openGL PRIVATE ${PROJECT_SOURCE_DIR}/libs)
target_link_libraries(test_openGL PUBLIC 
    glfw
    OpenGL::GL
    ${CMAKE_DL_LIBS}
)
