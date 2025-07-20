cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project("StateManagerLib")

include(FetchContent)

add_library(StateManagerLibImpl STATIC
    src/StateManager.cpp
)

target_include_directories(StateManagerLibImpl PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    add_compile_options(/Qspectre-)
endif()

## --== LOGGER ==--
FetchContent_Declare(LoggerLibImpl
  GIT_REPOSITORY https://github.com/KOD-development/Logger.git
  GIT_TAG main
)
FetchContent_MakeAvailable(LoggerLibImpl)

## --== SFML ==--
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

target_link_libraries(StateManagerLibImpl PUBLIC LoggerLibImpl SFML::Graphics)
target_compile_options(StateManagerLibImpl PRIVATE -Wall)

# --- TESTING ---

enable_testing()

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(StateManagerTests
    "tests/test_StateManager.cpp"
)

target_link_libraries(StateManagerTests PRIVATE StateManagerLibImpl gtest_main)

include(GoogleTest)
gtest_discover_tests(StateManagerTests)