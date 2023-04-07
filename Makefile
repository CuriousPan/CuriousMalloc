SRC = main.c Malloc.c

all:
	${CC} ${SRC} -Wall -Wpedantic -O3 -o main

bf:
	${CC} ${SRC} -Wall -Wpedantic -O3 -DBEST_FIT -o main

ff:
	${CC} ${SRC} -Wall -Wpedantic -O3 -DFIRST_FIT -o main

clean:
	rm -rf main.o Malloc.o main
