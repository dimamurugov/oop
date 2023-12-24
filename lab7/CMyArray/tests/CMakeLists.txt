set(TEST_FILES tests.cpp)
set(TESTING_FILES ../CMyArray.h ../CMyArray.cpp)

add_executable(tests ${TEST_FILES} ../../../../../catch2/catch.hpp ${TESTING_FILES})