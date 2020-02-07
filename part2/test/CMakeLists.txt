set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB TEST_SOURCES *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} tmp125_driver gtest pthread)