cmake_minimum_required(VERSION 3.10)
project(lab3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Добавление библиотек
add_library(${CMAKE_PROJECT_NAME}_lib_point src/point.cpp)
add_library(${CMAKE_PROJECT_NAME}_lib_figure src/figure.cpp)
add_library(${CMAKE_PROJECT_NAME}_lib_rhombus src/rhombus.cpp)
add_library(${CMAKE_PROJECT_NAME}_lib_rectangle src/rectangle.cpp)
add_library(${CMAKE_PROJECT_NAME}_lib_trapezoid src/trapezoid.cpp)
add_library(${CMAKE_PROJECT_NAME}_lib_utils src/utils.cpp)

# Создание общей цели для линковки всех библиотек
add_library(lab3_common_libs INTERFACE)
target_link_libraries(lab3_common_libs INTERFACE
  ${CMAKE_PROJECT_NAME}_lib_point
  ${CMAKE_PROJECT_NAME}_lib_figure
  ${CMAKE_PROJECT_NAME}_lib_rhombus
  ${CMAKE_PROJECT_NAME}_lib_rectangle
  ${CMAKE_PROJECT_NAME}_lib_trapezoid
  ${CMAKE_PROJECT_NAME}_lib_utils
)

# Линковка библиотек для фигур
target_link_libraries(${CMAKE_PROJECT_NAME}_lib_rhombus PRIVATE ${CMAKE_PROJECT_NAME}_lib_utils)
target_link_libraries(${CMAKE_PROJECT_NAME}_lib_rectangle PRIVATE ${CMAKE_PROJECT_NAME}_lib_utils)
target_link_libraries(${CMAKE_PROJECT_NAME}_lib_trapezoid PRIVATE ${CMAKE_PROJECT_NAME}_lib_utils)

# Добавление исполняемого файла
add_executable(${CMAKE_PROJECT_NAME}_exe main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME}_exe PRIVATE lab3_common_libs)

# Включение тестирования
enable_testing()

# Добавление тестового исполняемого файла
add_executable(tests test/tests.cpp)
target_link_libraries(tests PRIVATE lab3_common_libs gtest_main)

# Добавление теста
add_test(NAME MyProjectTests COMMAND tests)