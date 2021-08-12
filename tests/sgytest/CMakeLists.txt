
set(testgrp sgytest)


file(GLOB TESTS "*.cpp")

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-march=native" _march_native_works)
check_cxx_compiler_flag("-xHost" _xhost_works)

set(_CXX_FLAGS)
if(_march_native_works)
  message(STATUS "Using processor's vector instructions (-march=native compiler flag set)")
  set(_CXX_FLAGS "-march=native")
elseif(_xhost_works)
  message(STATUS "Using processor's vector instructions (-xHost compiler flag set)")
  set(_CXX_FLAGS "-xHost")
else()
  message(STATUS "No suitable compiler flag found for vectorization")
endif()


add_executable(${testgrp} ${TESTS})

target_compile_options(${testgrp} PRIVATE ${_CXX_FLAGS})

add_custom_command(TARGET ${testgrp} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/testdata $<TARGET_FILE_DIR:${testgrp}>/testdata)

target_link_libraries(${testgrp} PRIVATE Qt5::Test sgy fftw3)
