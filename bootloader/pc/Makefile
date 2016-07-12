all : clean main

clean :
	rm -f main

main : main.c rs232.c
	gcc main.c rs232.c -O2 -Wall -o main
