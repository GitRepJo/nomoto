cmake_minimum_required(VERSION 3.5)
project(nomoto)

set(CMAKE_C_STANDARD 99)

set(CMAKE_CXX_STANDARD 14)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Boost 1.45.0 COMPONENTS math) 

add_executable(nomoto src/main.cpp src/nomoto_sim.cpp)

target_include_directories(nomoto PRIVATE include/)

file(COPY config/nomoto_config.yaml DESTINATION ./ )

include_directories(${Boost_INCLUDE_DIRS}) 
include_directories(${CMAKE_SOURCE_DIR}/yaml-cpp/include)

target_link_libraries(${PROJECT_NAME} yaml-cpp)
target_link_libraries (${PROJECT_NAME} Eigen3::Eigen)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests test/test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)