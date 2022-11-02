cmake_minimum_required(VERSION 3.21.1)

project(InventoryManager VERSION 1.0.0 LANGUAGES CXX)

# Specify C++17 (required by Qt, and our Logger) and make it required or else we exit.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output executables to bin, .o files to obj/
set(EXECUTABLE_OUTPUT_PATH "bin")

# Include our .hpp files
include_directories("./include")

# If macOS / Ubuntu, run with these g++ flags.
if (UNIX)
  string(APPEND CMAKE_CXX_FLAGS " -Wall -Werror -Wno-format-security ")
endif()

# Linux Qt Path
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(CMAKE_PREFIX_PATH "~/Qt/6.4.0/gcc_64")
endif()

# macOS Qt Path
if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  set(CMAKE_PREFIX_PATH "~/Qt/6.4.0/macos")
endif()

# If Windows, configure path for Windows Qt install.
# We're gonna drop support for Windows, but this was enough to get it working *sometimes*,
# so why not keep it.
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  # add a warning message for whoever tries to compile natively on windows
  message("You're compiling on Windows, but development is on UNIX systems, may not work as expected.")
  set(CMAKE_PREFIX_PATH "C:/Qt/6.4.0/mingw_64")
  set(Qt6_DIR "C:/Qt/6.4.0/mingw_64/lib/cmake/Qt6")
  set(Qt6Core_DIR "C:/Qt/6.4.0/mingw_64/lib/cmake/Qt6Core")
  set(QT_QMAKE_EXECUTABLE "C:/Qt/6.4.0/mingw_64/bin/qmake.exe")
endif()

# Find Qt packages.
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup()

# Add source files for bin/main
add_executable(main
  src/InventoryManager.cpp
  src/ActiveInventory.cpp
  src/HelperFunctions.cpp
  src/Login.cpp
  src/User.cpp
  src/Sales.cpp
  src/main.cpp
)

# Actually link Qt to our main executable.
target_link_libraries(main
  Qt6::Core
  Qt6::Gui
  Qt6::Widgets
)

# Add source files for bin/gen-inventory
add_executable(gen-inventory
  src/CSVEntry.cpp
  src/InventoryGenerator.cpp
  src/InventoryGeneratorDriver.cpp
)

# Add source files for bin/gen-sales
add_executable(gen-sales
  src/CSVEntry.cpp
  src/Date.cpp
  src/SalesGenerator.cpp
  src/SalesGeneratorDriver.cpp
)

# Gonna limit tests to Ubuntu rather than trying to support my Mac.  May change in the future.
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")

  include(FetchContent)

  # Fetch GTest
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )

  enable_testing()

  FetchContent_MakeAvailable(googletest)

  # Add source files for bin/unit_tests
  add_executable(unit_tests
    src/HelperFunctions.cpp
    src/ActiveInventory.cpp
    src/User.cpp
    src/Login.cpp
    src/Sales.cpp
    src/InventoryManager.cpp
    src/unit_tests.cpp
  )

  # Link GTest
  target_link_libraries(unit_tests GTest::gtest)

  # There is a CMake way of doing this that's more modular and better, but we can just use the way we're currently doing.
endif()
