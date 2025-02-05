cmake_minimum_required(VERSION 3.28)
project(cript)

set(CMAKE_CXX_STANDARD 23)

# Enable testing
enable_testing()

# Add the main executable
add_executable(cript src/main.cpp
        src/caesarCyph.cpp
        src/caesarCyph.h
        src/transpositionCipher.cpp
        src/transpositionCipher.h)

# Add the tests directory
add_subdirectory(tests)

# Ensure tests run automatically after compilation
add_custom_target(run_tests
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        DEPENDS transposition_test  # This must be the actual test executable name
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Make the test execution dependent on building the project
add_dependencies(cript run_tests)
