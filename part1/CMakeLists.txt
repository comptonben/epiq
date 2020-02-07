cmake_minimum_required(VERSION 3.10)
project(PTM)

file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
add_library(${PROJECT_NAME}_lib SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME} pthread curl)
install(TARGETS ${PROJECT_NAME} DESTINATION /usr/lib/${PROJECT_NAME})

file(GLOB HEADERS src/*.h)
install(FILES ${HEADERS} DESTINATION /usr/include/${PROJECT_NAME})