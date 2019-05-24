CFLAGS = -g -Wall -std=c99 -pedantic -o

all:		app

app:		main.c
		gcc $(CFLAGS) bin/run main.c
		./bin/run

clean:
		rm -f *~ run

