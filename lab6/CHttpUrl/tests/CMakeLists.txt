set(TEST_FILES tests.cpp)
set(TESTING_FILES ../CHttpUrl.h ../CHttpUrl.cpp ../CUrlParsingError.h ../CUrlParsingError.cpp)

add_executable(tests ${TEST_FILES} ../../../../../catch2/catch.hpp ${TESTING_FILES})