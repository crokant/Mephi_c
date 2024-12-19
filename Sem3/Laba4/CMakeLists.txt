cmake_minimum_required(VERSION 3.25)
project(LABA4_Mephi_Sem3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finput-charset=UTF-8")

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_executable(LABA4_Mephi_Sem3 main.cpp GraphUI.cpp tests/VertexTests.cpp tests/EdgeTests.cpp tests/GraphTests.cpp )

target_link_libraries(LABA4_Mephi_Sem3 PRIVATE Qt6::Core Qt6::Widgets)
target_compile_options(LABA4_Mephi_Sem3 PRIVATE -finput-charset=UTF-8 -fexec-charset=UTF-8)
