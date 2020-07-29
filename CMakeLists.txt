cmake_minimum_required(VERSION 3.15)
project(ToDOlist)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "-D_GLIBCXX_DEBUG")
add_executable(ToDOList src/main.cpp
        src/api/TaskService.cpp src/api/TaskService.h
        src/memory_model/Task.h
        src/memory_model/TaskNode.cpp src/memory_model/TaskNode.h
        src/memory_model/TaskFactory.cpp src/memory_model/TaskFactory.h
        src/memory_model/TaskController.cpp src/memory_model/TaskController.h
        src/memory_model/PriorityView.cpp src/memory_model/PriorityView.h
        src/api/TaskDTO.cpp src/api/TaskDTO.h
        src/task_io/task_io.h
        src/memory_model/TaskID.cpp src/memory_model/TaskID.h
        src/memory_model/PriorityViewInterface.cpp src/memory_model/PriorityViewInterface.h
        src/api/TaskAPI.h
        src/memory_model/TaskControllerInterface.h
        src/memory_model/TaskFactoryInterface.h
        src/memory_model/TaskIDFactory.cpp src/memory_model/TaskIDFactory.h
        src/api/TaskCreationResult.cpp src/api/TaskCreationResult.h src/memory_model/TagPriorityViewInterface.h src/memory_model/TagPriorityView.cpp src/memory_model/TagPriorityView.h)
#find_package(Boost 1.74.0 REQUIRED system)
#TARGET_LINK_LIBRARIES( ToDOList LINK_PUBLIC ${Boost_LIBRARIES} )
include_directories(src)
include_directories(tests)


include(GoogleTest)
find_package(GTest REQUIRED)
enable_testing()

add_executable(TestsExecutable tests/TaskNodeTest.cpp tests/TestTaskDTO.cpp tests/TestTaskFactory.cpp tests/TaskCreationResultTest.cpp tests/TagPriorityViewTest.cpp)
target_link_libraries(TestsExecutable GTest::GTest GTest::Main)

gtest_discover_tests(TestsExecutable)