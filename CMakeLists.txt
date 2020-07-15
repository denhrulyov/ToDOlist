cmake_minimum_required(VERSION 3.15)
project(ToDOlist)

set(CMAKE_CXX_STANDARD 17)

add_executable(ToDOList src/main.cpp src/memory_model/TaskService.cpp src/memory_model/TaskService.h src/memory_model/Task.h src/memory_model/TaskNode.cpp src/memory_model/TaskNode.h src/memory_model/TaskStorage.cpp src/memory_model/TaskStorage.h src/memory_model/TaskController.cpp src/memory_model/TaskController.h src/memory_model/PriorityView.cpp src/memory_model/PriorityView.h src/memory_model/TaskEntity.cpp src/memory_model/TaskEntity.h src/task_io/task_io.hpp)

include_directories(src)

include(GoogleTest)
find_package(GTest REQUIRED)
enable_testing()

add_executable(TestsExecutable tests/TaskNodeTest.cpp tests/TestTaskEntity.cpp tests/TestTaskStorage.cpp)
target_link_libraries(TestsExecutable GTest::GTest GTest::Main)

gtest_discover_tests(TestsExecutable)