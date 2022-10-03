#generator driver needs to be an exe


CC = g++
INCLUDES = -I./include
CFLAGS = -g -Wall -Werror -std=c++14 $(INCLUDES) -O3

EXECUTABLES = bin/main bin/gen-inventory

SOURCE = src/main.cpp src/CSVEntry.cpp src/InventoryGenerator.cpp src/InventoryGeneratorDriver.cpp src/Date.cpp src/Item.cpp src/NonPerishableItem.cpp src/PerishableItem.cpp

OBJECT = obj/main.o obj/CSVEntry.o obj/InventoryGenerator.o obj/InventoryGeneratorDriver.o obj/Date.o obj/Item.o obj/NonPerishableItem.o obj/PerishableItem.o obj/ActiveInventory.o

all: $(EXECUTABLES) $(OBJECT)

obj/main.o: src/main.cpp 
	$(CC) $(CFLAGS) -c src/main.cpp -o obj/main.o

bin/main: obj/main.o
	$(CC) $(CFLAGS) -o bin/main obj/main.o

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

obj/Item.o: src/Item.cpp
	$(CC) $(CFLAGS) -c src/Item.cpp -o obj/Item.o

obj/NonPerishableItem.o: src/NonPerishableItem.cpp
	$(CC) $(CFLAGS) -c src/NonPerishableItem.cpp -o obj/NonPerishableItem.o

obj/PerishableItem.o: src/PerishableItem.cpp
	$(CC) $(CFLAGS) -c src/PerishableItem.cpp -o obj/PerishableItem.o

obj/ActiveInventory.o: src/ActiveInventory.cpp
	$(CC) $(CFLAGS) -c src/ActiveInventory.cpp -o obj/ActiveInventory.o

clean: 
	rm $(EXECUTABLES) obj/*.o 
