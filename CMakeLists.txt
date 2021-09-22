cmake_minimum_required(VERSION 3.5)

project(BT_test LANGUAGES C)

set(SUBPROJECTS
    Struct
    Parser
)

foreach(subdir IN LISTS SUBPROJECTS)
    add_subdirectory(${subdir})
endforeach()
