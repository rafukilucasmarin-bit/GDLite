cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(GDLiteMac VERSION 1.0.0)

if (APPLE)
	enable_language(OBJCXX)
endif()

file(GLOB SOURCES src/*.cpp)
if (APPLE)
	file(GLOB MM_SOURCES src/*.mm)
	list(APPEND SOURCES ${MM_SOURCES})
endif()

add_library(${PROJECT_NAME} SHARED ${SOURCES})

if (NOT DEFINED ENV{GEODE_SDK})
	message(FATAL_ERROR "Define la variable de entorno GEODE_SDK apuntando al SDK de Geode")
else()
	message(STATUS "Geode SDK: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)
setup_geode_mod(${PROJECT_NAME})
