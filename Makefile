proc1: p3.c
		gcc -o p3 p3.c -pthread

clean:
		rm *.o p3 a.out
