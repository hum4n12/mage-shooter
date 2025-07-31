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

add_executable(mageshooter src/main.cpp "src/Player.cpp")

target_link_libraries(mageshooter PRIVATE sfml-graphics sfml-window sfml-system box2d)
