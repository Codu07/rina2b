cmake_minimum_required(VERSION 3.1...3.19)

project(Rina C CXX)

set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_STANDARD_REQUIRED True)

#include(FindProtobuf)

#include_directories(dep/ggml/include/ggml third_party/ggml/src)
#add_subdirectory(dep/ggml)

#include_directories(dep/sentencepiece/src)
#add_subdirectory(dep/sentencepiece)

#if (GGML_CUBLAS)
#    add_compile_definitions(GGML_USE_CUBLAS)
#    set(CUDA_ARCHITECTURES "52;61;70;75;80;86" CACHE STRING "coreai: cuda architectures to compile")
#    set_property(TARGET ggml PROPERTY CUDA_ARCHITECTURES ${CUDA_ARCHITECTURES})
#endif ()
 
#if (GGML_METAL)
#    add_compile_definitions(GGML_USE_METAL)
    #configure_file(dep/ggml/src/ggml-metal.metal ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/ggml-metal.metal COPYONLY)
#endif ()

# look for cxxopt
find_path(CXXOPTS_INCLUDE_PATH NAMES cxxopts.hpp)
if (NOT CXXOPTS_INCLUDE_PATH)
    message(FATAL_ERROR "Failed to find cxxopts")
endif()
include_directories(${CXXOPTS_INCLUDE_PATH})

# look for fmtlib
find_path(FMTLIB_INCLUDE_PATH NAMES fmt/format.h)
find_library(FMT_LIB NAMES libfmt.a fmt)
if((NOT FMTLIB_INCLUDE_PATH) OR (NOT FMT_LIB))
    message(FATAL_ERROR "Failed to find fmtlib")
endif()
include_directories(${FMTLIB_INCLUDE_PATH})

# look for spdlog
find_path(SPDLOG_INCLUDE_PATH NAMES spdlog/spdlog.h)
find_library(SPDLOG_LIB NAMES libspdlog.a spdlog)
if((NOT SPDLOG_INCLUDE_PATH) OR (NOT SPDLOG_LIB))
    message(FATAL_ERROR "Failed to find spdlog")
endif()
include_directories(${SPDLOG_INCLUDE_PATH})

# look for yaml-cpp
find_path(YAMLCPP_INCLUDE_PATH NAMES yaml-cpp/yaml.h)
find_library(YAMLCPP_LIB NAMES libyaml-cpp.a yaml-cpp)
if((NOT YAMLCPP_INCLUDE_PATH) OR (NOT YAMLCPP_LIB))
    message(FATAL_ERROR "Failed to find yaml-cpp")
endif()
include_directories(${YAMLCPP_INCLUDE_PATH})

# look for workflow
find_path(WORKFLOW_INCLUDE_PATH NAMES workflow/Workflow.h)
find_library(WORKFLOW_LIB NAMES libworkflow.a workflow)
if((NOT WORKFLOW_INCLUDE_PATH) OR (NOT WORKFLOW_LIB))
    message(FATAL_ERROR "Failed to find workflow")
endif()
include_directories(${WORKFLOW_INCLUDE_PATH})

# look for nlohmann json
find_path(JSON_INCLUDE_PATH NAMES nlohmann/json.hpp)
if (NOT JSON_INCLUDE_PATH)
    message(FATAL_ERROR "Failed to find nlohmann-json")
endif()
include_directories(${JSON_INCLUDE_PATH})

# look for jwt-cpp
find_path(JWT_INCLUDE_PATH NAMES jwt-cpp/jwt.h)
if(NOT JWT_INCLUDE_PATH)
    message(FATAL_ERROR "Failed to find jwt-cpp")
endif()
include_directories(${JWT_INCLUDE_PATH})

# look for openssl
find_package(OpenSSL)
include_directories(${OPENSSL_INCLUDE_DIR})

include_directories(.)

set(CMAKE_CXX_FLAGS "${CMAKE_CPP_FLAGS} -O2 -std=c++2a -pipe -W -Wall -Wno-unused-parameter -fPIC -fno-omit-frame-pointer")

set(LIBS
    ${FMT_LIB}
    ${SPDLOG_LIB}
    ${PROTOBUF_LIBRARIES}
    ${YAMLCPP_LIB}
    ${WORKFLOW_LIB}
    ${LEVELDB_LIB}
    ${OPENSSL_CRYPTO_LIBRARY}
    ${OPENSSL_SSL_LIBRARY}
    dl
    )

aux_source_directory(./src DIR_SRCS)
aux_source_directory(./idl DIR_IDLS)

add_executable(rina ${DIR_SRCS} ${DIR_IDLS})
target_link_libraries(rina ${LIBS})
