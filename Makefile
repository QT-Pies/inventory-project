#generator driver needs to be an exe


CC = g++
INCLUDES = -I./include
CFLAGS = -g -Wall -Werror -std=c++11 $(INCLUDES) -O3

EXECUTABLES = bin/main bin/InventoryGeneratorDriver

SOURCE = src/main.cpp src/CSVEntry.cpp src/CSVGenerator.cpp src/CSVGeneratorDriver.cpp src/Date.cpp src/Item.cpp src/NonPerishableItem.cpp src/PerishableItem.cpp

OBJECT = obj/main.o obj/CSVEntry.o obj/CSVGenerator.o obj/CSVGeneratorDriver.o obj/Date.o obj/Item.o obj/NonPerishableItem.o obj/PerishableItem.o

all: $(EXECUTABLES) $(OBJECT)

obj/main.o: src/main.cpp 
	$(CC) $(CFLAGS) -c src/main.cpp -o obj/main.o

bin/main: obj/main.o
	$(CC) $(CFLAGS) -o bin/main obj/main.o

obj/CSVEntry.o: src/CSVEntry.cpp
	$(CC) $(CFLAGS) -c src/CSVEntry.cpp -o obj/CSVEntry.o

obj/CSVGenerator.o: src/CSVGenerator.cpp
	$(CC) $(CFLAGS) -c src/CSVGenerator.cpp -o obj/CSVGenerator.o

obj/CSVGeneratorDriver.o: src/CSVGeneratorDriver.cpp
	$(CC) $(CFLAGS) -c src/CSVGeneratorDriver.cpp -o obj/CSVGeneratorDriver.o

bin/InventoryGeneratorDriver: obj/CSVGenerator.o obj/CSVGeneratorDriver.o obj/CSVEntry.o
	$(CC) $(CFLAGS) -o bin/InventoryGeneratorDriver obj/CSVGenerator.o obj/CSVGeneratorDriver.o obj/CSVEntry.o

obj/Date.o: src/Date.cpp
	$(CC) $(CFLAGS) -c src/Date.cpp -o obj/Date.o

obj/Item.o: src/Item.cpp
	$(CC) $(CFLAGS) -c src/Item.cpp -o obj/Item.o

obj/NonPerishableItem.o: src/NonPerishableItem.cpp
	$(CC) $(CFLAGS) -c src/NonPerishableItem.cpp -o obj/NonPerishableItem.o

obj/PerishableItem.o: src/PerishableItem.cpp
	$(CC) $(CFLAGS) -c src/PerishableItem.cpp -o obj/PerishableItem.o

clean: 
	rm $(EXECUTABLES) obj/*.o 
