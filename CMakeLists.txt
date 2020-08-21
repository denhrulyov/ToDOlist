cmake_minimum_required(VERSION 3.15)
project(ToDOlist)
include_directories(src)
include_directories(tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
#set(CMAKE_CXX_FLAGS "-D_GLIBCXX_DEBUG")

file( GLOB_RECURSE CLI_SOURCES src/cli/*.cpp)
file( GLOB_RECURSE CLI_HEADERS src/cli/*.h)
file( GLOB_RECURSE CORE_HEADERS src/core/*.h)
file( GLOB_RECURSE CORE_SOURCES src/core/*.cpp)
add_executable(ToDOList src/main.cpp
        ${CLI_SOURCES} ${CLI_HEADERS}
        ${CORE_SOURCES} ${CORE_HEADERS})

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


target_link_libraries(ToDOList -static)
target_link_libraries(ToDOList ${Boost_LIBRARIES})

##############################################################

include_directories(src)
include_directories(tests)

#boost pthread issue fixup ##################

#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)

#thread
#target_link_libraries(ToDOList Threads::Threads)

#############################################

# tests #####################################

include(GoogleTest)
find_package(GTest REQUIRED)
include_directories(${GMOCK_INCLUDE_DIR})
enable_testing()

add_executable(TestsExecutable
                tests/TestTaskNode.cpp
                tests/TestTaskDTO.cpp
                tests/TestTagPriorityView.cpp
                tests/TestDatePriortyView.cpp
                tests/TestTaskService.cpp
                tests/TestLinkManager.cpp
                tests/TestTaskStorage.cpp
                tests/TestTaskID.cpp
                tests/TestTaskIDFactory.cpp
                tests/TestTaskCreationResult.cpp
                tests/TestTaskModificationResult.cpp
                tests/TestRequestResult.cpp
                src/core/api/RequestResult.cpp
                src/core/api/TaskModificationResult.cpp
                src/core/api/TaskCreationResult.cpp
                src/core/api/TaskService.cpp
                src/core/memory_model/data/Task.cpp
                src/core/memory_model/structure/TaskNode.cpp
                src/core/memory_model/view/DatePriorityView.cpp
                src/core/api/TaskDTO.cpp
                src/core/memory_model/data/TaskID.cpp
                src/core/memory_model/data/TaskIDFactory.cpp
                src/core/api/TaskCreationResult.cpp
                src/core/memory_model/view/TagPriorityView.cpp
                src/core/memory_model/data/TaskStorage.cpp
                src/core/memory_model/structure/LinkManager.cpp
                src/core/utils/data_transfer/TaskDTOConverter.cpp
                src/core/memory_model/data/TaskPriority.h tests/test_main.cpp
                src/core/api/TaskServiceInterface.h
                ${CLI_SOURCES})
target_link_libraries(TestsExecutable GTest::GTest GTest::Main ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY})

gtest_discover_tests(TestsExecutable)

#############################################