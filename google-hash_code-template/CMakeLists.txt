cmake_minimum_required(VERSION 3.16.1)
project(hash_code LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})

add_compile_definitions("USE_SPDLOG")

find_package(Filesystem REQUIRED)
include(cmake/modules/sanitizers.cmake)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
   add_compile_options(-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
   add_compile_options(-fcolor-diagnostics)
endif ()

add_executable(main "")
target_compile_options(main PRIVATE -Wall -Wextra -pedantic -Wno-unused-parameter)
target_compile_options(main PUBLIC -Ofast)

target_compile_features(main PRIVATE cxx_std_20)

## Libraries
target_link_libraries(main PRIVATE std::filesystem)

#set(Boost_USE_STATIC_LIBS   ON)
#set(Boost_USE_MULTITHREADED ON)
#find_package(Boost 1.72.0 REQUIRED)
#if(Boost_FOUND)
#  include_directories(${Boost_INCLUDE_DIRS})
#  target_link_libraries(main ${Boost_LIBRARIES})
#endif()

add_subdirectory(external/fmt-7.1.3)
target_link_libraries(main PRIVATE fmt::fmt)

option(SPDLOG_FMT_EXTERNAL ON)
add_subdirectory(external/spdlog-1.8.5)
target_link_libraries(main PRIVATE spdlog::spdlog)

## Sources
add_subdirectory(src)
