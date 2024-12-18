cmake_minimum_required(VERSION 3.10)

# Устанавливаем имя проекта
project(Lab6)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем заголовочные файлы
include_directories(include)

# Добавляем исходные файлы
set(SOURCES
    src/bear.cpp
    src/factory.cpp
    src/npc.cpp
    src/visitor.cpp
    src/vup.cpp
    src/vykhuhol.cpp
)

# Добавляем исполняемый файл
add_executable(main main.cpp ${SOURCES})

# Подключаем Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Добавляем тесты
add_executable(tests tests/test.cpp ${SOURCES})

# Линкуем тесты с Google Test
target_link_libraries(tests gtest_main)

# Указываем, что main использует все необходимые библиотеки
# target_link_libraries(main some_libraries)