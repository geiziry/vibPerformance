set(testgrp uitest)


file(GLOB TESTS "*.cpp")


add_executable(${testgrp} ${TESTS})

target_link_libraries(${testgrp} PRIVATE Qt5::Test sgy ui)
