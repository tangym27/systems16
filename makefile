all: share.c
	gcc share.c

run:
	./a.out

clean:
	rm *.out
