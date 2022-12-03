# minium version of cmake needed
cmake_minimum_required(VERSION 3.25)

# project
project(ffsExpianedModifier)

# set version number
set(CMAKE_PROJECT_VERSION_MAJOR 0)
set(CMAKE_PROJECT_VERSION_MINOR 1)

set(SOURCES 
    src/fileIo.cpp
    src/stringEncodingProcess.cpp
    src/stringRegexRuledModify.cpp
    src/main.cpp
)

add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
    )

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)