set(TEST_FILES tests.cpp)
set(TESTING_FILES ../Car.cpp ../Car.h ../CarController.cpp ../CarController.h)

add_executable(tests ${TEST_FILES} ../../../catch2/catch.hpp ${TESTING_FILES})