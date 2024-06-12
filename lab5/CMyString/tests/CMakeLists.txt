set(TESTING_FILES ../CMyString.h ../CMyString.cpp)
set(TEST_FILES tests.cpp)

add_executable(tests ${TEST_FILES} ../../../../../catch2/catch.hpp ${TESTING_FILES})