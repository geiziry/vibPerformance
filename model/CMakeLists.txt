set(proj model)

file(GLOB SOURCES "src/*.cpp")

file(GLOB HEADERS "include/*.h")

add_library(${proj} SHARED ${SOURCES} ${HEADERS})

target_include_directories(${proj} PUBLIC include)

target_link_libraries(${proj} PUBLIC Qt5::Widgets Qt5::Charts)

