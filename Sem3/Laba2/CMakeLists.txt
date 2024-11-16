cmake_minimum_required(VERSION 3.25)
project(LABA2_Mephi_Sem3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC OFF)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_executable(LABA2_Mephi_Sem3 main.cpp DataGenerator.cpp SortUI.cpp tests.cpp)

target_link_libraries(LABA2_Mephi_Sem3 PRIVATE Qt6::Core Qt6::Widgets)