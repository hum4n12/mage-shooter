cmake_minimum_required(VERSION 3.20)
project(mageshooter VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
    box2d
    GIT_REPOSITORY https://github.com/erincatto/box2d
    GIT_TAG v3.1.1
)
FetchContent_MakeAvailable(box2d)

file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

add_executable(mageshooter ${SOURCES})

target_include_directories(mageshooter
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(mageshooter PRIVATE sfml-graphics sfml-window sfml-system box2d)

foreach(source_file IN LISTS SOURCES)
    file(RELATIVE_PATH rel_path "${CMAKE_CURRENT_SOURCE_DIR}/src" "${source_file}")

    get_filename_component(dir "${rel_path}" PATH)

    if(dir)
        string(REPLACE "/" "\\" group_name "${dir}")
        source_group("${group_name}" FILES "${source_file}")
    endif()
endforeach()