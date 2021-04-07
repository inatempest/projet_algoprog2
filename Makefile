all: projet

projet: main.o electromenager.o panneaux.o
	gcc main.o electromenager.o panneaux.o -o projet -lm

main.o: main.c electromenager.h panneaux.h
	gcc -Wall -g -c main.c
	
panneaux.o: panneaux.c electromenager.h panneaux.h
	gcc -Wall -g -c panneaux.c

electromenager.o: electromenager.c electromenager.h panneaux.h
	gcc -Wall -g -c electromenager.c

