cmake_minimum_required(VERSION 3.11.0)
project(word_counter VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
   googletest
   GIT_REPOSITORY      https://github.com/google/googletest.git
   GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

set(PROJECT_SOURCES entry.h entry.cpp word_counter.h word_counter.cpp)

add_executable(main main.cpp ${PROJECT_SOURCES})
add_executable(testGoogle testGoogle.cpp ${PROJECT_SOURCES})
target_link_libraries(testGoogle PUBLIC gtest_main)
