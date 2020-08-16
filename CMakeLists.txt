cmake_minimum_required(VERSION 3.15)
project(ToDOlist)
include_directories(src)
include_directories(tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
#set(CMAKE_CXX_FLAGS "-D_GLIBCXX_DEBUG")
add_executable(ToDOList src/main.cpp
        src/api/TaskService.cpp src/api/TaskService.h
        src/memory_model/data/Task.h
        src/memory_model/data/Task.cpp
        src/memory_model/structure/TaskNode.cpp src/memory_model/structure/TaskNode.h
        src/memory_model/view/DatePriorityView.cpp src/memory_model/view/DatePriorityView.h
        src/api/TaskDTO.cpp src/api/TaskDTO.h
        src/utils/task_io/ConsoleTaskIO.h
        src/memory_model/data/TaskID.cpp src/memory_model/data/TaskID.h
        src/memory_model/view/PriorityViewInterface.h
        src/api/Service.h
        src/memory_model/data/TaskIDFactory.cpp src/memory_model/data/TaskIDFactory.h
        src/memory_model/view/TagPriorityView.cpp src/memory_model/view/TagPriorityView.h
        src/memory_model/data/TaskStorageInterface.h
        src/memory_model/data/TaskStorage.cpp
        src/memory_model/data/TaskStorage.h
        src/memory_model/structure/LinkManager.cpp
        src/memory_model/structure/LinkManager.h
        src/utils/data_transfer/TaskDTOConverter.cpp
        src/utils/data_transfer/TaskDTOConverter.h
        src/api/RequestResult.cpp src/api/RequestResult.h
        src/api/TaskModificationResult.cpp src/api/TaskModificationResult.h
        src/api/TaskCreationResult.cpp src/api/TaskCreationResult.h src/memory_model/data/TaskPriority.h src/memory_model/structure/LinkManagerInterface.h)

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

                src/api/RequestResult.cpp
                src/api/TaskModificationResult.cpp
                src/api/TaskCreationResult.cpp
                src/api/TaskService.cpp
                src/memory_model/data/Task.cpp
                src/memory_model/structure/TaskNode.cpp
                src/memory_model/view/DatePriorityView.cpp
                src/api/TaskDTO.cpp
                src/memory_model/data/TaskID.cpp
                src/memory_model/data/TaskIDFactory.cpp
                src/api/TaskCreationResult.cpp
                src/memory_model/view/TagPriorityView.cpp
                src/memory_model/data/TaskStorage.cpp
                src/memory_model/structure/LinkManager.cpp
                src/utils/data_transfer/TaskDTOConverter.cpp
                src/memory_model/data/TaskPriority.h tests/test_main.cpp)
target_link_libraries(TestsExecutable GTest::GTest GTest::Main ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY})

gtest_discover_tests(TestsExecutable)

#############################################