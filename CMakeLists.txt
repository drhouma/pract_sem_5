cmake_minimum_required(VERSION 3.27)

project(async_solver)

set(CMAKE_CXX_STANDARD 20)

set(Boost_USE_MULTITHREADING ON)
set(Boost_USE_STATIC_LIBS ON)

set(HDR algo.h)
set(SRC algo.cpp
        main.cpp)

if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    set(CONAN_BUILD_INFO ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
elseif (EXISTS ${CMAKE_BINARY_DIR}/conan-dependencies/conanbuildinfo.cmake)
    set(CONAN_BUILD_INFO ${CMAKE_BINARY_DIR}/conan-dependencies/conanbuildinfo.cmake)
endif ()

if (NOT CONAN_BUILD_INFO)
    message(FATAL_ERROR "couldn't find conanbuildinfo.cmake")
endif ()

include(${CONAN_BUILD_INFO})
conan_basic_setup(TARGETS)

find_package(Boost 1.83.0
    COMPONENTS
    thread
    REQUIRED)

if (Boost_FOUND)
    message(STATUS "boost is found")
    message(STATUS "boost include path " ${Boost_INCLUDE_DIRS})
    message(STATUS "boost library path " ${Boost_LIBRARY_DIRS})
    message(STATUS "boost libraries "    ${Boost_LIBRARIES})
else ()
    message(FATAL_ERROR "couldn't found boost")
endif ()

add_executable(${PROJECT_NAME}
        ${HDR}
        ${SRC}
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${Boost_INCLUDE_DIRS}
        ${Boost_LIBRARY_DIRS}
)
target_link_libraries(${PROJECT_NAME}
        PUBLIC
        ${Boost_LIBRARIES}
)
