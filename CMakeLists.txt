cmake_minimum_required(VERSION 3.15)
project(ToDOlist)
include_directories(src)
include_directories(tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
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

file(GLOB_RECURSE PROTO_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/proto/*.proto )
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SOURCES})
message("Generated ${PROTO_SRCS} ${PROTO_HDRS}")

SET_SOURCE_FILES_PROPERTIES(${PROTO_SRCS} ${PROTO_HDRS} PROPERTIES GENERATED TRUE)



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
file( GLOB_RECURSE SERIALIZATION_HEADERS src/serialization/*.h)
file( GLOB_RECURSE SERIALIZATION_SOURCES src/serialization/*.cpp)
add_executable(ToDOList src/main.cpp
        ${CLI_SOURCES} ${CLI_HEADERS}
        ${CORE_SOURCES} ${CORE_HEADERS}
        ${SERIALIZATION_HEADERS} ${SERIALIZATION_SOURCES}
        ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(ToDOList -static ${Protobuf_LIBRARIES})
target_link_libraries(ToDOList ${Boost_LIBRARIES})

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
        ${TESTS} ${MOCKS})
target_link_libraries(TestsExecutable GTest::GTest GTest::Main
                        ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY}
                        ${Boost_LIBRARIES})

gtest_discover_tests(TestsExecutable)

#############################################