cmake_minimum_required(VERSION 3.0.0)
project(main VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(main main.cpp geometry.cpp rrt.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE "-lsfml-graphics -lsfml-window -lsfml-system")

include(CPack)
