# Find GoogleTest
find_package(GTest REQUIRED)

# Create test executable
add_executable(transposition_test transposition_test.cpp ../src/transpositionCipher.cpp ../src/utils.cpp)
add_executable(caesar_test caesar_test.cpp ../src/caesarCyph.cpp ../src/utils.cpp)
add_executable(affine_test affinecipher_test.cpp ../src/affineCipher.cpp ../src/utils.cpp)
add_executable(utils_test utils_test.cpp ../src/utils.cpp)



# Link GoogleTest with the test executable
target_link_libraries(transposition_test PRIVATE GTest::GTest GTest::Main)
target_link_libraries(caesar_test PRIVATE GTest::GTest GTest::Main)
target_link_libraries(affine_test PRIVATE GTest::GTest GTest::Main)
target_link_libraries(utils_test PRIVATE GTest::GTest GTest::Main)

# Add tests to the CMake test system
add_test(NAME TranspositionTest COMMAND transposition_test)
add_test(NAME CaesarTest COMMAND caesar_test)
add_test(NAME AffineTest COMMAND affine_test)
add_test(NAME UtilsTest COMMAND utils_test)