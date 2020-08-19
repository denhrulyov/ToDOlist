cmake_minimum_required(VERSION 3.15)
project(ToDOlist)
include_directories(src)
include_directories(tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
#set(CMAKE_CXX_FLAGS "-D_GLIBCXX_DEBUG")
add_executable(ToDOList src/main.cpp
        src/core/api/TaskService.cpp src/core/api/TaskService.h
        src/core/memory_model/data/Task.h
        src/core/memory_model/data/Task.cpp
        src/core/memory_model/structure/TaskNode.cpp src/core/memory_model/structure/TaskNode.h
        src/core/memory_model/view/DatePriorityView.cpp src/core/memory_model/view/DatePriorityView.h
        src/core/api/TaskDTO.cpp src/core/api/TaskDTO.h
        src/core/utils/task_io/ConsoleTaskIO.h
        src/core/memory_model/data/TaskID.cpp src/core/memory_model/data/TaskID.h
        src/core/memory_model/view/PriorityViewInterface.h
        src/core/api/TODOList.h
        src/core/memory_model/data/TaskIDFactory.cpp src/core/memory_model/data/TaskIDFactory.h
        src/core/memory_model/view/TagPriorityView.cpp src/core/memory_model/view/TagPriorityView.h
        src/core/memory_model/data/TaskStorageInterface.h
        src/core/memory_model/data/TaskStorage.cpp
        src/core/memory_model/data/TaskStorage.h
        src/core/memory_model/structure/LinkManager.cpp
        src/core/memory_model/structure/LinkManager.h
        src/core/utils/data_transfer/TaskDTOConverter.cpp
        src/core/utils/data_transfer/TaskDTOConverter.h
        src/core/api/RequestResult.cpp src/core/api/RequestResult.h
        src/core/api/TaskModificationResult.cpp src/core/api/TaskModificationResult.h
        src/core/api/TaskCreationResult.cpp src/core/api/TaskCreationResult.h src/core/memory_model/data/TaskPriority.h src/core/memory_model/structure/LinkManagerInterface.h src/cli/states/State.h src/cli/states/ParseState.cpp src/cli/states/ParseState.h src/cli/states/ParseID.cpp src/cli/states/ParseID.h src/cli/states/ShowState.h src/cli/get_commands/GetCommand.h src/cli/get_commands/GetAll.cpp src/cli/get_commands/GetAll.h src/cli/get_commands/GetToday.cpp src/cli/get_commands/GetToday.h src/cli/get_commands/GetThisWeek.cpp src/cli/get_commands/GetThisWeek.h src/cli/get_commands/GetByLabel.cpp src/cli/get_commands/GetByLabel.h src/cli/states/StartState.cpp src/cli/states/StartState.h src/cli/Console.cpp src/cli/Console.h src/cli/CLI.h)

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
        src/core/memory_model/data/TaskPriority.h tests/test_main.cpp src/core/api/TaskServiceInterface.h src/cli/states/State.h src/cli/states/ParseState.cpp src/cli/states/ParseState.h src/cli/states/ParseGetParem.cpp src/cli/states/ParseGetParem.h src/cli/states/ParseTask.cpp src/cli/states/ParseTask.h src/cli/states/ParseAddType.cpp src/cli/states/ParseAddType.h src/cli/states/ParseID.cpp src/cli/states/ParseID.h src/cli/states/ShowState.h src/cli/get_commands/GetCommand.h src/cli/get_commands/GetAll.cpp src/cli/get_commands/GetAll.h src/cli/get_commands/GetToday.cpp src/cli/get_commands/GetToday.h src/cli/get_commands/GetThisWeek.cpp src/cli/get_commands/GetThisWeek.h src/cli/get_commands/GetByLabel.cpp src/cli/get_commands/GetByLabel.h src/cli/states/StartState.cpp src/cli/states/StartState.h src/cli/Console.cpp src/cli/Console.h)
target_link_libraries(TestsExecutable GTest::GTest GTest::Main ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY})

gtest_discover_tests(TestsExecutable)

#############################################