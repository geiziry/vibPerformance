cmake_minimum_required(VERSION 3.1...3.14)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(vibPerformance
                       DESCRIPTION "end to end VSP interpretation"
                       LANGUAGES CXX)

if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
    SET(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 -lprofiler")
else()
    SET(GCC_COVERAGE_COMPILE_FLAGS "-g -O3 -lprofiler")
endif()

#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(USE_TESTS ON)

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)
#find_package(Eigen3 3.3.7 REQUIRED CONFIG)
enable_testing()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

#add_subdirectory(thirdparty/Eigen)
add_subdirectory(thirdparty/segyio)
add_subdirectory(sgy)
add_subdirectory(model)
add_subdirectory(ui)
add_subdirectory(share)

if(${USE_TESTS})
    add_subdirectory( tests )
endif()

list (APPEND RESOURCES resources/resources.qrc)

qt5_add_resources (RCC_SOURCES ${RESOURCES})
add_executable(${PROJECT_NAME} main.cpp ${RCC_SOURCES} )
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Widgets sgy share model ui)
