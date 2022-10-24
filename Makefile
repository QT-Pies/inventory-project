CC = g++
INCLUDES = -I./include
CFLAGS = -g -Wall -Werror -std=c++14 $(INCLUDES) -O3

EXECUTABLES = bin/main bin/gen-inventory bin/unit_tests

SOURCE = src/main.cpp src/CSVEntry.cpp src/InventoryGenerator.cpp src/InventoryGeneratorDriver.cpp src/Date.cpp src/HelperFunctions.cpp src/Item.cpp src/NonPerishableItem.cpp src/PerishableItem.cpp src/ActiveInventory.cpp src/InventoryManager.cpp src/Sales.cpp src/Login.cpp src/User.cpp
OBJECT = obj/main.o obj/CSVEntry.o obj/InventoryGenerator.o obj/InventoryGeneratorDriver.o obj/Date.o obj/HelperFunctions.o obj/Item.o obj/NonPerishableItem.o obj/PerishableItem.o obj/ActiveInventory.o obj/InventoryManager.o obj/Sales.o obj/Login.o obj/User.o

all: $(OBJECT) $(EXECUTABLES)

obj/main.o: src/main.cpp obj/InventoryManager.o
	$(CC) $(CFLAGS) -c src/main.cpp -o obj/main.o

bin/main: obj/main.o obj/InventoryManager.o obj/HelperFunctions.o
	$(CC) $(CFLAGS) -o bin/main obj/main.o obj/InventoryManager.o obj/ActiveInventory.o obj/HelperFunctions.o obj/Login.o obj/User.o obj/Sales.o

obj/CSVEntry.o: src/CSVEntry.cpp
	$(CC) $(CFLAGS) -c src/CSVEntry.cpp -o obj/CSVEntry.o

obj/InventoryGenerator.o: src/InventoryGenerator.cpp
	$(CC) $(CFLAGS) -c src/InventoryGenerator.cpp -o obj/InventoryGenerator.o

obj/InventoryGeneratorDriver.o: src/InventoryGeneratorDriver.cpp
	$(CC) $(CFLAGS) -c src/InventoryGeneratorDriver.cpp -o obj/InventoryGeneratorDriver.o

bin/gen-inventory: obj/InventoryGenerator.o obj/InventoryGeneratorDriver.o obj/CSVEntry.o
	$(CC) $(CFLAGS) -o bin/gen-inventory obj/InventoryGenerator.o obj/InventoryGeneratorDriver.o obj/CSVEntry.o

obj/Date.o: src/Date.cpp
	$(CC) $(CFLAGS) -c src/Date.cpp -o obj/Date.o

obj/HelperFunctions.o: src/HelperFunctions.cpp
	$(CC) $(CFLAGS) -c src/HelperFunctions.cpp -o obj/HelperFunctions.o

obj/Item.o: src/Item.cpp
	$(CC) $(CFLAGS) -c src/Item.cpp -o obj/Item.o

obj/NonPerishableItem.o: src/NonPerishableItem.cpp
	$(CC) $(CFLAGS) -c src/NonPerishableItem.cpp -o obj/NonPerishableItem.o

obj/PerishableItem.o: src/PerishableItem.cpp
	$(CC) $(CFLAGS) -c src/PerishableItem.cpp -o obj/PerishableItem.o

obj/ActiveInventory.o: src/ActiveInventory.cpp
	$(CC) $(CFLAGS) -c src/ActiveInventory.cpp -o obj/ActiveInventory.o

obj/InventoryManager.o: src/InventoryManager.cpp obj/ActiveInventory.o obj/Login.o obj/User.o obj/Sales.o
	$(CC) $(CFLAGS) -c src/InventoryManager.cpp -o obj/InventoryManager.o

obj/Sales.o: src/Sales.cpp
	$(CC) $(CFLAGS) -c src/Sales.cpp -o obj/Sales.o

obj/Login.o: src/Login.cpp
	$(CC) $(CFLAGS) -c src/Login.cpp -o obj/Login.o

obj/User.o: src/User.cpp
	$(CC) $(CFLAGS) -c src/User.cpp -o obj/User.o

bin/unit_tests:
	$(CC) $(CFLAGS) -o bin/unit_tests src/unit_tests.cpp -lgtest obj/InventoryManager.o obj/ActiveInventory.o obj/HelperFunctions.o obj/Login.o obj/User.o obj/Sales.o

clean: 
	rm $(EXECUTABLES) obj/*.o 

better:
	clang-format -i src/* include/* tests/*