
set(proj ui)

file(GLOB SOURCES "src/*.cpp")

file(GLOB HEADERS "include/*.h")

file(GLOB FORMS "forms/*ui")

qt5_wrap_ui(FORM_H ${FORMS})

add_library(${proj} SHARED ${SOURCES} ${HEADERS} ${FORM_H})

target_include_directories(${proj} PUBLIC include ${CMAKE_BINARY_DIR})

target_link_libraries(${proj} PUBLIC Qt5::Widgets Qt5::Charts model sgy)


