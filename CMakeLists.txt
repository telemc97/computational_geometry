cmake_minimum_required(VERSION 3.0.2)
project(computational_geometry)

add_library(ConvexHull2D ${PROJECT_SOURCE_DIR}/include/ConvexHull2D.cpp ${PROJECT_SOURCE_DIR}/include/ConvexHull2D.h)
add_library(HullOpenGL ${PROJECT_SOURCE_DIR}/include/HullOpenGL.cpp ${PROJECT_SOURCE_DIR}/include/HullOpenGL.h)

add_subdirectory(libs/eigen)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Eigen3 3.4 REQUIRED)

# test OpenGl section
add_executable(test_openGL src/testOpenGl.cpp)

target_include_directories(test_openGL PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(test_openGL PRIVATE ${PROJECT_SOURCE_DIR}/libs)

target_link_libraries(test_openGL 
    ConvexHull2D
    HullOpenGL
    glfw
    OpenGL::GL
    Eigen3::Eigen
)