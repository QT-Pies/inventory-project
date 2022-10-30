cmake_minimum_required(VERSION 3.21.1)

project(InventoryManager VERSION 1.0.0 LANGUAGES CXX)

# Specify C++17 (required by Qt, and our Logger) and make it required or else we exit.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output executables to bin, .o files to obj/
set(EXECUTABLE_OUTPUT_PATH "bin")

# Include our .hpp files
include_directories("./include")

# It looks like we can run with these flags on g++ and MINGW g++, so add them.
string(APPEND CMAKE_CXX_FLAGS " -Wall -Werror -Wno-format-security ")

# If macOS / Ubuntu build agent, run with these flags
if (UNIX)
  message("I'm running on an Unix based system!")
endif()

# Additional build settings for Noah
if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  message ("I'm running on macOS")

  # This is a hardcoded User install path, but I don't care since I'm the only one running macOS.
  set(CMAKE_PREFIX_PATH "/Users/noah/Qt/6.4.0/macos")
endif()

# If Windows, 

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

