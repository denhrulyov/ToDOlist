
cmake_minimum_required(VERSION 3.15)
project(ToDOlist)
include_directories(src)
include_directories(tests)
#SET(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")
SET(CMAKE_CXX_FLAGS "-fstandalone-debug")
set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(BUILD_SHARED_LIBS OFF)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
#set(CMAKE_CXX_FLAGS "-D_GLIBCXX_DEBUG")

# boost #####################################################
set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     OFF)

find_package(Boost REQUIRED COMPONENTS date_time)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE PROTO_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/proto/task.proto )
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SOURCES})
message("Generated ${PROTO_SRCS} ${PROTO_HDRS}")

SET_SOURCE_FILES_PROPERTIES(${PROTO_SRCS} ${PROTO_HDRS} PROPERTIES GENERATED TRUE)

#gRPC###################################

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)


# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
find_package(gRPC REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)

##########################################

# Proto file
get_filename_component(ts_proto "proto/TaskService.proto" ABSOLUTE)
get_filename_component(ts_proto_path "${ts_proto}" PATH)

set(ts_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/TaskService.pb.cc")
set(ts_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/TaskService.pb.h")
set(ts_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/TaskService.grpc.pb.cc")
set(ts_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/TaskService.grpc.pb.h")
add_custom_command(
        OUTPUT "${ts_proto_srcs}" "${ts_proto_hdrs}" "${ts_grpc_srcs}" "${ts_grpc_hdrs}"
        COMMAND protoc
        ARGS -I "${ts_proto_path}"
        --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        ${ts_proto}
        DEPENDS ${ts_proto})


include_directories("${CMAKE_CURRENT_BINARY_DIR}")



##############################################################

include_directories(src)
include_directories(tests)

#boost pthread issue fixup ##################

#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)

#thread
#target_link_libraries(ToDOList Threads::Threads)

#############################################



file( GLOB_RECURSE CLI_SOURCES src/cli/*.cpp)
file( GLOB_RECURSE CLI_HEADERS src/cli/*.h)
file( GLOB_RECURSE CORE_HEADERS src/core/*.h)
file( GLOB_RECURSE CORE_SOURCES src/core/*.cpp)
add_executable(ToDOList src/main.cpp
        ${CLI_SOURCES} ${CLI_HEADERS}
        ${CORE_SOURCES} ${CORE_HEADERS}
        ${PROTO_SRCS} ${PROTO_HDRS}
        ${ts_proto_srcs} ${ts_proto_hdrs}
        ${ts_grpc_srcs} ${ts_grpc_hdrs})
target_link_libraries(ToDOList ${Boost_LIBRARIES} ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF})

add_executable(Server src/Server.cpp
        src/core/api/GrpcTaskServiceImpl.h src/core/api/GrpcTaskServiceImpl.cpp
        ${Boost_LIBRARIES}
        ${CLI_SOURCES} ${CLI_HEADERS}
        ${CORE_SOURCES} ${CORE_HEADERS}
        ${PROTO_SRCS} ${PROTO_HDRS}
        ${ts_proto_srcs}
        ${ts_grpc_srcs})
target_link_libraries(Server
        ${Boost_LIBRARIES}
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF})

add_executable(Client src/Client.cpp
        src/core/api/GrpcTaskServiceImpl.h src/core/api/GrpcTaskServiceImpl.cpp
        ${CLI_SOURCES} ${CLI_HEADERS}
        ${CORE_SOURCES} ${CORE_HEADERS}
        ${PROTO_SRCS} ${PROTO_HDRS}
        ${ts_proto_srcs}
        ${ts_grpc_srcs})
target_link_libraries(Client
        ${Boost_LIBRARIES}
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF})

#target_link_libraries(ToDOList ${Protobuf_LIBRARIES})

# tests #####################################
include(GoogleTest)
find_package(GTest REQUIRED)
include_directories(${GMOCK_INCLUDE_DIR})
enable_testing()

file(GLOB_RECURSE TESTS tests/*.cpp)
file(GLOB_RECURSE MOCKS tests/mocks/*.h)

add_executable(TestsExecutable
        ${CLI_SOURCES} ${CLI_HEADERS}
        ${CORE_SOURCES} ${CORE_HEADERS}
        ${TESTS} ${MOCKS}
        ${PROTO_SRCS} ${PROTO_HDRS}
        ${ts_proto_srcs}
        ${ts_grpc_srcs})
target_link_libraries(TestsExecutable GTest::GTest GTest::Main
        ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY}
        ${Boost_LIBRARIES}
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF})

gtest_discover_tests(TestsExecutable)

#############################################