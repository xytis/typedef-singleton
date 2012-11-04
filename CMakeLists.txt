cmake_minimum_required (VERSION 2.6)

project (SingletonShowcase)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

link_libraries(pthread)

file(GLOB SingletonShowcase_SRC
    "showcase.cpp"
)
add_executable(SingletonShowcase ${SingletonShowcase_SRC})
