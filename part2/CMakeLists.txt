cmake_minimum_required(VERSION 3.10)
project(tmp125_driver)

file(GLOB SOURCES src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
install(TARGETS ${PROJECT_NAME} DESTINATION /usr/lib/${PROJECT_NAME})

file(GLOB HEADERS src/*.h)
install(FILES ${HEADERS} DESTINATION /usr/include/${PROJECT_NAME})

link_directories(test)
add_subdirectory(test)
enable_testing()