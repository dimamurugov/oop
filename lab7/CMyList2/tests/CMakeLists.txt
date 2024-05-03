set(TEST_FILES tests.cpp)
set(TESTING_FILES ../CMyList.h ../CMyList.cpp)

add_executable(tests ${TEST_FILES} ../../../../../catch2/catch.hpp ${TESTING_FILES})