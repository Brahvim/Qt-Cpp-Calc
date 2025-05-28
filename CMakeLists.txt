cmake_minimum_required(VERSION 3.15)
project(Qt1)

set(CMAKE_AUTOMOC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

include_directories(".")
add_executable(Qt1 "main.cpp" "CMyObject.cpp")

find_package(Qt6 REQUIRED COMPONENTS Widgets)
target_link_libraries(Qt1 PRIVATE Qt6::Widgets)
# qt_wrap_cpp(...) # This stuff *straight from hell* (apparently, allegedly) is
# no longer necessary to deal with given modern-day Qt6's "AutoMOC".
