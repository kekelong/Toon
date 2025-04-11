cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

project(Toon VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)

# ---- Include guards ----
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options("/MP")
endif()

set(TOON_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SOURCE_ROOT_DIR "${TOON_ROOT_DIR}/source")
set(THIRD_PARTY_DIR "${TOON_ROOT_DIR}/3rdparty")
set(ENGINE_ASSET_DIR "asset")

# 设置可执行文件和库文件的输出目录为根路径下的 bin 目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TOON_ROOT_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TOON_ROOT_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TOON_ROOT_DIR}/bin)

add_subdirectory(3rdparty)
add_subdirectory(source)