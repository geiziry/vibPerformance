cmake_minimum_required(VERSION 3.1...3.14)

project(share VERSION 1.0)


#find_package(Qt5 COMPONENTS Widgets REQUIRED)

file(GLOB SOURCES "src/*.cpp" "src/*.c")

file(GLOB HEADERS "include/*.h")


add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Widgets)
