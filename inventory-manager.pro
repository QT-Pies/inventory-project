QT       += core gui widgets
greaterThan(QT_MAJOR_VERSION, 4) QT += widgets
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
SOURCES += src/mainwindow.cpp
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
HEADERS += include/mainwindow.hpp
FORMS += mainwindow.ui \
    mainwindow.ui
QMAKE_CXXFLAGS +=  -g -Wno-format-security -std=c++17 -I./include -O3
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
