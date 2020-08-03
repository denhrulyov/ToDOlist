cmake_minimum_required(VERSION 3.15)
project(ToDOlist)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "-D_GLIBCXX_DEBUG")
add_executable(ToDOList src/main.cpp
        src/api/TaskService.cpp src/api/TaskService.h
        src/memory_model/Task.h
        src/memory_model/Task.cpp
        src/memory_model/TaskNode.cpp src/memory_model/TaskNode.h
        src/memory_model/DatePriorityView.cpp src/memory_model/DatePriorityView.h
        src/api/TaskDTO.cpp src/api/TaskDTO.h
        src/task_io/task_io.h
        src/memory_model/TaskID.cpp src/memory_model/TaskID.h
        src/memory_model/PriorityViewInterface.h
        src/api/TaskAPI.h
        src/memory_model/TaskIDFactory.cpp src/memory_model/TaskIDFactory.h
        src/api/TaskCreationResult.cpp src/api/TaskCreationResult.h
        src/memory_model/TagPriorityView.cpp src/memory_model/TagPriorityView.h
        src/memory_model/TaskIDFactoryInterface.h
        src/memory_model/TaskStrorageInterface.h
        src/memory_model/TaskStrorage.cpp src/memory_model/TaskStrorage.h src/memory_model/ReferenceHandler.cpp src/memory_model/ReferenceHandler.h src/api/TaskDTOConverter.cpp src/api/TaskDTOConverter.h)
find_package(Boost 1.70.0 REQUIRED system)

# boost #####################################################
set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     OFF)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()
find_package(Boost REQUIRED COMPONENTS date_time)
find_package(Boost REQUIRED COMPONENTS regex)

target_link_libraries(ToDOList -static)
target_link_libraries(ToDOList ${Boost_LIBRARIES})

##############################################################

include_directories(src)
include_directories(tests)

#boost pthread issue fixup ##################

#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)

#thread
target_link_libraries(ToDOList Threads::Threads)

#############################################

# tests #####################################

include(GoogleTest)
find_package(GTest REQUIRED)
enable_testing()

add_executable(TestsExecutable
                tests/TestTaskNode.cpp
                tests/TestTaskDTO.cpp
                tests/TestTaskCreationResult.cpp
                tests/TestTagPriorityView.cpp
                tests/TestDatePriortyView.cpp
                tests/TestTaskService.cpp
                tests/TestReferenceHandler.cpp

                src/api/TaskService.cpp
                src/memory_model/Task.cpp
                src/memory_model/TaskNode.cpp
                src/memory_model/DatePriorityView.cpp
                src/api/TaskDTO.cpp
                src/memory_model/TaskID.cpp
                src/memory_model/TaskIDFactory.cpp
                src/api/TaskCreationResult.cpp
                src/memory_model/TagPriorityView.cpp
                src/memory_model/TaskStrorage.cpp
                src/memory_model/ReferenceHandler.cpp src/api/TaskDTOConverter.cpp src/api/TaskDTOConverter.h tests/TestTaskStorage.cpp)
target_link_libraries(TestsExecutable GTest::GTest GTest::Main)

gtest_discover_tests(TestsExecutable)

#############################################