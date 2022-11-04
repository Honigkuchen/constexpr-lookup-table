set(EXECUTABLE_NAME CPP_CMAKE_DEFAULT)
add_executable(${EXECUTABLE_NAME} main.cc)

target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror -Wconversion)