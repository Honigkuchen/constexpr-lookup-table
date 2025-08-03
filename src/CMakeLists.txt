set(EXECUTABLE_NAME constexpr-lookup-table)
add_executable(${EXECUTABLE_NAME} main.cpp)

target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic
                                                  -Werror -Wconversion)
