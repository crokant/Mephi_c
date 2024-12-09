cmake_minimum_required(VERSION 3.25)
project(LABA3_Mephi_Sem3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC OFF)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_executable(LABA3_Mephi_Sem3 main.cpp Board.h Board.cpp Bot.h Bot.cpp Game.h Game.cpp UnorderedMap.h TictactoeUI.cpp)

target_link_libraries(LABA3_Mephi_Sem3 PRIVATE Qt6::Core Qt6::Widgets)