set(TEST_FILES tests.cpp)
set(TESTING_FILES ../Functions.cpp ../Functions.h)

add_executable(tests ${TEST_FILES} ../../../../catch2/catch.hpp ${TESTING_FILES})