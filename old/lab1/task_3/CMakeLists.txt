cmake_minimum_required(VERSION 3.23)
project(task_3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(task_3 main.cpp)

#add_custom_command(TARGET task_3
#        POST_BUILD
#        COMMAND .\tests\test.bat
#        )


