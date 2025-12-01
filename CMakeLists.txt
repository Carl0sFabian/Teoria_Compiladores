cmake_minimum_required(VERSION 3.15)
project(minic_llvm_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# enable RTTI (some ANTLR builds disable RTTI by default)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti")

# Find LLVM 22
find_package(LLVM 22 REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(LLVM_LIBS
    support
    core
    native
    asmparser
)

# ANTLR runtime (system)
find_library(ANTLR4_RUNTIME_LIBRARY NAMES antlr4-runtime antlr4_shared HINTS /usr/lib /usr/local/lib)

if(NOT ANTLR4_RUNTIME_LIBRARY)
    message(FATAL_ERROR "No se encontró la librería antlr4-runtime. Instálala o ajusta CMake.")
endif()

include_directories(/usr/include/antlr4-runtime)

set(SOURCES
    main.cpp
    MiniCVisitorLLVM.cpp
    CodeGen.cpp

    # ANTLR generated sources (regenera siempre si cambias MiniC.g4)
    MiniCLexer.cpp
    MiniCParser.cpp
    MiniCBaseVisitor.cpp
)

add_executable(minic ${SOURCES})

target_include_directories(minic PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(minic PRIVATE
    ${LLVM_LIBS}
    ${ANTLR4_RUNTIME_LIBRARY}
)
