cmake_minimum_required(VERSION 3.21.1)

project(InventoryManager VERSION 1.0.0 LANGUAGES CXX)

# Specify C++17 (required by Qt, and our Logger) and make it required or else we exit.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output executables to bin, .o files to obj/
set(EXECUTABLE_OUTPUT_PATH "bin")

# Ignore Qt for now -- get normal program compiling correctly.
#find_package(Qt6 REQUIRED COMPONENTS Widgets)
#qt_standard_project_setup()

# Include our .hpp files
include_directories("./include")

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

# Add source files for bin/gen-inventory
add_executable(gen-inventory
  src/CSVEntry.cpp
  src/InventoryGenerator.cpp
  src/InventoryGeneratorDriver.cpp
)
