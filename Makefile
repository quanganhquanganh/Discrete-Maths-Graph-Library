all: 
	gcc -c ./src/*.c
	gcc -c ./io/*.c
	gcc -c ./tests/*.c
	gcc -c ./libfdr/*.c
	ar ru ./lib/libfdr.a ./libfdr/*.o
	ranlib ./lib/libfdr.a 
	ar ru ./lib/libio.a ./libfdr/*.o ./io/*.o ./src/graph.o
	ar ru ./lib/libgrp.a ./libfdr/*.o ./src/*.o

clean:
	rm -f core *.o all