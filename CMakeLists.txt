cmake_minimum_required(VERSION 2.6)
project(flights_javeriana)

#Version Number
set(flights_javeriana_VERSION_MAJOR 0)
set(flights_javeriana_VERSION_MINOR 2)
set(CMAKE_CXX_STANDARD 17)

file( GLOB SRCS ./src/*.cpp ./src/*.cxx ./src/PUJ/*.cxx )

add_executable( ${PROJECT_NAME}  ${SRCS})
