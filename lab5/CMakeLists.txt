cmake_minimum_required(VERSION 3.10)

project(CustomMemoryVector)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    main.cpp
    src/memory.cpp
)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(program ${SOURCES})

if (CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(program PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Указываем файлы для тестов
set(TEST_SOURCES
    tests/test.cpp
    src/memory.cpp
)

#исполняемый файл для тестов
add_executable(tests ${TEST_SOURCES})
# Отключаем вывод сообщений об аллокации/деаллокации в тестах
target_compile_definitions(tests PRIVATE NDEBUG)

# Подключаем Google Test
target_link_libraries(tests gtest_main)

if (COMMAND cmake_policy)
  cmake_policy(SET CMP0012 NEW)  # Политика для аргументов с "ON"
  cmake_policy(SET CMP0003 NEW)  # Политика для библиотек
  cmake_policy(SET CMP0028 NEW)  # Политика для двойных двоеточий в именах
endif()

enable_testing()
add_test(NAME AllTests COMMAND tests)

find_package(Threads REQUIRED)
target_link_libraries(tests Threads::Threads)