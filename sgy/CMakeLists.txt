cmake_minimum_required(VERSION 3.1...3.14)

project(sgy)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

#find_package(MKL REQUIRED)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
target_include_directories(sgy PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Widgets segyio share  fftw3)#eigen
