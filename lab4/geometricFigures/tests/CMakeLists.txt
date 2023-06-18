set(TEST_FILES tests.cpp)
set(TESTING_FILES ../CPoint.h ../CPoint.cpp ../CCircle.cpp ../CCircle.h ../CLineSegment.cpp ../CLineSegment.h)

add_executable(tests ${TEST_FILES} ../../../../../catch2/catch.hpp ${TESTING_FILES})