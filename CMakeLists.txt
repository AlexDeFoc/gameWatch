cmake_minimum_required(VERSION 3.30.3)

project(app)

add_executable(${PROJECT_NAME} "./src/main.cpp" "./src/item.cpp")

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
)
