all: projet

projet: main.o electromenager.o 
	gcc main.o electromenager.o -o projet

main.o: main.c electromenager.h panneaux.h
	gcc -Wall -g -c main.c
	
electromenager.o: electromenager.c electromenager.h panneaux.h
	gcc -Wall -g -c electromenager.c


