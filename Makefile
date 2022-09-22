#c++ standard 11
#warning as an error
#optimization level 3 for -o
#

CC = g++

CFLAGS = -g -Wall -Werror

##main: main.o PerishableItem.o Item.o NonPerishableItem.o
##	$(CC) $(CFLAGS) -o main main.o PerishableItem.o Item.o NonPerishableItem.o

##main.o: main.cpp include/PerishableItem.hpp include/Item.hpp include/NonPerishableItem.hpp
##	$(CC) $(CFLAGS) -c main.cpp 

PerishableItem.o: src/PerishableItem.cpp include/PerishableItem.hpp
	$(CC) -c PerishableItem.cpp

NonPerishableItem.o: src/NonPerishableItem.cpp include/NonPerishableItem.hpp
	$(CC) -c NonPerishableItem.cpp

Item.o: src/Item.cpp include/Item.hpp
	$(CC) -c Item.cpp

clean:
	-rm *.o 



	
