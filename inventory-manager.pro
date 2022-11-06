SOURCES += src/ActiveInventory.cpp
SOURCES += src/Date.cpp
SOURCES += src/HelperFunctions.cpp
SOURCES += src/InventoryManager.cpp
SOURCES += src/Item.cpp
SOURCES += src/Login.cpp
SOURCES += src/main.cpp
SOURCES += src/NonPerishableItem.cpp
SOURCES += src/PerishableItem.cpp
SOURCES += src/Sales.cpp
SOURCES += src/User.cpp
HEADERS += include/ActiveInventory.hpp
HEADERS += include/Date.hpp
HEADERS += include/HelperFunctions.hpp
HEADERS += include/InventoryManager.hpp
HEADERS += include/Item.hpp
HEADERS += include/Logger.hpp
HEADERS += include/Login.hpp
HEADERS += include/NonPerishableItem.hpp
HEADERS += include/PerishableItem.hpp
HEADERS += include/Sales.hpp
HEADERS += include/User.hpp

QMAKE_CXXFLAGS +=  -g -Wno-format-security -std=c++17 -I./include -O3
