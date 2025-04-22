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
set(CMAKE_INSTALL_PREFIX "${TOON_ROOT_DIR}/bin")
set(BINARY_ROOT_DIR "${CMAKE_INSTALL_PREFIX}")
set(SOURCE_ROOT_DIR "${TOON_ROOT_DIR}/source")
set(THIRD_PARTY_DIR "${TOON_ROOT_DIR}/3rdparty")
set(TOON_ASSET_DIR "asset")
set(TOON_CONFIG_DIR "configs")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TOON_ROOT_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TOON_ROOT_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TOON_ROOT_DIR}/bin)

add_subdirectory(3rdparty)

add_subdirectory(source/runtime)
add_subdirectory(source/editor)
add_subdirectory(source/meta_parser)


set(CODEGEN_TARGET "ToonPreCompile")
include(source/precompile/precompile.cmake)
set_target_properties("${CODEGEN_TARGET}" PROPERTIES FOLDER "Engine" )

add_dependencies(ToonRuntime "${CODEGEN_TARGET}")
add_dependencies("${CODEGEN_TARGET}" "ToonParser")
